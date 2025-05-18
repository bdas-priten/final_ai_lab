#include <iostream>
#include <vector>
using namespace std;

// Depth-Limited Search (DLS)
bool DLS(vector<vector<int>>& graph, int current, int target, int limit, vector<bool>& visited) {
    if (current == target) {
        cout << "Found target " << target << " at depth limit " << limit << "\n";
        return true;
    }

    if (limit == 0) return false;

    visited[current] = true;
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (DLS(graph, neighbor, target, limit - 1, visited))
                return true;
        }
    }
    return false;
}

// Iterative Deepening DFS
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
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter " << E << " edges (as pairs u v, 0-indexed):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // If undirected graph
    }

    int start, target, maxDepth;
    cout << "Enter start node: ";
    cin >> start;

    cout << "Enter target node: ";
    cin >> target;

    cout << "Enter maximum depth: ";
    cin >> maxDepth;

    cout << "\nRunning IDDFS...\n\n";

    if (!IDDFS(graph, start, target, maxDepth))
        cout << "\nTarget not found within depth limit.\n";

    return 0;
}
