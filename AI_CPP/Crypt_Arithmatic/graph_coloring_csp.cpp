#include <iostream>
#include <vector>
using namespace std;

const int V = 4; // Number of vertices
const int M = 3; // Number of colors
vector<vector<int>> adjList(V);
int colors[V] = {0};

void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // Undirected graph
}

bool isSafe(int vertex, int c) {
    for (int neighbor : adjList[vertex]) {
        if (colors[neighbor] == c)
            return false;
    }
    return true;
}

bool solve(int vertex) {
    if (vertex == V)
        return true;

    for (int c = 1; c <= M; c++) {
        if (isSafe(vertex, c)) {
            colors[vertex] = c;
            if (solve(vertex + 1))
                return true;
            colors[vertex] = 0; // Backtrack
        }
    }

    return false;
}

void printSolution() {
    cout << "Coloring is possible with " << M << " colors:\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " ---> Color " << colors[i] << endl;
    }
}

int main() {
    // Initialize graph
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 3);

    if (solve(0))
        printSolution();
    else
        cout << "No solution exists.\n";

    return 0;
}
