#include <bits/stdc++.h>
using namespace std;

struct PuzzleState {
    vector<vector<int>> board;
    int g;  // cost so far (number of moves)
    int h;  // heuristic estimate (Manhattan distance)
    int f;  // g + h
    string boardStr;  // string representation for hashing
    shared_ptr<PuzzleState> parent;

    PuzzleState(const vector<vector<int>> &b, int gCost, shared_ptr<PuzzleState> p)
        : board(b), g(gCost), parent(p) {
        h = manhattanDistance();
        f = g + h;
        boardStr = boardToString();
    }

    // Compute Manhattan distance heuristic
    int manhattanDistance() const {
        int dist = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = board[i][j];
                if (val != 0) {
                    int targetX = (val - 1) / 3;
                    int targetY = (val - 1) % 3;
                    dist += abs(i - targetX) + abs(j - targetY);
                }
            }
        }
        return dist;
    }

    // Check if board is goal state
    bool isGoal() const {
        int expected = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == 2 && j == 2) {
                    if (board[i][j] != 0) return false;
                } else if (board[i][j] != expected) {
                    return false;
                }
                expected++;
            }
        }
        return true;
    }

    // Convert board to a string for hashing/comparison
    string boardToString() const {
        string s;
        for (auto &row : board)
            for (int val : row)
                s += to_string(val) + ",";
        return s;
    }

    // Generate next states with correct parent pointer
    vector<shared_ptr<PuzzleState>> generateNextStates(shared_ptr<PuzzleState> self) {
        vector<shared_ptr<PuzzleState>> nextStates;
        int x, y;
        // find zero (blank)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        vector<pair<int, int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};
        for (auto [dx, dy] : moves) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[x][y], newBoard[nx][ny]);
                nextStates.push_back(make_shared<PuzzleState>(newBoard, g+1, self));
            }
        }
        return nextStates;
    }

    void printBoard() const {
        for (auto &row : board) {
            for (int val : row)
                cout << val << " ";
            cout << "\n";
        }
        cout << "\n";
    }
};

// For priority queue: states with smaller f have higher priority
struct ComparePuzzleState {
    bool operator()(const shared_ptr<PuzzleState> &a, const shared_ptr<PuzzleState> &b) const {
        return a->f > b->f;
    }
};

void printPath(shared_ptr<PuzzleState> state) {
    vector<shared_ptr<PuzzleState>> path;
    while (state) {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());

    cout << "Solution path (moves = " << path.size() - 1 << "):\n\n";
    for (auto &st : path) {
        st->printBoard();
    }
}

void aStar(const vector<vector<int>> &startBoard) {
    auto start = make_shared<PuzzleState>(startBoard, 0, nullptr);

    priority_queue<shared_ptr<PuzzleState>, vector<shared_ptr<PuzzleState>>, ComparePuzzleState> openSet;
    unordered_set<string> closedSet;

    openSet.push(start);

    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();

        if (current->isGoal()) {
            printPath(current);
            return;
        }

        if (closedSet.count(current->boardStr)) continue;
        closedSet.insert(current->boardStr);

        for (auto &nextState : current->generateNextStates(current)) {
            if (!closedSet.count(nextState->boardStr)) {
                openSet.push(nextState);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    cout << "Enter the 8-puzzle board (3x3) with 0 as blank:\n";
    vector<vector<int>> startBoard(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> startBoard[i][j];

    aStar(startBoard);
    return 0;
}
