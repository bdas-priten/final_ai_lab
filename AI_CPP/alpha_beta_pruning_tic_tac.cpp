#include <iostream>
#include <limits>
using namespace std;

const char PLAYER = 'X'; // Human
const char AI = 'O';     // Computer

char board[3][3];

// Initialize the board with empty spaces
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '_';
}

// Display the board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// Check if there are any moves left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// Evaluate the board
int evaluate() {
    // Rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    return 0;
}

// Alpha-Beta pruning minimax function
int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = AI;
                    int val = minimax(depth + 1, false, alpha, beta);
                    board[i][j] = '_';
                    best = max(best, val);
                    alpha = max(alpha, best);

                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = PLAYER;
                    int val = minimax(depth + 1, true, alpha, beta);
                    board[i][j] = '_';
                    best = min(best, val);
                    beta = min(beta, best);

                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = AI;
                int moveVal = minimax(0, false, -1000, 1000);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Check if game is over
bool isGameOver() {
    int score = evaluate();
    if (score == 10 || score == -10 || !isMovesLeft())
        return true;
    return false;
}

// Driver
int main() {
    initializeBoard();
    cout << "You are X, Computer is O\n";

    printBoard();

    while (!isGameOver()) {
        int x, y;
        cout << "\nEnter your move (row and column: 0-based): ";
        cin >> x >> y;

        if (board[x][y] != '_') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[x][y] = PLAYER;
        printBoard();

        if (isGameOver()) break;

        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = AI;
        cout << "\nComputer played:\n";
        printBoard();
    }

    int finalScore = evaluate();
    if (finalScore == 10)
        cout << "\nComputer wins!\n";
    else if (finalScore == -10)
        cout << "\nYou win!\n";
    else
        cout << "\nIt's a draw!\n";

    return 0;
}
