#include "XOGame.hpp"

// Function to display the game board
void XOGame::displayBoard() const
{
    // Clear the terminal
    cout << "\033[2J\033[H";

    cout << "\n";
    for (int i = 0; i < 9; i++) {
        if (board[i] == 'X') {
            cout << " \033[31m" << board[i] << "\033[0m"; // Red color for X
        } else if (board[i] == 'O') {
            cout << " \033[34m" << board[i] << "\033[0m"; // Blue color for O
        } else {
            cout << " " << board[i];
        }
        if ((i + 1) % 3 == 0) {
            cout << "\n";
            if (i < 6) cout << "---|---|---\n";
        } else {
            cout << " |";
        }
    }
    cout << "\n\n";
}

// Function to check for a winner or draw
char XOGame::checkWinner() const
{
	const int winPatterns[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
		{0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
		{0, 4, 8}, {2, 4, 6}             // Diagonals
	};

	for (auto& pattern : winPatterns) {
		if (board[pattern[0]] == board[pattern[1]] &&
			board[pattern[1]] == board[pattern[2]] &&
			board[pattern[0]] != ' ') {
			return board[pattern[0]];
		}
	}

	// Check for a draw
	for (char cell : board) {
		if (cell == ' ') return ' '; // Game is still ongoing
	}

	return 'D'; // Draw
}

void XOGame::changePlayer()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

void	XOGame::makeMove(int move)
{
	board[move - 1] = player;
	changePlayer();
}

