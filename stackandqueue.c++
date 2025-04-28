/*  Perform Stack operations using Linked List implementation.
Perform Stack operations using Array implementation. Use Templates.
Perform Queues operations using Circular Array implementation. Use Templates.
Create and perform different operations on Double-ended Queues using Linked List
implementation. */

#include <iostream>
using namespace std;

// Stack implemented using Linked List (Template)
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class StackLinkedList {
private:
    Node<T>* top;

public:
    StackLinkedList() : top(nullptr) {}

    ~StackLinkedList() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return T();
        }
        T value = top->data;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    T peek() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return T();
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Stack implemented using Array (Template)
template <typename T>
class StackArray {
private:
    T* arr;
    int top;
    int capacity;

public:
    StackArray(int size) : capacity(size), top(-1) {
        arr = new T[capacity];
    }

    ~StackArray() {
        delete[] arr;
    }

    void push(T value) {
        if (top == capacity - 1) {
            cout << "Stack overflow.\n";
            return;
        }
        arr[++top] = value;
    }

    T pop() {
        if (top == -1) {
            cout << "Stack is empty.\n";
            return T();
        }
        return arr[top--];
    }

    T peek() {
        if (top == -1) {
            cout << "Stack is empty.\n";
            return T();
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// Queue implemented using Circular Array (Template)
template <typename T>
class QueueCircularArray {
private:
    T* arr;
    int front, rear, capacity;

public:
    QueueCircularArray(int size) : capacity(size), front(0), rear(0) {
        arr = new T[capacity];
    }

    ~QueueCircularArray() {
        delete[] arr;
    }

    void enqueue(T value) {
        if ((rear + 1) % capacity == front) {
            cout << "Queue overflow.\n";
            return;
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;
    }

    T dequeue() {
        if (front == rear) {
            cout << "Queue is empty.\n";
            return T();
        }
        T value = arr[front];
        front = (front + 1) % capacity;
        return value;
    }

    T peek() {
        if (front == rear) {
            cout << "Queue is empty.\n";
            return T();
        }
        return arr[front];
    }

    bool isEmpty() {
        return front == rear;
    }
};

// Deque implemented using Linked List (Template)
template <typename T>
class DequeLinkedList {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    DequeLinkedList() : front(nullptr), rear(nullptr) {}

    ~DequeLinkedList() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void insertFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (front == nullptr) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front = newNode;
        }
    }

    void insertRear(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T deleteFront() {
        if (front == nullptr) {
            cout << "Deque is empty.\n";
            return T();
        }
        T value = front->data;
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        return value;
    }

    T deleteRear() {
        if (rear == nullptr) {
            cout << "Deque is empty.\n";
            return T();
        }
        T value = rear->data;
        if (front == rear) {
            delete rear;
            front = rear = nullptr;
        } else {
            Node<T>* temp = front;
            while (temp->next != rear) {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete rear;
            rear = temp;
        }
        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    T getFront() {
        if (front == nullptr) {
            cout << "Deque is empty.\n";
            return T();
        }
        return front->data;
    }

    T getRear() {
        if (rear == nullptr) {
            cout << "Deque is empty.\n";
            return T();
        }
        return rear->data;
    }
};

// Main Function for testing all implementations
int main() {
    // Test Stack using Linked List
    StackLinkedList<int> stackLinkedList;
    stackLinkedList.push(10);
    stackLinkedList.push(20);
    stackLinkedList.push(30);
    cout << "Stack (Linked List) Top: " << stackLinkedList.peek() << endl;
    cout << "Popped: " << stackLinkedList.pop() << endl;
    cout << "Stack (Linked List) Top after pop: " << stackLinkedList.peek() << endl;

    // Test Stack using Array
    StackArray<int> stackArray(5);
    stackArray.push(10);
    stackArray.push(20);
    stackArray.push(30);
    cout << "Stack (Array) Top: " << stackArray.peek() << endl;
    cout << "Popped: " << stackArray.pop() << endl;
    cout << "Stack (Array) Top after pop: " << stackArray.peek() << endl;

    // Test Queue using Circular Array
    QueueCircularArray<int> queue(5);
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    cout << "Queue Front: " << queue.peek() << endl;
    cout << "Dequeued: " << queue.dequeue() << endl;
    cout << "Queue Front after dequeue: " << queue.peek() << endl;

    // Test Deque using Linked List
    DequeLinkedList<int> deque;
    deque.insertFront(10);
    deque.insertRear(20);
    deque.insertFront(5);
    cout << "Deque Front: " << deque.getFront() << endl;
    cout << "Deque Rear: " << deque.getRear() << endl;
    cout << "Deleted from Front: " << deque.deleteFront() << endl;
    cout << "Deleted from Rear: " << deque.deleteRear() << endl;
    cout << "Deque Empty: " << deque.isEmpty() << endl;

    return 0;
}
