/* WAP to implement heap operations. */

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;  // To store the elements in the heap

    // Function to get the index of the left child
    int left(int i) { return 2 * i + 1; }

    // Function to get the index of the right child
    int right(int i) { return 2 * i + 2; }

    // Function to heapify the tree to maintain the heap property
    void heapify(int i) {
        int largest = i;
        int leftChild = left(i);
        int rightChild = right(i);

        // Check if left child is larger than root
        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        // Check if right child is larger than largest so far
        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        // If largest is not root
        if (largest != i) {
            swap(heap[i], heap[largest]);  // Swap
            heapify(largest);  // Recursively heapify the affected subtree
        }
    }

public:
    // Function to insert a new element in the heap
    void insert(int value) {
        heap.push_back(value);
        int index = heap.size() - 1;

        // Move up the newly inserted element to its correct position
        while (index != 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    // Function to delete the root element (max element in max-heap)
    void deleteRoot() {
        if (heap.size() == 0) {
            throw out_of_range("Heap is empty.");
        }

        // Replace the root with the last element in the heap
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();  // Remove the last element

        // Reheapify the tree to maintain the heap property
        heapify(0);
    }

    // Function to get the maximum element (root element)
    int peek() {
        if (heap.size() == 0) {
            throw out_of_range("Heap is empty.");
        }
        return heap[0];
    }

    // Function to build the heap from an unsorted array
    void buildHeap(const vector<int>& arr) {
        heap = arr;
        int n = heap.size();

        // Start from the last non-leaf node and heapify all nodes
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    // Function to print the heap elements
    void printHeap() {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap maxHeap;

    // Insert elements into the heap
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);
    maxHeap.insert(30);
    maxHeap.insert(40);
    maxHeap.insert(50);
    maxHeap.insert(5);

    cout << "Heap after insertions: ";
    maxHeap.printHeap();

    // Peek the maximum element (root)
    cout << "Max element (root) is: " << maxHeap.peek() << endl;

    // Delete the root element (maximum element)
    maxHeap.deleteRoot();
    cout << "Heap after deleting root: ";
    maxHeap.printHeap();

    // Build a heap from an unsorted array
    vector<int> arr = {10, 20, 15, 30, 40, 50, 5};
    maxHeap.buildHeap(arr);
    cout << "Heap after building from array: ";
    maxHeap.printHeap();

    return 0;
}
