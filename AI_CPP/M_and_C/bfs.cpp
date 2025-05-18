#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct State {
    int missionariesLeft;
    int cannibalsLeft;
    bool boatLeft;
    State* parent;

    State(int m, int c, bool boat, State* p = nullptr)
        : missionariesLeft(m), cannibalsLeft(c), boatLeft(boat), parent(p) {}

    bool isValid() const {
        int missionariesRight = 3 - missionariesLeft;
        int cannibalsRight = 3 - cannibalsLeft;

        if (missionariesLeft < 0 || cannibalsLeft < 0 ||
            missionariesLeft > 3 || cannibalsLeft > 3)
            return false;

        if (missionariesLeft > 0 && missionariesLeft < cannibalsLeft)
            return false;

        if (missionariesRight > 0 && missionariesRight < cannibalsRight)
            return false;

        return true;
    }

    bool isGoal() const {
        return missionariesLeft == 0 && cannibalsLeft == 0 && !boatLeft;
    }

    bool operator<(const State& other) const {
        if (missionariesLeft != other.missionariesLeft)
            return missionariesLeft < other.missionariesLeft;
        if (cannibalsLeft != other.cannibalsLeft)
            return cannibalsLeft < other.cannibalsLeft;
        return boatLeft < other.boatLeft;
    }

    void print() const {
        cout << "Left Bank -> M: " << missionariesLeft << ", C: " << cannibalsLeft
             << ", Boat: " << (boatLeft ? "Left" : "Right") << endl;
    }
};

vector<State> generateSuccessors(const State& current) {
    vector<State> successors;
    int direction = current.boatLeft ? -1 : 1;

    int moves[5][2] = {
        {1, 0}, {2, 0},  // one or two missionaries
        {0, 1}, {0, 2},  // one or two cannibals
        {1, 1}           // one missionary and one cannibal
    };

    for (auto& move : moves) {
        int newM = current.missionariesLeft + direction * move[0];
        int newC = current.cannibalsLeft + direction * move[1];
        bool newBoat = !current.boatLeft;

        State nextState(newM, newC, newBoat, nullptr);
        if (nextState.isValid()) {
            successors.push_back(nextState);
        }
    }
    return successors;
}

void printSolution(State* goal) {
    vector<State*> path;
    State* current = goal;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    reverse(path.begin(), path.end());

    cout << "Solution path:" << endl;
    for (auto s : path) {
        s->print();
    }
}

void bfs() {
    State* start = new State(3, 3, true, nullptr);
    queue<State*> q;
    set<State> visited;

    q.push(start);
    visited.insert(*start);

    while (!q.empty()) {
        State* current = q.front();
        q.pop();

        if (current->isGoal()) {
            printSolution(current);
            return;
        }

        vector<State> successors = generateSuccessors(*current);
        for (auto& next : successors) {
            if (visited.find(next) == visited.end()) {
                State* nextState = new State(next.missionariesLeft, next.cannibalsLeft, next.boatLeft, current);
                visited.insert(*nextState);
                q.push(nextState);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    bfs();
    return 0;
}
