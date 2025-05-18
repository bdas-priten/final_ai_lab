#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

struct Edge {
    string to;
    int cost;
    Edge(string t, int c) : to(t), cost(c) {}
};

struct Node {
    string name;
    int h; // heuristic value
    Node* parent;
    string parentName;
    
    Node(string n, int heuristic, Node* p, string pName)
        : name(n), h(heuristic), parent(p), parentName(pName) {}
};

// Comparator for priority queue to get min heuristic node first
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->h > b->h;
    }
};

void printPath(Node* node, unordered_map<string, vector<Edge>>& graph) {
    vector<Node*> path;
    for (Node* cur = node; cur != nullptr; cur = cur->parent) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << "Path with edges and costs:\n";
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        string from = path[i]->name;
        string to = path[i + 1]->name;
        // find edge cost from 'from' to 'to'
        int cost = 0;
        for (auto& edge : graph[from]) {
            if (edge.to == to) {
                cost = edge.cost;
                break;
            }
        }
        cout << from << " -> " << to << " (cost: " << cost << ")\n";
    }
}

void bestFirstSearch(unordered_map<string, vector<Edge>>& graph,
                     unordered_map<string, int>& heuristic,
                     const string& start, const string& goal) {
    priority_queue<Node*, vector<Node*>, CompareNode> open;
    unordered_set<string> visited;

    open.push(new Node(start, heuristic[start], nullptr, ""));

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (visited.find(current->name) != visited.end()) {
            delete current;
            continue;
        }

        visited.insert(current->name);

        if (current->name == goal) {
            printPath(current, graph);
            // Clean up nodes in open queue (optional, for memory safety)
            while (!open.empty()) {
                delete open.top();
                open.pop();
            }
            delete current;
            return;
        }

        for (auto& edge : graph[current->name]) {
            if (visited.find(edge.to) == visited.end()) {
                open.push(new Node(edge.to, heuristic[edge.to], current, current->name));
            }
        }
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
    graph["G"] = {}; // goal node

    unordered_map<string, int> heuristic = {
        {"A", 7}, {"B", 6}, {"C", 5},
        {"D", 4}, {"E", 3}, {"F", 6},
        {"G", 0}
    };

    bestFirstSearch(graph, heuristic, "A", "G");

    return 0;
}
