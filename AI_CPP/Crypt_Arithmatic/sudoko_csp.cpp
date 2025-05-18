#include <iostream>
using namespace std;

const int SIZE = 9;

bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for (int i = 0; i < SIZE; i++)
        if (board[row][i] == num)
            return false;

    // Check column
    for (int i = 0; i < SIZE; i++)
        if (board[i][col] == num)
            return false;

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (board[i][j] == num)
                return false;

    return true;
}

bool solve(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve(board))
                            return true;
                        board[row][col] = 0; // Backtrack
                    }
                }
                return false; // no valid number found
            }
        }
    }
    return true; // solved
}

void printBoard(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------\n";
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) cout << "| ";
            cout << board[row][col] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solve(board)) {
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
