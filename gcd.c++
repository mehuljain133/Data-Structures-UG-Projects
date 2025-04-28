/*  WAP to calculate GCD of 2 number (i) with recursion (ii) without recursion */

#include <iostream>
using namespace std;

// Function to calculate GCD using recursion (Euclid's algorithm)
int gcdRecursion(int a, int b) {
    if (b == 0) {
        return a; // Base case: gcd(a, 0) is a
    }
    return gcdRecursion(b, a % b); // Recursive case: gcd(b, a % b)
}

// Function to calculate GCD using iteration (Euclid's algorithm)
int gcdIteration(int a, int b) {
    while (b != 0) {
        int temp = a % b;  // Calculate remainder
        a = b;              // Update a to b
        b = temp;           // Update b to remainder
    }
    return a; // When b becomes 0, a contains the GCD
}

int main() {
    int num1, num2;

    // Taking input from the user
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    // GCD Calculation using recursion
    cout << "\nGCD (using recursion) of " << num1 << " and " << num2 << " is: " << gcdRecursion(num1, num2) << endl;

    // GCD Calculation using iteration
    cout << "GCD (using iteration) of " << num1 << " and " << num2 << " is: " << gcdIteration(num1, num2) << endl;

    return 0;
}

