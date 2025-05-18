#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random
using namespace std;

// Objective function: we want to maximize this
double objectiveFunction(double x) {
    return -x * x + 10 * x;
}

int main() {
    srand(time(0)); // Random seed

    double current = rand() % 10;  // Start from a random point in [0,10)
    double stepSize = 0.1;
    int iterations = 100;

    cout << "Initial x: " << current << ", f(x): " << objectiveFunction(current) << "\n";

    for (int i = 0; i < iterations; i++) {
        double next1 = current + stepSize;
        double next2 = current - stepSize;

        double f_current = objectiveFunction(current);
        double f_next1 = objectiveFunction(next1);
        double f_next2 = objectiveFunction(next2);

        if (f_next1 > f_current)
            current = next1;
        else if (f_next2 > f_current)
            current = next2;
        else
            break;  // No improvement

        cout << "Iteration " << i+1 << ": x = " << current << ", f(x) = " << objectiveFunction(current) << "\n";
    }

    cout << "\nFinal solution: x = " << current << ", f(x) = " << objectiveFunction(current) << "\n";

    return 0;
}
