#include <iostream>
#include <vector>
using namespace std;

int V, M; // Number of vertices and colors
vector<vector<int>> adjList;
vector<int> colors;

bool isSafe(int vertex, int color) {
    for (int neighbor : adjList[vertex]) {
        if (colors[neighbor] == color)
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
        cout << "Vertex " << i << " ---> Color " << colors[i] << "\n";
    }
}

int main() {
    int E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter number of colors: ";
    cin >> M;

    adjList.resize(V);
    colors.resize(V, 0);

    cout << "Enter " << E << " edges (u v) one per line:\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since graph is undirected
    }

    if (solve(0)) {
        printSolution();
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}



/*

Enter number of vertices: 8
Enter number of edges: 12
Enter number of colors: 3
Enter 12 edges (u v) one per line:
0 1  
0 2  
1 2
1 3
2 3
3 4
4 5
4 6
5 6
5 7
6 7
2 6



*/
