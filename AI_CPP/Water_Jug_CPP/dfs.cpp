#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct WaterJugState {
    int jug4, jug3;

    WaterJugState() : jug4(0), jug3(0) {}
    WaterJugState(int a, int b) : jug4(a), jug3(b) {}

    bool operator==(const WaterJugState& other) const {
        return jug4 == other.jug4 && jug3 == other.jug3;
    }

    // For printing
    friend ostream& operator<<(ostream& os, const WaterJugState& s) {
        os << "(" << s.jug4 << ", " << s.jug3 << ")";
        return os;
    }
};

// Custom hash function for unordered_set and unordered_map
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
    states.emplace_back(cap4, b);
    states.emplace_back(a, cap3);

    // Empty jugs
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

void solveWaterJugDFS() {
    int cap4 = 4, cap3 = 3, goal = 2;
    WaterJugState start(0, 0);

    stack<WaterJugState> s;
    unordered_set<WaterJugState, WaterJugStateHash> visited;
    unordered_map<WaterJugState, WaterJugState, WaterJugStateHash> parent;

    s.push(start);
    visited.insert(start);

    while (!s.empty()) {
        WaterJugState current = s.top();
        s.pop();

        if (current.jug4 == goal) {
            vector<WaterJugState> path;
            WaterJugState node = current;

            while (true) {
                path.push_back(node);
                auto it = parent.find(node);
                if (it == parent.end()) break;
                node = it->second;
            }

            reverse(path.begin(), path.end());

            cout << "Solution path:\n";
            for (const auto& state : path) {
                cout << state << "\n";
            }
            return;
        }

        for (const auto& next : generateNextStates(current, cap4, cap3)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                parent[next] = current;
                s.push(next);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    solveWaterJugDFS();
    return 0;
}
