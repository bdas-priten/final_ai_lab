#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct WaterJugState {
    int jug4, jug3;
    WaterJugState() : jug4(0), jug3(0) {}  // Default constructor added
    WaterJugState(int a, int b) : jug4(a), jug3(b) {}

    bool operator==(const WaterJugState& other) const {
        return jug4 == other.jug4 && jug3 == other.jug3;
    }
};

// Custom hash function for WaterJugState to be used in unordered_set and unordered_map
struct WaterJugStateHash {
    size_t operator()(const WaterJugState& s) const {
        return hash<int>()(s.jug4) ^ (hash<int>()(s.jug3) << 1);
    }
};

vector<WaterJugState> generateNextStates(const WaterJugState& current, int cap4, int cap3) {
    vector<WaterJugState> states;
    int a = current.jug4;
    int b = current.jug3;

    // Fill jugs
    states.emplace_back(cap4, b); // Fill 4-gallon
    states.emplace_back(a, cap3); // Fill 3-gallon

    // Empty jugs
    states.emplace_back(0, b); // Empty 4-gallon
    states.emplace_back(a, 0); // Empty 3-gallon

    // Pour from 4 to 3
    int pour4to3 = min(a, cap3 - b);
    states.emplace_back(a - pour4to3, b + pour4to3);

    // Pour from 3 to 4
    int pour3to4 = min(b, cap4 - a);
    states.emplace_back(a + pour3to4, b - pour3to4);

    return states;
}

void printPath(const WaterJugState& goal, unordered_map<WaterJugState, WaterJugState, WaterJugStateHash>& parent) {
    vector<WaterJugState> path;
    WaterJugState current = goal;

    while (true) {
        path.push_back(current);
        auto it = parent.find(current);
        if (it == parent.end()) break;
        current = it->second;
    }

    reverse(path.begin(), path.end());

    cout << "Solution path to get 2 gallons in the 4-gallon jug:\n";
    for (const auto& state : path) {
        cout << "(" << state.jug4 << ", " << state.jug3 << ")\n";
    }
}

void solveWaterJugBFS() {
    int jug4Capacity = 4;
    int jug3Capacity = 3;
    int goal = 2;

    queue<WaterJugState> q;
    unordered_set<WaterJugState, WaterJugStateHash> visited;
    unordered_map<WaterJugState, WaterJugState, WaterJugStateHash> parent;

    WaterJugState start(0, 0);
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        WaterJugState current = q.front();
        q.pop();

        if (current.jug4 == goal) {
            printPath(current, parent);
            return;
        }

        vector<WaterJugState> nextStates = generateNextStates(current, jug4Capacity, jug3Capacity);

        for (const WaterJugState& next : nextStates) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                parent[next] = current;
                q.push(next);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    solveWaterJugBFS();
    return 0;
}
