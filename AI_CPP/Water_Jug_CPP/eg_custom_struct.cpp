#include <iostream>
#include <unordered_set>
#include <functional>

using namespace std;

// Define WaterJugState
struct WaterJugState {
    int jug4;
    int jug3;

    WaterJugState(int a = 0, int b = 0) : jug4(a), jug3(b) {}

    bool operator==(const WaterJugState& other) const {
        return jug4 == other.jug4 && jug3 == other.jug3;
    }

    friend ostream& operator<<(ostream& os, const WaterJugState& state) {
        os << "(" << state.jug4 << ", " << state.jug3 << ")";
        return os;
    }
};

// Hash function for unordered_set/map
struct WaterJugStateHash {
    size_t operator()(const WaterJugState& s) const {
        return hash<int>()(s.jug4) ^ (hash<int>()(s.jug3) << 1);
    }
};

// Main function - required!
int main() {
    unordered_set<WaterJugState, WaterJugStateHash> visited;

    WaterJugState state1(3, 0);
    visited.insert(state1);

    if (visited.count(WaterJugState(3, 0))) {
        cout << "Already visited state: " << state1 << endl;
    } else {
        cout << "State not visited yet." << endl;
    }

    return 0;
}
