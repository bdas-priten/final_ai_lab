#include <bits/stdc++.h>
using namespace std;

struct PuzzleState {
    vector<vector<int>> board;
    int zero_r, zero_c;      // position of the empty tile (0)
    int depth;
    vector<string> path;     // store moves leading here (optional)

    PuzzleState(vector<vector<int>> b, int d = 0, vector<string> p = {})
        : board(b), depth(d), path(p) {
        // find zero position
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == 0) {
                    zero_r = i;
                    zero_c = j;
                }
    }

    bool isGoal() const {
        int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != goal[i][j]) return false;
        return true;
    }

    // convert board to string to use as visited key
    string boardToString() const {
        string s;
        for (auto &row : board)
            for (int x : row)
                s += to_string(x) + ",";
        return s;
    }

    // generate next states by sliding the zero tile
    vector<PuzzleState> generateNextStates() const {
        vector<PuzzleState> nextStates;
        vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
        vector<string> moves = {"Up", "Down", "Left", "Right"};

        for (int i = 0; i < 4; i++) {
            int new_r = zero_r + directions[i].first;
            int new_c = zero_c + directions[i].second;
            if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[zero_r][zero_c], newBoard[new_r][new_c]);
                vector<string> newPath = path;
                newPath.push_back(moves[i]);
                nextStates.emplace_back(newBoard, depth+1, newPath);
            }
        }
        return nextStates;
    }

    void printBoard() const {
        for (auto &row : board) {
            for (int x : row) cout << x << " ";
            cout << "\n";
        }
        cout << "\n";
    }
};

bool dfs(PuzzleState state, int maxDepth, unordered_set<string> &visited) {
    if (state.isGoal()) {
        cout << "Goal reached in " << state.depth << " moves.\n";
        cout << "Moves:\n";
        for (auto &move : state.path)
            cout << move << " ";
        cout << "\n\nSolution Path:\n";
        state.printBoard();
        return true;
    }

    if (state.depth >= maxDepth) return false;

    visited.insert(state.boardToString());

    for (auto &nextState : state.generateNextStates()) {
        if (visited.find(nextState.boardToString()) == visited.end()) {
            if (dfs(nextState, maxDepth, visited))
                return true;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> startBoard(3, vector<int>(3));

    cout << "Enter the 8-puzzle board (3x3) using 0 for blank:\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> startBoard[i][j];

    PuzzleState start(startBoard);
    unordered_set<string> visited;
    int maxDepth = 20; // adjust depth limit for search

    if (!dfs(start, maxDepth, visited)) {
        cout << "No solution found within depth limit " << maxDepth << ".\n";
    }

    return 0;
}
