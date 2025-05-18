#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct State {
    int missionariesLeft, cannibalsLeft;
    bool boatLeft;
    State() : missionariesLeft(0), cannibalsLeft(0), boatLeft(false) {}

    State(int m, int c, bool b) : missionariesLeft(m), cannibalsLeft(c), boatLeft(b) {}

    bool isGoal() const {
        return missionariesLeft == 0 && cannibalsLeft == 0 && !boatLeft;
    }

    bool isValid() const {
        int missionariesRight = 3 - missionariesLeft;
        int cannibalsRight = 3 - cannibalsLeft;

        if (missionariesLeft < 0 || cannibalsLeft < 0 || missionariesRight < 0 || cannibalsRight < 0)
            return false;
        if ((missionariesLeft > 0 && missionariesLeft < cannibalsLeft) ||
            (missionariesRight > 0 && missionariesRight < cannibalsRight))
            return false;
        return true;
    }

    bool operator==(const State& other) const {
        return missionariesLeft == other.missionariesLeft &&
               cannibalsLeft == other.cannibalsLeft &&
               boatLeft == other.boatLeft;
    }

    // For printing
    void print() const {
        cout << "(" << missionariesLeft << "M, " << cannibalsLeft << "C, Boat " 
             << (boatLeft ? "Left" : "Right") << ")" << endl;
    }
};

// Hash function for unordered_set/map with State keys
struct StateHasher {
    size_t operator()(const State& s) const {
        return hash<int>()(s.missionariesLeft) ^ (hash<int>()(s.cannibalsLeft) << 1) ^ (hash<bool>()(s.boatLeft) << 2);
    }
};

struct StateWithDepth {
    State state;
    int depth;

    StateWithDepth(State s, int d) : state(s), depth(d) {}
};

vector<State> generateSuccessors(const State& current) {
    vector<State> successors;
    int dir = current.boatLeft ? -1 : 1;

    int moves[5][2] = {
        {1, 0}, {2, 0},  // missionaries
        {0, 1}, {0, 2},  // cannibals
        {1, 1}           // one of each
    };

    for (auto& move : moves) {
        int newM = current.missionariesLeft + dir * move[0];
        int newC = current.cannibalsLeft + dir * move[1];
        bool newBoat = !current.boatLeft;

        State next(newM, newC, newBoat);
        if (next.isValid()) {
            successors.push_back(next);
        }
    }
    return successors;
}

void printPath(const State& goal, unordered_map<State, State, StateHasher>& parent) {
    vector<State> path;
    State current = goal;

    // Because start has no parent, loop until current is not found in parent
    while (true) {
        path.push_back(current);
        auto it = parent.find(current);
        if (it == parent.end()) break;
        current = it->second;
    }

    reverse(path.begin(), path.end());

    cout << "Solution path (Stack-based DLS):" << endl;
    for (const State& s : path) {
        s.print();
    }
}

int main() {
    const int maxDepth = 20;

    State start(3, 3, true);
    stack<StateWithDepth> stack;
    unordered_set<State, StateHasher> visited;
    unordered_map<State, State, StateHasher> parent;

    stack.push(StateWithDepth(start, 0));
    visited.insert(start);

    while (!stack.empty()) {
        StateWithDepth currentWD = stack.top();
        stack.pop();

        State current = currentWD.state;
        int depth = currentWD.depth;

        if (current.isGoal()) {
            printPath(current, parent);
            return 0;
        }

        if (depth >= maxDepth) continue;

        vector<State> successors = generateSuccessors(current);
        for (State& next : successors) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                parent[next] = current;
                stack.push(StateWithDepth(next, depth + 1));
            }
        }
    }

    cout << "No solution found within depth limit." << endl;
    return 0;
}
