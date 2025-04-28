/* WAP to calculate factorial and to compute the factors of a given no. (i)using recursion, (ii)
using iteration */

#include <iostream>
#include <vector>
using namespace std;

// Function to calculate factorial using recursion
int factorialRecursion(int n) {
    if (n == 0 || n == 1) {
        return 1; // Base case: 0! = 1 and 1! = 1
    }
    return n * factorialRecursion(n - 1); // Recursive step
}

// Function to calculate factorial using iteration
int factorialIteration(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i; // Multiply result with i
    }
    return result;
}

// Function to find factors of a number using recursion
void factorsRecursion(int n, int i = 1) {
    if (i > n / 2) {
        if (n > 1) cout << n << " "; // The number itself is a factor (if n > 1)
        return;
    }
    if (n % i == 0) {
        cout << i << " "; // i is a factor of n
    }
    factorsRecursion(n, i + 1); // Recur with next integer
}

// Function to find factors of a number using iteration
void factorsIteration(int n) {
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            cout << i << " "; // i is a factor of n
        }
    }
    if (n > 1) cout << n << " "; // The number itself is a factor (if n > 1)
}

int main() {
    int num;

    // Taking user input
    cout << "Enter a number: ";
    cin >> num;

    // Factorial Calculation
    cout << "\nFactorial (using recursion) of " << num << " is: " << factorialRecursion(num) << endl;
    cout << "Factorial (using iteration) of " << num << " is: " << factorialIteration(num) << endl;

    // Factors Calculation
    cout << "\nFactors (using recursion) of " << num << " are: ";
    factorsRecursion(num);
    cout << endl;

    cout << "Factors (using iteration) of " << num << " are: ";
    factorsIteration(num);
    cout << endl;

    return 0;
}
