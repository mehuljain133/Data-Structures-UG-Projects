/* Write a program to search an element from a list. Give user the option to perform Linear or
Binary search. Use Template functions. */


#include <iostream>
#include <vector>
#include <algorithm> // for sort (needed for binary search)
using namespace std;

// Template function for Linear Search
template <typename T>
int linearSearch(const vector<T>& arr, T key) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == key)
            return i;
    }
    return -1; // Not found
}

// Template function for Binary Search
template <typename T>
int binarySearch(const vector<T>& arr, T key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Not found
}

int main() {
    int n, choice;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    int key;
    cout << "Enter the element to search: ";
    cin >> key;

    cout << "Choose Search Method:\n";
    cout << "1. Linear Search\n2. Binary Search\n";
    cin >> choice;

    int result = -1;

    switch (choice) {
    case 1:
        result = linearSearch(arr, key);
        break;
    case 2:
        sort(arr.begin(), arr.end()); // Must sort before Binary Search
        cout << "Array sorted for Binary Search.\n";
        result = binarySearch(arr, key);
        break;
    default:
        cout << "Invalid choice!\n";
        return 0;
    }

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found.\n";

    return 0;
}
