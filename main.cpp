#include "mtcs.hpp"
#include <cctype>

int main() {
	int		move;
	char	winner = ' ';
	char	player = ' ';
	XOGame game;

	cout << "Welcome to Tic-Tac-Toe!\n";
	while (player != 'X' && player != 'O')
	{
		cout << "What do you want to play X or O? :";
		cin >> player;
		player = toupper(player);
	}
	game.displayBoard();

	while (winner == ' ') {
		if (game.player == player)
		{
			cout << "Player " << game.player << "'s turn. Enter your move (1-9): ";
			cin >> move;

			// Validate input
			if (move < 1 || move > 9 || game.board[move - 1] != ' ') {
				cout << "Invalid move. Please try again.\n";
				continue;
			}
		}
		else
		{
			mtcs mt(game, game.player);
			move = mt.runMtcs() + 1;
			cout << "final move is :" << move << endl;
		}
		// Update the board
		game.makeMove(move - 1);
		game.displayBoard();

		// Check for a winner or draw
		winner = game.checkWinner();

		// Switch player

	}
	if (winner == 'D') {
		cout << "It's a draw!\n";
	} else if (winner == player)
	{
		cout << "Good job you win!!" << endl;
	}
	else {
		cout << "You are so bad Ai WON!" << endl;
	}

	return 0;
}
