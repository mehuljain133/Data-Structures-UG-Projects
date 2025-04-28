/* . WAP to convert the Sparse Matrix into non-zero form and vice-versa. */

#include <iostream>
#include <vector>
using namespace std;

class SparseMatrix {
private:
    vector<vector<int>> matrix; // Original matrix
    vector<int> values;         // Non-zero values
    vector<int> columnIndices;  // Column indices of non-zero elements
    vector<int> rowPointers;    // Row pointers

public:
    // Constructor to initialize matrix dimensions
    SparseMatrix(int rows, int cols) {
        matrix.resize(rows, vector<int>(cols, 0));
    }

    // Function to fill the matrix with some values (just for demonstration)
    void fillMatrix() {
        // Manually setting some non-zero elements in the matrix
        matrix[0][1] = 5;
        matrix[0][3] = 8;
        matrix[1][2] = 7;
        matrix[2][1] = 9;
        matrix[3][3] = 3;
    }

    // Function to print the original matrix
    void printMatrix() {
        cout << "Original Matrix: \n";
        for (auto& row : matrix) {
            for (auto& element : row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }

    // Convert Sparse Matrix to Non-Zero Form (CSR)
    void convertToNonZeroForm() {
        int rows = matrix.size();
        int cols = matrix[0].size();
        values.clear();
        columnIndices.clear();
        rowPointers.clear();
        
        rowPointers.push_back(0); // Row pointer for row 0

        // Traverse the matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] != 0) {
                    values.push_back(matrix[i][j]);
                    columnIndices.push_back(j);
                }
            }
            rowPointers.push_back(values.size()); // Row pointer for the next row
        }
    }

    // Print Non-Zero Form (CSR)
    void printNonZeroForm() {
        cout << "Non-Zero Form (CSR): \n";
        cout << "Values: ";
        for (int val : values) {
            cout << val << " ";
        }
        cout << endl;

        cout << "Column Indices: ";
        for (int idx : columnIndices) {
            cout << idx << " ";
        }
        cout << endl;

        cout << "Row Pointers: ";
        for (int ptr : rowPointers) {
            cout << ptr << " ";
        }
        cout << endl;
    }

    // Convert Non-Zero Form (CSR) back to Sparse Matrix
    void convertToSparseMatrix() {
        int rows = rowPointers.size() - 1;
        int cols = matrix[0].size();
        matrix.resize(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; ++i) {
            for (int j = rowPointers[i]; j < rowPointers[i + 1]; ++j) {
                matrix[i][columnIndices[j]] = values[j];
            }
        }
    }

    // Print the matrix after conversion from Non-Zero form
    void printConvertedMatrix() {
        cout << "Converted Sparse Matrix: \n";
        for (auto& row : matrix) {
            for (auto& element : row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create a sparse matrix with 4 rows and 5 columns
    SparseMatrix sm(4, 5);

    // Fill the matrix with non-zero elements
    sm.fillMatrix();

    // Print the original matrix
    sm.printMatrix();

    // Convert Sparse Matrix to Non-Zero Form (CSR)
    sm.convertToNonZeroForm();
    
    // Print the Non-Zero Form
    sm.printNonZeroForm();

    // Convert back to Sparse Matrix from Non-Zero Form
    sm.convertToSparseMatrix();

    // Print the converted Sparse Matrix
    sm.printConvertedMatrix();

    return 0;
}
