#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int N = 3; // 3x3 puzzle
const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

struct PuzzleState {
    vector<vector<int>> board;
    PuzzleState* parent;

    PuzzleState(vector<vector<int>> b, PuzzleState* p = nullptr) : board(b), parent(p) {}

    string toString() const {
        string s;
        for (const auto& row : board)
            for (int val : row)
                s += to_string(val);
        return s;
    }

    bool isGoal() const {
        return board == goal;
    }

    void printBoard() const {
        for (const auto& row : board) {
            for (int val : row)
                cout << val << " ";
            cout << endl;
        }
        cout << endl;
    }

    vector<PuzzleState*> generateNextStates() const {
        vector<PuzzleState*> nextStates;
        int x, y;
        // Find the blank (0) position
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] == 0) {
                    x = i;
                    y = j;
                }

        // Possible directions: up, down, left, right
        vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[x][y], newBoard[newX][newY]);
                nextStates.push_back(new PuzzleState(newBoard, const_cast<PuzzleState*>(this)));
            }
        }

        return nextStates;
    }
};

void printPath(PuzzleState* state) {
    vector<PuzzleState*> path;
    while (state) {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());
    cout << "Solution path (BFS):" << endl;
    for (const auto& s : path)
        s->printBoard();
}

void bfs(PuzzleState* start) {
    queue<PuzzleState*> q;
    set<string> visited;

    q.push(start);
    visited.insert(start->toString());

    while (!q.empty()) {
        PuzzleState* current = q.front();
        q.pop();

        if (current->isGoal()) {
            printPath(current);
            return;
        }

        vector<PuzzleState*> nextStates = current->generateNextStates();
        for (auto& next : nextStates) {
            string key = next->toString();
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                q.push(next);
            } else {
                delete next; // Avoid memory leak
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> startBoard(N, vector<int>(N));
    cout << "Enter the 8-puzzle board (3x3) using 0 for the blank:" << endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> startBoard[i][j];

    PuzzleState* start = new PuzzleState(startBoard);
    bfs(start);

    // Cleanup dynamically allocated memory
    delete start;

    return 0;
}
