#include <vector>
#include <cmath>
#include "XOGame.hpp"
#define UCB1_C 1.414
#define NUMBER_ITERATIONS 1000

using namespace std;

typedef struct Node
{
	vector<Node *>	children;
	Node*			parent;
	XOGame			game;
	int				visits = 0;
	int				wins = 0;
	int				move = -1;
	char			player;
	int				isFullyExpanded;
	int				isTerminated;

	Node(char Player, XOGame Game) : player(Player), isFullyExpanded(0), isTerminated(0){
		game = Game;
	}
	 ~Node() {
		for (auto child : children) delete child;
	}
	void	checkExpansion();
	void	checkTermination();
}	Node;

class mtcs {
	public:

		Node *root;
		mtcs(XOGame game, char player)
		{
			root = new Node(player, game);
		}
		~mtcs()
		{
			// delete root;
		}
		int	runMtcs();
		void	runIteration();
		Node*	select(Node *node);
		Node*	expand(Node *node);
		int		simulate(Node *node);
		void	backPorpagate(Node *node, int result);
		// std::pair <int, int> getBestMove();
};

