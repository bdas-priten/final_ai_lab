#include <iostream>
#include <cmath>
using namespace std;

int N; // Number of queens and size of the board
int X[20]; // X[i] is the column of the queen in row i (1-based)

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (X[j] == i || abs(X[j] - i) == abs(j - k))
            return false;
    }
    return true;
}

void printSolution() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (X[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

void NQueens(int k) {
    for (int i = 1; i <= N; i++) {
        if (Place(k, i)) {
            X[k] = i;
            if (k == N)
                printSolution();
            else
                NQueens(k + 1);
        }
    }
}

int main() {
    cout << "Enter the value of N (N >= 4): ";
    cin >> N;

    cout << "Solutions for " << N << "-Queens problem:" << endl;
    NQueens(1);

    return 0;
}
