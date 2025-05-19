#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct WaterJugState {
    int jugA, jugB;
    WaterJugState(int a = 0, int b = 0) : jugA(a), jugB(b) {}

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

    // Fill
    states.emplace_back(capA, b);
    states.emplace_back(a, capB);

    // Empty
    states.emplace_back(0, b);
    states.emplace_back(a, 0);

    // Pour A -> B
    int pourAtoB = min(a, capB - b);
    states.emplace_back(a - pourAtoB, b + pourAtoB);

    // Pour B -> A
    int pourBtoA = min(b, capA - a);
    states.emplace_back(a + pourBtoA, b - pourBtoA);

    return states;
}

bool dfs(WaterJugState current, int capA, int capB, int goal,
         unordered_set<WaterJugState, WaterJugStateHash>& visited,
         unordered_map<WaterJugState, WaterJugState, WaterJugStateHash>& parent,
         WaterJugState& goalState) {
    
    if (current.jugA == goal || current.jugB == goal) {
        goalState = current;
        return true;
    }

    visited.insert(current);
    for (const auto& next : generateNextStates(current, capA, capB)) {
        if (visited.find(next) == visited.end()) {
            parent[next] = current;
            if (dfs(next, capA, capB, goal, visited, parent, goalState))
                return true;
        }
    }

    return false;
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

    cout << "\nDFS Solution Path:\n";
    for (const auto& state : path) {
        cout << "(" << state.jugA << ", " << state.jugB << ")\n";
    }
}

int main() {
    int capA, capB, goal;
    cout << "Enter capacity of Jug A: ";
    cin >> capA;
    cout << "Enter capacity of Jug B: ";
    cin >> capB;
    cout << "Enter goal amount to be measured: ";
    cin >> goal;

    unordered_set<WaterJugState, WaterJugStateHash> visited;
    unordered_map<WaterJugState, WaterJugState, WaterJugStateHash> parent;
    WaterJugState goalState;

    WaterJugState start(0, 0);
    bool found = dfs(start, capA, capB, goal, visited, parent, goalState);

    if (found) {
        printPath(goalState, parent);
    } else {
        cout << "No solution found using DFS.\n";
    }

    return 0;
}
