#include <vector>

using namespace std;

typedef struct Node
{
	vector<Node *>	children;
	Node*			parent;
	int				visits = 0;
	int				wins = 0;
	int				move = -1;
	bool			isPlayerTurn;

	Node(bool isPlayerTurn) : isPlayerTurn(isPlayerTurn){}
	 ~Node() {
        for (auto child : children) delete child;
    }
}	Node;
