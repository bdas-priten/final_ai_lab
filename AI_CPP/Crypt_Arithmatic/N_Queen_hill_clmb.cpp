#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int N;

// Board state: `board[col] = row` means queen in column `col` at row `board[col]`
vector<int> board;

// Function to calculate number of pairs of queens attacking each other
int calculateConflicts(const vector<int>& state) {
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (state[i] == state[j] ||                // Same row
                abs(state[i] - state[j]) == j - i) {   // Same diagonal
                conflicts++;
            }
        }
    }
    return conflicts;
}

// Hill Climbing algorithm to reduce conflicts
bool hillClimbing() {
    while (true) {
        int currentConflicts = calculateConflicts(board);
        if (currentConflicts == 0) {
            return true;  // solution found
        }

        int bestConflicts = currentConflicts;
        int bestCol = -1, bestRow = -1;

        // For each column, try moving the queen to every possible row to find best move
        for (int col = 0; col < N; col++) {
            int originalRow = board[col];
            for (int row = 0; row < N; row++) {
                if (row == originalRow) continue;

                board[col] = row;
                int conflicts = calculateConflicts(board);

                if (conflicts < bestConflicts) {
                    bestConflicts = conflicts;
                    bestCol = col;
                    bestRow = row;
                }
            }
            board[col] = originalRow;  // revert
        }

        if (bestConflicts == currentConflicts) {
            // No better move found - stuck at local minima
            return false;
        }

        // Make the best move
        board[bestCol] = bestRow;
    }
}

void printBoard() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[col] == row)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "Enter number of queens (N): ";
    cin >> N;

    srand(time(0));

    // Initialize board with random positions
    board.resize(N);
    for (int i = 0; i < N; i++) {
        board[i] = rand() % N;
    }

    cout << "Initial board (random):\n";
    printBoard();

    // Try hill climbing with random restarts
    int attempts = 0;
    const int maxAttempts = 1000;
    bool solved = false;
    while (attempts < maxAttempts) {
        if (hillClimbing()) {
            solved = true;
            break;
        }
        // Restart with a new random board if stuck
        for (int i = 0; i < N; i++) {
            board[i] = rand() % N;
        }
        attempts++;
    }

    if (solved) {
        cout << "\nSolution found:\n";
        printBoard();
    } else {
        cout << "\nFailed to find solution after " << maxAttempts << " attempts.\n";
    }

    return 0;
}
