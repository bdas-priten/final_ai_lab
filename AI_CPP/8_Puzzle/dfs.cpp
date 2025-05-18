#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

const int N = 3;
const int MAX_DEPTH = 30;

struct PuzzleState {
    vector<vector<int>> board;
    PuzzleState* parent;
    int x, y;

    PuzzleState(vector<vector<int>> b, PuzzleState* p) : board(b), parent(p) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] == 0) {
                    x = i;
                    y = j;
                }
    }

    string toString() const {
        string s;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                s += to_string(board[i][j]);
        return s;
    }

    bool isGoal() const {
        int val = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (i == N - 1 && j == N - 1) return board[i][j] == 0;
                else if (board[i][j] != val++) return false;
        return true;
    }

    void printBoard() const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << "-----" << endl;
    }

    vector<PuzzleState*> generateNextStates() const {
        vector<PuzzleState*> states;
        vector<pair<int, int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};
        for (auto [dx, dy] : moves) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[x][y], newBoard[nx][ny]);
                states.push_back(new PuzzleState(newBoard, const_cast<PuzzleState*>(this)));
            }
        }
        return states;
    }
};

void printPath(PuzzleState* goal) {
    vector<PuzzleState*> path;
    while (goal != nullptr) {
        path.push_back(goal);
        goal = goal->parent;
    }
    reverse(path.begin(), path.end());
    cout << "Solution path (DFS):\n";
    for (auto& state : path) {
        state->printBoard();
    }
}

void dfs(PuzzleState* start) {
    stack<pair<PuzzleState*, int>> stk;
    set<string> visited;

    stk.push({start, 0});
    visited.insert(start->toString());

    while (!stk.empty()) {
        auto [current, depth] = stk.top();
        stk.pop();

        if (current->isGoal()) {
            printPath(current);
            return;
        }

        if (depth > MAX_DEPTH) continue;

        vector<PuzzleState*> nextStates = current->generateNextStates();
        for (auto& next : nextStates) {
            string key = next->toString();
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                stk.push({next, depth + 1});
            } else {
                delete next;
            }
        }
    }

    cout << "No solution found within depth limit." << endl;
}

int main() {
    vector<vector<int>> board(3, vector<int>(3));
    cout << "Enter the 8-puzzle board (3x3) using 0 for the blank:\n";
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cin >> board[i][j];

    PuzzleState* start = new PuzzleState(board, nullptr);
    dfs(start);
    return 0;
}
