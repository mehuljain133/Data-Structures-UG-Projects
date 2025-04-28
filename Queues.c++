/* Queues: Array and linked representation of queue, de-queue, comparison of the operations on
queues in the two representations. Applications of queues. */

#include <iostream>
#include <queue>   // For C++ STL queues
#include <deque>   // For double-ended queues
using namespace std;

// 1. Array-based Queue
class ArrayQueue {
private:
    int *arr;
    int front, rear, size, capacity;

public:
    ArrayQueue(int c) {
        capacity = c;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    ~ArrayQueue() {
        delete[] arr;
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return arr[front];
    }

    void display() {
        cout << "Array Queue: ";
        if (isEmpty()) {
            cout << "Empty\n";
            return;
        }
        int count = size;
        int i = front;
        while (count--) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

// 2. Linked-list-based Queue
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedQueue {
private:
    Node* front;
    Node* rear;

public:
    LinkedQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (!front) {
            cout << "Queue Underflow\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
    }

    int peek() {
        if (!front) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return front->data;
    }

    void display() {
        cout << "Linked Queue: ";
        Node* temp = front;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// 3. Dequeue (Double Ended Queue) using Deque
void dequeExample() {
    deque<int> dq;
    dq.push_back(10);
    dq.push_front(20);
    dq.push_back(30);

    cout << "Deque elements: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    dq.pop_front();
    dq.pop_back();

    cout << "Deque after popping front and back: ";
    for (int x : dq) cout << x << " ";
    cout << endl;
}

// 4. Applications of Queues
void queueApplications() {
    cout << "Applications of Queues:\n";
    cout << "- Job Scheduling\n";
    cout << "- Printer Spooling\n";
    cout << "- Order processing systems\n";
    cout << "- BFS (Breadth-First Search) in Graphs\n";
    cout << "- Traffic Management\n";
    cout << "- Real-time streaming (Data Buffers)\n\n";
}

// 5. Comparison Function
void compareQueues() {
    cout << "Comparison of Array Queue vs Linked Queue:\n";
    cout << "Array Queue:\n";
    cout << "- Fixed size (needs resizing if full)\n";
    cout << "- Faster access (direct index)\n";
    cout << "- Can waste space if not managed (circular technique)\n";
    cout << "\nLinked Queue:\n";
    cout << "- Dynamic size (no limit unless memory full)\n";
    cout << "- Slight overhead (extra pointer field)\n";
    cout << "- Good for unpredictable queue sizes\n";
}

int main() {
    // Array Queue
    ArrayQueue aq(5);
    aq.enqueue(1);
    aq.enqueue(2);
    aq.enqueue(3);
    aq.display();
    aq.dequeue();
    aq.display();
    cout << "ArrayQueue peek: " << aq.peek() << endl << endl;

    // Linked Queue
    LinkedQueue lq;
    lq.enqueue(100);
    lq.enqueue(200);
    lq.enqueue(300);
    lq.display();
    lq.dequeue();
    lq.display();
    cout << "LinkedQueue peek: " << lq.peek() << endl << endl;

    // Dequeue
    dequeExample();
    cout << endl;

    // Applications
    queueApplications();

    // Comparison
    compareQueues();

    return 0;
}
