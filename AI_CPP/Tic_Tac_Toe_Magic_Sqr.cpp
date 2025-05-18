#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 3;
const int MAGIC_SQUARE[3][3] = {
    {8, 3, 4},
    {1, 5, 9},
    {6, 7, 2}
};

int board[BOARD_SIZE][BOARD_SIZE] = {0};
set<int> playerXMoves;
set<int> playerOMoves;

void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (board[i][j]) {
                case 1: cout << " X "; break;
                case 2: cout << " O "; break;
                default: cout << "   "; break;
            }
            if (j < BOARD_SIZE - 1) cout << "|";
        }
        cout << endl;
        if (i < BOARD_SIZE - 1) cout << "---|---|---" << endl;
    }
}

pair<int, int> getPosition(int move) {
    int row = (move - 1) / BOARD_SIZE;
    int col = (move - 1) % BOARD_SIZE;
    return {row, col};
}

bool isValidMove(int move) {
    if (move < 1 || move > 9) return false;
    auto [row, col] = getPosition(move);
    return board[row][col] == 0;
}

void makeMove(int move, bool isPlayerX) {
    auto [row, col] = getPosition(move);
    board[row][col] = isPlayerX ? 1 : 2;
    (isPlayerX ? playerXMoves : playerOMoves).insert(MAGIC_SQUARE[row][col]);
}

bool isPositionEmpty(int magicValue) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (MAGIC_SQUARE[i][j] == magicValue && board[i][j] == 0)
                return true;
        }
    }
    return false;
}

bool checkWin(bool isPlayerX) {
    vector<int> moveList((isPlayerX ? playerXMoves : playerOMoves).begin(),
                         (isPlayerX ? playerXMoves : playerOMoves).end());

    int n = moveList.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (moveList[i] + moveList[j] + moveList[k] == 15)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    vector<int> moves;
    int move;
    while (cin >> move) {
        moves.push_back(move);
    }

    cout << "Welcome to Tic-Tac-Toe using the Magic Square method!" << endl;
    printBoard();

    bool isPlayerX = true;
    int totalMoves = 0;
    int moveIndex = 0;

    while (totalMoves < BOARD_SIZE * BOARD_SIZE) {
        cout << (isPlayerX ? "Player X" : "Player O") << ", enter your move (1-9):" << endl;

        if (moveIndex >= moves.size()) {
            cout << "No more moves provided." << endl;
            break;
        }

        int currentMove = moves[moveIndex++];
        if (!isValidMove(currentMove)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        makeMove(currentMove, isPlayerX);
        printBoard();
        totalMoves++;

        if (checkWin(isPlayerX)) {
            cout << (isPlayerX ? "Player X" : "Player O") << " wins!" << endl;
            return 0;
        }

        isPlayerX = !isPlayerX;
    }

    cout << "It's a draw!" << endl;
    return 0;
}
