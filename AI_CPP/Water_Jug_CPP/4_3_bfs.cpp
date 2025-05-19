#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct WaterJugState {
    int jugA, jugB;
    WaterJugState() : jugA(0), jugB(0) {}
    WaterJugState(int a, int b) : jugA(a), jugB(b) {}

    bool operator==(const WaterJugState& other) const {
        return jugA == other.jugA && jugB == other.jugB;
    }
};

struct WaterJugStateHash {
    size_t operator()(const WaterJugState& s) const {
        return hash<int>()(s.jugA) ^ (hash<int>()(s.jugB) << 1);
    }
};

vector<WaterJugState> generateNextStates(const WaterJugState& current, int capA, int capB) {
    vector<WaterJugState> states;
    int a = current.jugA;
    int b = current.jugB;

    // Fill jugs
    states.emplace_back(capA, b);
    states.emplace_back(a, capB);

    // Empty jugs
    states.emplace_back(0, b);
    states.emplace_back(a, 0);

    // Pour from A to B
    int pourAtoB = min(a, capB - b);
    states.emplace_back(a - pourAtoB, b + pourAtoB);

    // Pour from B to A
    int pourBtoA = min(b, capA - a);
    states.emplace_back(a + pourBtoA, b - pourBtoA);

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

    cout << "\nSolution path:\n";
    for (const auto& state : path) {
        cout << "(" << state.jugA << ", " << state.jugB << ")\n";
    }
}

void solveWaterJugBFS(int capA, int capB, int target) {
    queue<WaterJugState> q;
    unordered_set<WaterJugState, WaterJugStateHash> visited;
    unordered_map<WaterJugState, WaterJugState, WaterJugStateHash> parent;

    WaterJugState start(0, 0);
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        WaterJugState current = q.front();
        q.pop();

        if (current.jugA == target || current.jugB == target) {
            printPath(current, parent);
            return;
        }

        vector<WaterJugState> nextStates = generateNextStates(current, capA, capB);

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
    int capA, capB, target;
    cout << "Enter capacity of Jug A: ";
    cin >> capA;
    cout << "Enter capacity of Jug B: ";
    cin >> capB;
    cout << "Enter target amount of water: ";
    cin >> target;

    if (target > max(capA, capB)) {
        cout << "Target cannot be more than jug capacities.\n";
    } else {
        solveWaterJugBFS(capA, capB, target);
    }

    return 0;
}


/*

4
3
2

*/
