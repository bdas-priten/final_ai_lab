#include <bits/stdc++.h>
using namespace std;

struct Edge {
    string to;
    int cost;
    Edge(string t, int c) : to(t), cost(c) {}
};

struct Node {
    string name;
    int g; // cost from start to current
    int h; // heuristic cost to goal
    Node* parent;

    Node(string n, int g_, int h_, Node* p) : name(n), g(g_), h(h_), parent(p) {}

    int f() const {
        return g + h;
    }
};

// Comparator for priority queue (min-heap by f value)
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

void printPath(Node* node) {
    vector<string> path;
    int totalCost = node->g;

    while (node) {
        path.push_back(node->name);
        node = node->parent;
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal cost: " << totalCost << "\n";
}

void aStarSearch(const unordered_map<string, vector<Edge>>& graph,
                 const unordered_map<string, int>& heuristic,
                 const string& start, const string& goal) {

    priority_queue<Node*, vector<Node*>, CompareNode> open;
    unordered_set<string> closed;

    open.push(new Node(start, 0, heuristic.at(start), nullptr));

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (current->name == goal) {
            printPath(current);
            // Clean memory (optional)
            while (!open.empty()) {
                delete open.top();
                open.pop();
            }
            return;
        }

        if (closed.count(current->name)) {
            delete current;
            continue;
        }
        closed.insert(current->name);

        for (const Edge& edge : graph.at(current->name)) {
            if (!closed.count(edge.to)) {
                int gNew = current->g + edge.cost;
                int hNew = heuristic.at(edge.to);
                open.push(new Node(edge.to, gNew, hNew, current));
            }
        }
        // Note: We do not delete current here as it is used as parent by child nodes
        // In a full implementation, careful memory management or smart pointers are preferred
    }

    cout << "No path found.\n";
}

int main() {
    unordered_map<string, vector<Edge>> graph;
    graph["A"] = {Edge("B", 1), Edge("C", 4)};
    graph["B"] = {Edge("D", 2), Edge("E", 5)};
    graph["C"] = {Edge("F", 3)};
    graph["D"] = {Edge("G", 1)};
    graph["E"] = {Edge("G", 2)};
    graph["F"] = {Edge("G", 5)};
    graph["G"] = {};

    unordered_map<string, int> heuristic = {
        {"A", 7}, {"B", 6}, {"C", 5}, {"D", 4}, {"E", 3}, {"F", 6}, {"G", 0}
    };

    aStarSearch(graph, heuristic, "A", "G");

    return 0;
}
