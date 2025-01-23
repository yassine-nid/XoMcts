#include "XOGame.hpp"

int main() {
	int		move;
	char	winner = ' ';
	XOGame game;

	cout << "Welcome to Tic-Tac-Toe!\n";
	game.displayBoard();

	while (winner == ' ') {
		cout << "Player " << game.player << "'s turn. Enter your move (1-9): ";
		cin >> move;

		// Validate input
		if (move < 1 || move > 9 || game.board[move - 1] != ' ') {
			cout << "Invalid move. Please try again.\n";
			continue;
		}

		// Update the board
		game.makeMove(move);
		game.displayBoard();

		// Check for a winner or draw
		winner = game.checkWinner();

		// Switch player

	}
	if (winner == 'D') {
		cout << "It's a draw!\n";
	} else {
		cout << "Player " << winner << " wins! Congratulations!\n";
	}

	return 0;
}