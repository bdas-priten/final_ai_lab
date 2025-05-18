#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = '_';

char board[3][3] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};

// Predefined human moves for online compiler testing
int humanMoves[][2] = {{0, 0}, {2, 2}, {1, 1}}; // (row, col)
int moveIndex = 0;
int totalMoves = sizeof(humanMoves) / sizeof(humanMoves[0]);

// Function to print the board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << ' ';
        }
        cout << "\n";
    }
}

// Function to check for a winner
char checkWinner() {
    // Rows, columns, diagonals
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    return EMPTY;
}

// Check if board is full
bool isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

// Minimax algorithm
int minimax(bool isMax) {
    char winner = checkWinner();
    if (winner == AI) return +10;
    if (winner == PLAYER) return -10;
    if (isFull()) return 0;

    int best = isMax ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = isMax ? AI : PLAYER;
                int score = minimax(!isMax);
                board[i][j] = EMPTY;
                best = isMax ? max(best, score) : min(best, score);
            }
        }
    }
    return best;
}

// Find best move for AI
pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    cout << "You are X, Computer is O\n";

    while (true) {
        printBoard();
        if (checkWinner() != EMPTY || isFull()) break;

        // Human move (predefined for online compiler)
        if (moveIndex < totalMoves) {
            int x = humanMoves[moveIndex][0];
            int y = humanMoves[moveIndex][1];
            moveIndex++;
            if (board[x][y] == EMPTY) {
                board[x][y] = PLAYER;
                cout << "\nYour move: (" << x << ", " << y << ")\n";
            } else {
                cout << "Invalid move at (" << x << "," << y << ")\n";
                continue;
            }
        }

        printBoard();
        if (checkWinner() != EMPTY || isFull()) break;

        // AI move
        auto [aiX, aiY] = findBestMove();
        board[aiX][aiY] = AI;
        cout << "\nComputer played: (" << aiX << ", " << aiY << ")\n";
    }

    printBoard();
    char result = checkWinner();
    if (result == PLAYER)
        cout << "\nYou win!\n";
    else if (result == AI)
        cout << "\nComputer wins!\n";
    else
        cout << "\nIt's a draw!\n";

    return 0;
}
