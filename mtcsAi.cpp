#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

const int BOARD_SIZE = 3;
const int EMPTY = 0;
const int PLAYER = 1;
const int AI = 2;

class Board {
public:
    int grid[BOARD_SIZE][BOARD_SIZE];

    Board() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                grid[i][j] = EMPTY;
            }
        }
    }

    bool is_full() const {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (grid[i][j] == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    bool is_winner(int player) const {
        // Check rows and columns
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) return true;
            if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player) return true;
        }
        // Check diagonals
        if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) return true;
        if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) return true;
        return false;
    }

    std::vector<std::pair<int, int>> get_available_moves() const {
        std::vector<std::pair<int, int>> moves;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (grid[i][j] == EMPTY) {
                    moves.push_back({i, j});
                }
            }
        }
        return moves;
    }

    void make_move(int player, int row, int col) {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && grid[row][col] == EMPTY) {
            grid[row][col] = player;
        }
    }

    void print() const {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                char symbol = (grid[i][j] == EMPTY) ? '.' : (grid[i][j] == PLAYER) ? 'X' : 'O';
                std::cout << symbol << " ";
            }
            std::cout << std::endl;
        }
    }
};

class MCTS {
public:
    struct Node {
        Board state;
        Node* parent;
        std::vector<Node*> children;
        int wins = 0;
        int visits = 0;
        std::pair<int, int> move;

        Node(Board state, Node* parent = nullptr, std::pair<int, int> move = {-1, -1})
            : state(state), parent(parent), move(move) {}

        ~Node() {
            for (auto child : children) {
                delete child;
            }
        }
    };

    Node* root;

    MCTS(Board initial_state) {
        root = new Node(initial_state);
    }

    ~MCTS() {
        delete root;
    }

    Node* select(Node* node) {
        while (!node->state.is_full() && !node->state.is_winner(PLAYER) && !node->state.is_winner(AI)) {
            if (node->children.size() < node->state.get_available_moves().size()) {
                return expand(node);
            } else {
                node = best_child(node);
            }
        }
        return node;
    }

    Node* expand(Node* node) {
        auto available_moves = node->state.get_available_moves();
        for (auto move : available_moves) {
            bool already_expanded = false;
            for (auto child : node->children) {
                if (child->move == move) {
                    already_expanded = true;
                    break;
                }
            }
            if (!already_expanded) {
                Board new_state = node->state;
                new_state.make_move((node->state.is_winner(PLAYER) || node->state.is_winner(AI)) ? EMPTY : AI, move.first, move.second);
                Node* new_node = new Node(new_state, node, move);
                node->children.push_back(new_node);
                return new_node;
            }
        }
        return nullptr;
    }

    void backpropagate(Node* node, int result) {
        while (node != nullptr) {
            node->visits++;
            node->wins += result;
            node = node->parent;
        }
    }

    Node* best_child(Node* node) {
        Node* best = nullptr;
        double best_score = -1;
        for (auto child : node->children) {
            double score = (double)child->wins / child->visits + sqrt(2 * log(node->visits) / child->visits);
            if (score > best_score) {
                best_score = score;
                best = child;
            }
        }
        return best;
    }

    std::pair<int, int> best_move(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            Node* node = select(root);
            int result = simulate(node);
            backpropagate(node, result);
        }
        Node* best = best_child(root);
        return best->move;
    }

    int simulate(Node* node) {
        Board temp_state = node->state;
        int current_player = AI;
        while (!temp_state.is_full() && !temp_state.is_winner(PLAYER) && !temp_state.is_winner(AI)) {
            auto moves = temp_state.get_available_moves();
            auto move = moves[rand() % moves.size()];
            temp_state.make_move(current_player, move.first, move.second);
            current_player = (current_player == PLAYER) ? AI : PLAYER;
        }
        if (temp_state.is_winner(AI)) {
            return 1;
        } else if (temp_state.is_winner(PLAYER)) {
            return 0;
        } else {
            return 0; // Draw
        }
    }
};

int main() {
    srand(time(0));
    Board board;
    bool player_turn = true;

    while (!board.is_full() && !board.is_winner(PLAYER) && !board.is_winner(AI)) {
        board.print();
        if (player_turn) {
            int row, col;
            std::cout << "Your move (row col): ";
            std::cin >> row >> col;
            if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board.grid[row][col] == EMPTY) {
                board.make_move(PLAYER, row, col);
                player_turn = false;
            } else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        } else {
            std::cout << "AI is thinking..." << std::endl;
            MCTS mcts(board);
            auto move = mcts.best_move(100000); // Number of MCTS iterations
            board.make_move(AI, move.first, move.second);
            player_turn = true;
        }
    }

    board.print();
    if (board.is_winner(PLAYER)) {
        std::cout << "You win!" << std::endl;
    } else if (board.is_winner(AI)) {
        std::cout << "AI wins!" << std::endl;
    } else {
        std::cout << "It's a draw!" << std::endl;
    }

    return 0;
}