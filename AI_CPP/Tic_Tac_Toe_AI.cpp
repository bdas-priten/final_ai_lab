#include <iostream>
#include <vector>
#include <limits>
using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Function to display the board
void displayBoard() {
    cout << endl;
    cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
    cout << "-+-+-" << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
    cout << "-+-+-" << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
    cout << endl;
}

// Check for winner
bool checkWinner(char player) {
    int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };

    for (auto &combo : winCombos) {
        if (board[combo[0]] == player && board[combo[1]] == player && board[combo[2]] == player) {
            return true;
        }
    }
    return false;
}

// Check if board is full
bool isDraw() {
    for (char c : board) {
        if (c == ' ') return false;
    }
    return true;
}

// Minimax algorithm
int minimax(bool isMaximizing) {
    if (checkWinner('X')) return 10;
    if (checkWinner('O')) return -10;
    if (isDraw()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(false);
                board[i] = ' ';
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(true);
                board[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

// Computer move using minimax
void computerMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            board[i] = 'X';
            int score = minimax(false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }

    board[move] = 'X';
    cout << "Computer chose position: " << (move + 1) << endl;
}

// Player move
void playerMove() {
    displayBoard();
    int move;
    do {
        cout << "Enter your move (1-9): ";
        cin >> move;
        move -= 1;
    } while (move < 0 || move >= 9 || board[move] != ' ');

    board[move] = 'O';
}

// Check if game is over
bool isGameOver() {
    if (checkWinner('X')) {
        displayBoard();
        cout << "Computer wins!" << endl;
        return true;
    }
    if (checkWinner('O')) {
        displayBoard();
        cout << "You win!" << endl;
        return true;
    }
    if (isDraw()) {
        displayBoard();
        cout << "It's a draw!" << endl;
        return true;
    }
    return false;
}

// Main function
int main() {
    cout << "Tic-Tac-Toe: You (O) vs Computer (X)" << endl;

    while (true) {
        playerMove();
        if (isGameOver()) break;

        computerMove();
        if (isGameOver()) break;
    }

    return 0;
}
