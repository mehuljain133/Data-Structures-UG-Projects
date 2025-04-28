/* WAP to implement Diagonal Matrix using one-dimensional array.
WAP to implement Lower Triangular Matrix using one-dimensional array.
WAP to implement Upper Triangular Matrix using one-dimensional array.
WAP to implement Symmetric Matrix using one-dimensional array */

#include <iostream>
#include <vector>
using namespace std;

// Class for different types of matrices
class Matrix {
public:
    // Function to store and print a Diagonal Matrix using 1D array
    static void diagonalMatrix(int n) {
        vector<int> arr(n); // One-dimensional array to store diagonal elements
        cout << "Enter " << n << " diagonal elements: ";
        for (int i = 0; i < n; ++i) {
            cin >> arr[i]; // Input diagonal elements
        }

        cout << "\nDiagonal Matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    cout << arr[i] << " "; // Diagonal elements
                } else {
                    cout << "0 "; // Non-diagonal elements are zero
                }
            }
            cout << endl;
        }
    }

    // Function to store and print a Lower Triangular Matrix using 1D array
    static void lowerTriangularMatrix(int n) {
        vector<int> arr((n * (n + 1)) / 2); // Array to store lower triangular elements
        cout << "Enter " << (n * (n + 1)) / 2 << " lower triangular elements: ";
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                cin >> arr[k++]; // Input elements
            }
        }

        cout << "\nLower Triangular Matrix:\n";
        k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i >= j) {
                    cout << arr[k++] << " "; // Lower triangular elements
                } else {
                    cout << "0 "; // Above diagonal elements are zero
                }
            }
            cout << endl;
        }
    }

    // Function to store and print an Upper Triangular Matrix using 1D array
    static void upperTriangularMatrix(int n) {
        vector<int> arr((n * (n + 1)) / 2); // Array to store upper triangular elements
        cout << "Enter " << (n * (n + 1)) / 2 << " upper triangular elements: ";
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                cin >> arr[k++]; // Input elements
            }
        }

        cout << "\nUpper Triangular Matrix:\n";
        k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i <= j) {
                    cout << arr[k++] << " "; // Upper triangular elements
                } else {
                    cout << "0 "; // Below diagonal elements are zero
                }
            }
            cout << endl;
        }
    }

    // Function to store and print a Symmetric Matrix using 1D array
    static void symmetricMatrix(int n) {
        vector<int> arr((n * (n + 1)) / 2); // Array to store symmetric matrix elements
        cout << "Enter " << (n * (n + 1)) / 2 << " elements (including the upper triangle): ";
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                cin >> arr[k++]; // Input upper triangular elements
            }
        }

        cout << "\nSymmetric Matrix:\n";
        k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i <= j) {
                    cout << arr[k++] << " "; // Upper triangular elements
                } else {
                    cout << arr[(j * (j + 1)) / 2 + i] << " "; // Symmetric elements
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int choice, size;

    cout << "Enter the size of the square matrix: ";
    cin >> size;

    cout << "\nChoose the type of matrix:\n";
    cout << "1. Diagonal Matrix\n";
    cout << "2. Lower Triangular Matrix\n";
    cout << "3. Upper Triangular Matrix\n";
    cout << "4. Symmetric Matrix\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            Matrix::diagonalMatrix(size);
            break;
        case 2:
            Matrix::lowerTriangularMatrix(size);
            break;
        case 3:
            Matrix::upperTriangularMatrix(size);
            break;
        case 4:
            Matrix::symmetricMatrix(size);
            break;
        default:
            cout << "Invalid choice!";
    }

    return 0;
}
