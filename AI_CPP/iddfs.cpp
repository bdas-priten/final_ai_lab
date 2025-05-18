#include <iostream>
#include <vector>
using namespace std;

// Depth-Limited DFS
bool DLS(vector<vector<int>>& graph, int current, int target, int limit, vector<bool>& visited) {
    if (current == target) {
        cout << "Found target " << target << " at depth " << limit << endl;
        return true;
    }

    if (limit <= 0) return false;

    visited[current] = true;
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (DLS(graph, neighbor, target, limit - 1, visited))
                return true;
        }
    }
    return false;
}

// IDDFS wrapper
bool IDDFS(vector<vector<int>>& graph, int start, int target, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<bool> visited(graph.size(), false);
        cout << "Searching at depth " << depth << "...\n";
        if (DLS(graph, start, target, depth, visited))
            return true;
    }
    return false;
}

int main() {
    int V = 7; // Number of vertices
    vector<vector<int>> graph(V);

    // Sample undirected graph
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5, 6};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};
    graph[6] = {2};

    int start = 0;
    int target = 6;
    int maxDepth = 3;

    cout << "IDDFS Search from " << start << " to " << target << " with max depth " << maxDepth << ":\n\n";

    if (!IDDFS(graph, start, target, maxDepth))
        cout << "Target not found within depth limit.\n";

    return 0;
}
