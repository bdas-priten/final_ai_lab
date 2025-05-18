#include <iostream>
#include <cmath>
using namespace std;

const int N = 8;
int X[N + 1]; // X[i] stores column position of queen at row i
int solutionCount = 0;
bool solutionFound = false;

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (X[j] == i || abs(X[j] - i) == abs(j - k))
            return false;
    }
    return true;
}

void printSolution() {
    solutionCount++;
    cout << "Solution " << solutionCount << ":\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (X[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
    cout << "------------------------\n";
   // solutionFound = true; for one solution only
}

void NQueens(int k) {
   // if(solutionFound) return; // Stop if a solution is found
    for (int i = 1; i <= N; i++) {
        if (Place(k, i)) {
            X[k] = i;
            if (k == N)
                printSolution();
            else
                NQueens(k + 1);

              //  if (solutionFound) return;  for one solution only
        }
    }
}

int main() {
    cout << "All solutions for " << N << "-Queens problem:\n";
    NQueens(1);
    cout << "Total number of solutions: " << solutionCount << endl;
    return 0;
}
