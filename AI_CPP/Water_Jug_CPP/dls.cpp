#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct WaterJugState {
    int jug4, jug3;

    WaterJugState(int a = 0, int b = 0) : jug4(a), jug3(b) {}

    bool operator==(const WaterJugState& other) const {
        return jug4 == other.jug4 && jug3 == other.jug3;
    }

    friend ostream& operator<<(ostream& os, const WaterJugState& s) {
        os << "(" << s.jug4 << ", " << s.jug3 << ")";
        return os;
    }
};

struct WaterJugStateHash {
    size_t operator()(const WaterJugState& s) const {
        return hash<int>()(s.jug4) ^ (hash<int>()(s.jug3) << 1);
    }
};

vector<WaterJugState> generateNextStates(const WaterJugState& current, int cap4, int cap3) {
    vector<WaterJugState> states;
    int a = current.jug4;
    int b = current.jug3;

    // Fill
    states.emplace_back(cap4, b);
    states.emplace_back(a, cap3);

    // Empty
    states.emplace_back(0, b);
    states.emplace_back(a, 0);

    // Pour from 4 to 3
    int pour4to3 = min(a, cap3 - b);
    states.emplace_back(a - pour4to3, b + pour4to3);

    // Pour from 3 to 4
    int pour3to4 = min(b, cap4 - a);
    states.emplace_back(a + pour3to4, b - pour3to4);

    return states;
}

const int MAX_DEPTH = 15;
vector<WaterJugState> path;
unordered_set<WaterJugState, WaterJugStateHash> visited;

bool dls(const WaterJugState& current, int goal, int cap4, int cap3, int depth) {
    if (depth > MAX_DEPTH) return false;
    if (current.jug4 == goal) {
        path.push_back(current);
        return true;
    }

    visited.insert(current);

    vector<WaterJugState> nextStates = generateNextStates(current, cap4, cap3);
    for (const WaterJugState& next : nextStates) {
        if (visited.find(next) == visited.end()) {
            if (dls(next, goal, cap4, cap3, depth + 1)) {
                path.push_back(current);
                return true;
            }
        }
    }

    return false;
}

int main() {
    WaterJugState start(0, 0);
    int goal = 2;

    bool found = dls(start, goal, 4, 3, 0);

    if (found) {
        reverse(path.begin(), path.end());
        cout << "Solution path (Depth-Limited Search):\n";
        for (const auto& state : path) {
            cout << state << "\n";
        }
    } else {
        cout << "No solution found within depth limit.\n";
    }

    return 0;
}
