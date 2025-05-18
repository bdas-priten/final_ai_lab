#include <bits/stdc++.h>
using namespace std;

struct PuzzleState {
    vector<vector<int>> board;
    int h; // heuristic value (Manhattan distance)
    PuzzleState* parent;

    PuzzleState(vector<vector<int>> b, PuzzleState* p = nullptr) : board(b), parent(p) {
        h = manhattanDistance();
    }

    // Check if goal state
    bool isGoal() const {
        int goal[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != goal[i][j]) return false;
        return true;
    }

    // Manhattan distance heuristic
    int manhattanDistance() const {
        int dist = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = board[i][j];
                if (val != 0) {
                    int goalRow = (val - 1) / 3;
                    int goalCol = (val - 1) % 3;
                    dist += abs(i - goalRow) + abs(j - goalCol);
                }
            }
        }
        return dist;
    }

    // Generate all next possible states by sliding the blank tile
    vector<PuzzleState*> generateNextStates() {
        vector<PuzzleState*> nextStates;
        int blankRow, blankCol;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    blankRow = i;
                    blankCol = j;
                }
            }
        }
        // Possible moves: up, down, left, right
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int d = 0; d < 4; d++) {
            int nr = blankRow + dr[d];
            int nc = blankCol + dc[d];
            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[blankRow][blankCol], newBoard[nr][nc]);
                nextStates.push_back(new PuzzleState(newBoard, this));
            }
        }
        return nextStates;
    }

    // Convert board to string for visited check
    string boardToString() const {
        string s = "";
        for (auto &row : board) {
            for (int v : row)
                s += to_string(v) + ",";
        }
        return s;
    }

    // Print the board state
    void printBoard() const {
        for (auto &row : board) {
            for (int v : row) {
                if (v == 0) cout << " 0 ";
                else cout << v << " ";
            }
            cout << "\n";
        }
        cout << "-----\n";
    }
};

// Comparator for priority queue based on heuristic value (h)
struct CompareHeuristic {
    bool operator()(PuzzleState* a, PuzzleState* b) {
        return a->h > b->h; // min heap by h
    }
};

void printPath(PuzzleState* state) {
    vector<PuzzleState*> path;
    while (state != nullptr) {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());
    cout << "Solution path (Best-First Search):\n";
    for (auto st : path) {
        st->printBoard();
    }
}

void bestFirstSearch(PuzzleState* start) {
    priority_queue<PuzzleState*, vector<PuzzleState*>, CompareHeuristic> open;
    unordered_set<string> visited;

    open.push(start);
    visited.insert(start->boardToString());

    while (!open.empty()) {
        PuzzleState* current = open.top();
        open.pop();

        if (current->isGoal()) {
            printPath(current);
            return;
        }

        for (auto next : current->generateNextStates()) {
            string key = next->boardToString();
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                open.push(next);
            } else {
                delete next; // avoid memory leak
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    cout << "Enter the 8-puzzle board (3x3) with 0 as blank:\n";
    vector<vector<int>> board(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> board[i][j];

    PuzzleState* start = new PuzzleState(board);
    bestFirstSearch(start);

    // Cleanup dynamically allocated states is skipped for brevity
    return 0;
}
