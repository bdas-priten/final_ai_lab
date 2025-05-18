#include <iostream>
using namespace std;

char board[9];

void printBoard() {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << (i % 3 == 2 ? '\n' : ' ');
    }
    cout << '\n';
}

bool checkWin(char p) {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto &w : wins) {
        if (board[w[0]] == p && board[w[1]] == p && board[w[2]] == p)
            return true;
    }
    return false;
}

bool isDraw() {
    for (int i = 0; i < 9; i++)
        if (board[i] == '.') return false;
    return true;
}

int main() {
    cout << "Welcome to Tic-Tac-Toe! Two players (X and O).\n\n";

    for (int i = 0; i < 9; i++) board[i] = '.';
    printBoard();

    char currentPlayer = 'X';
    int move;
    int movesPlayed = 0;

    // Read all moves from input until EOF or 9 moves max
    while (movesPlayed < 9 && cin >> move) {
        if (move < 1 || move > 9 || board[move-1] != '.') {
            cout << "Invalid move: " << move << ". Game aborted.\n";
            return 1;
        }
        board[move - 1] = currentPlayer;
        printBoard();

        if (checkWin(currentPlayer)) {
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            return 0;
        }
        if (isDraw()) {
            cout << "Game is a draw!\n";
            return 0;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        movesPlayed++;
    }

    cout << "Game ended. Thanks for playing!\n";
    return 0;
}
