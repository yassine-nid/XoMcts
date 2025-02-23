#include "mtcs.hpp"
#include <cstdint>
#include <future>

char	changePlayer(char player)
{
	if (player == 'X')
		return ('O');
	else
	 	return ('X');
}

double ucb1(Node* node)
{
	if (!node->visits)
		return (INFINITY);
	return ((double)node->wins / node->visits + UCB1_C * sqrt(log(node->parent->visits) / node->visits));
}

void	Node::checkExpansion()
{
	isFullyExpanded = game.avalibleMoves().size() == children.size();
}

void	Node::checkTermination()
{
	isTerminated = game.checkWinner() != ' ';
}

Node*	mtcs::select(Node *node)
{
	while (node->children.size() && node->isFullyExpanded)
	{
		double	bestScore = -INFINITY;
		Node	*bestChild = nullptr;

		for (auto child : node->children)
		{
			double score;
			
			score = ucb1(child);
			if (score > bestScore)
			{
				bestScore = score;
				bestChild = child;
			}
		}
		node = bestChild;
	}
	return node;
}

Node* mtcs::expand(Node *node)
{
	if (node->isTerminated || node->isFullyExpanded)
		return node;

	vector<int> avalibleMoves = node->game.avalibleMoves();
	for (auto move : avalibleMoves)
	{
		bool moveAlreadyExpanded = false;
		for (auto child : node->children)
		{
			if (child->move == move)
			{
				moveAlreadyExpanded = true;
				break;
			}
		}
		if (!moveAlreadyExpanded)
		{
			XOGame newGame(node->game);
			newGame.makeMove(move);
			Node* newNode = new Node(changePlayer(node->player), newGame);
			newNode->move = move;
			newNode->parent = node;
			node->children.push_back(newNode);
			return newNode;
		}
	}
	node->isFullyExpanded = true;
	return node;
}

int		mtcs::simulate(Node *node)
{
	XOGame simulationGame(node->game);
	while (simulationGame.checkWinner() == ' ')
		simulationGame.makeRandomMove();
	char winner = simulationGame.checkWinner();
	if (winner == node->player)
		return 1;
	else if (winner == 'D')
		return 0;
	else
	 	return -1;
}

void	mtcs::backPorpagate(Node *node, int result)
{
	while (node != nullptr)
    {
        node->visits++;
		node->wins += result;
		result *= -1;
        node = node->parent;
    }
}

void	mtcs::runIteration()
{
	Node	*leafNode;
	int		result;

	leafNode = select(root);
	leafNode->checkExpansion();
	leafNode = expand(leafNode);
	leafNode->checkTermination();
	leafNode->checkExpansion();
	result = simulate(leafNode);
	backPorpagate(leafNode, result);
}

void printNodeInfo(Node* node, const string& prefix = "") {
    cout << prefix << "Node Info:" << endl;
    cout << prefix << "  Move: " << node->move << endl;
    cout << prefix << "  Player: " << node->player << endl;
    cout << prefix << "  Visits: " << node->visits << endl;
    cout << prefix << "  Wins: " << node->wins << endl;
    cout << prefix << "  Fully Expanded: " << (node->isFullyExpanded ? "Yes" : "No") << endl;
    cout << prefix << "  Terminated: " << (node->isTerminated ? "Yes" : "No") << endl;
}

void printTree(Node* node, int depth = 0) {
    string prefix(depth * 2, ' '); // Indent based on depth
    printNodeInfo(node, prefix);

    for (auto child : node->children) {
        printTree(child, depth + 1);
    }
}


int	mtcs::runMtcs()
{
	Node	*bestMove = nullptr;
	int		mostVisited = -1;

	for (int i = 0; i < NUMBER_ITERATIONS; i++)
		runIteration();
	for (unsigned long n = 0; n < root->children.size(); n++)
	{
		if (root->children[n]->visits > mostVisited)
		{
			bestMove = root->children[n];
			mostVisited = root->children[n]->visits;
		}
	}
	// printTree(root, 0); // for debuging 
	if (bestMove != nullptr)
		return bestMove->move;
	else
	{
		cout << "No best move found! Something went wrong!" << endl;
		return -1;
	}
}

