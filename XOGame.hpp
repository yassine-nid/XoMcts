#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

class XOGame
{
	public:
		vector <char>	board;
		char			player;
	
		XOGame() : board(9, ' '), player('X'){}
		XOGame(XOGame &game) : board(game.board), player(game.player) {}
		~XOGame(){}
		void		displayBoard() const;
		char		checkWinner() const;
		void		makeMove(int move);
		void		makeRandomMove();
		vector<int>	avalibleMoves();
		void		changePlayer();

};
