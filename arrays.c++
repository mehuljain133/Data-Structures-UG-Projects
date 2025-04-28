/* Arrays: single and multi-dimensional arrays, analysis of insert, delete and search operations in
arrays (both linear search and binary search), implementing sparse matrices, applications of
arrays to sorting: selection sort, insertion sort, bubble sort, comparison of sorting techniques via
empirical studies. Introduction to Vectors. */

#include <iostream>
#include <vector>
#include <chrono> // For empirical time comparison
using namespace std;

// 1. Single-dimensional Array Operations
void insertElement(int arr[], int &n, int pos, int value) {
    for (int i = n; i > pos; --i)
        arr[i] = arr[i - 1];
    arr[pos] = value;
    n++;
}

void deleteElement(int arr[], int &n, int pos) {
    for (int i = pos; i < n - 1; ++i)
        arr[i] = arr[i + 1];
    n--;
}

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; ++i)
        if (arr[i] == key) return i;
    return -1;
}

int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 2. Multi-dimensional Array (Matrix)
void displayMatrix(int mat[][3], int rows, int cols) {
    cout << "Matrix:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

// 3. Sparse Matrix Representation
struct SparseElement {
    int row, col, value;
};

void createSparseMatrix(int mat[][3], int rows, int cols, vector<SparseElement> &sparse) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (mat[i][j] != 0)
                sparse.push_back({i, j, mat[i][j]});
}

void displaySparseMatrix(const vector<SparseElement> &sparse) {
    cout << "Sparse Matrix:\n";
    for (auto &elem : sparse)
        cout << "(" << elem.row << ", " << elem.col << ", " << elem.value << ")\n";
}

// 4. Sorting Algorithms
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i+1; j < n; ++j)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < n-i-1; ++j)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// 5. Empirical Comparison
void compareSorting(int arr[], int n) {
    int temp[n];
    chrono::steady_clock::time_point start, end;
    chrono::duration<double> elapsed;

    // Selection Sort
    copy(arr, arr + n, temp);
    start = chrono::steady_clock::now();
    selectionSort(temp, n);
    end = chrono::steady_clock::now();
    elapsed = end - start;
    cout << "Selection Sort Time: " << elapsed.count() << "s\n";

    // Insertion Sort
    copy(arr, arr + n, temp);
    start = chrono::steady_clock::now();
    insertionSort(temp, n);
    end = chrono::steady_clock::now();
    elapsed = end - start;
    cout << "Insertion Sort Time: " << elapsed.count() << "s\n";

    // Bubble Sort
    copy(arr, arr + n, temp);
    start = chrono::steady_clock::now();
    bubbleSort(temp, n);
    end = chrono::steady_clock::now();
    elapsed = end - start;
    cout << "Bubble Sort Time: " << elapsed.count() << "s\n";
}

// 6. Introduction to Vectors
void vectorExample() {
    vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    cout << "Vector elements: ";
    for (int elem : v)
        cout << elem << " ";
    cout << endl;
}

// Main Program
int main() {
    int arr[100] = {5, 8, 12, 15, 20};
    int n = 5;

    cout << "Original Array: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;

    insertElement(arr, n, 2, 10);
    cout << "After Insertion: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;

    deleteElement(arr, n, 3);
    cout << "After Deletion: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;

    int key = 12;
    cout << "Linear Search for " << key << ": Index " << linearSearch(arr, n, key) << endl;

    // Before binary search, array must be sorted
    selectionSort(arr, n);
    cout << "Binary Search for " << key << ": Index " << binarySearch(arr, 0, n-1, key) << endl;

    // Multi-dimensional array
    int mat[3][3] = {
        {5, 0, 0},
        {0, 8, 0},
        {0, 0, 3}
    };
    displayMatrix(mat, 3, 3);

    vector<SparseElement> sparse;
    createSparseMatrix(mat, 3, 3, sparse);
    displaySparseMatrix(sparse);

    // Sorting comparison
    int sortArr[10] = {29, 10, 14, 37, 13, 20, 15, 7, 23, 5};
    compareSorting(sortArr, 10);

    // Vectors
    vectorExample();

    return 0;
}
