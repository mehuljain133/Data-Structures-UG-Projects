/* WAP using templates to sort a list of elements. Give user the option to perform sorting using
Insertion sort, Bubble sort or Selection sort. */

#include <iostream>
#include <vector>
using namespace std;

// Template function for Insertion Sort
template <typename T>
void insertionSort(vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Template function for Bubble Sort
template <typename T>
void bubbleSort(vector<T>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Template function for Selection Sort
template <typename T>
void selectionSort(vector<T>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}

// Template function to display the array
template <typename T>
void display(const vector<T>& arr) {
    for (const auto& el : arr)
        cout << el << " ";
    cout << endl;
}

int main() {
    int n, choice;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << "Choose Sorting Method:\n";
    cout << "1. Insertion Sort\n2. Bubble Sort\n3. Selection Sort\n";
    cin >> choice;

    switch (choice) {
    case 1:
        insertionSort(arr);
        cout << "Sorted using Insertion Sort:\n";
        break;
    case 2:
        bubbleSort(arr);
        cout << "Sorted using Bubble Sort:\n";
        break;
    case 3:
        selectionSort(arr);
        cout << "Sorted using Selection Sort:\n";
        break;
    default:
        cout << "Invalid choice!\n";
        return 0;
    }

    display(arr);

    return 0;
}
