#include <iostream>
#include <vector>

using namespace std;

class XOGame
{
	public:
		vector <char>	board;
		char			player;
	
		XOGame() : board(9, ' '), player('X'){}
		~XOGame(){}
		void	displayBoard() const;
		char	checkWinner() const;
		void	makeMove(int move);
		void	changePlayer();

};