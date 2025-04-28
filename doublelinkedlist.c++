/*  Implement Doubly Linked List using templates. Include functions for insertion, deletion and
search of a number, reverse the list. */

#include <iostream>
using namespace std;

// Node structure for Doubly Linked List
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

// Doubly Linked List class with template
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to delete the doubly linked list
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert an element at the end
    void insertEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Insert an element at the beginning
    void insertBegin(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Delete an element by value
    void deleteValue(T value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node<T>* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Element not found.\n";
            return;
        }

        if (temp == head) {
            head = head->next;
            if (head != nullptr)
                head->prev = nullptr;
        } else if (temp == tail) {
            tail = tail->prev;
            if (tail != nullptr)
                tail->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
    }

    // Search for an element
    bool search(T value) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Reverse the list
    void reverse() {
        if (head == nullptr)
            return;

        Node<T>* temp = nullptr;
        Node<T>* current = head;
        tail = head;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr)
            head = temp->prev;
    }

    // Display the list from head to tail
    void displayForward() {
        Node<T>* temp = head;
        if (temp == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display the list from tail to head
    void displayBackward() {
        Node<T>* temp = tail;
        if (temp == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList<int> list;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertBegin(5);

    cout << "List from head to tail: ";
    list.displayForward();

    cout << "List from tail to head: ";
    list.displayBackward();

    list.deleteValue(20);
    cout << "List after deleting 20: ";
    list.displayForward();

    list.reverse();
    cout << "List after reversing: ";
    list.displayForward();

    if (list.search(10)) {
        cout << "10 found in the list.\n";
    } else {
        cout << "10 not found in the list.\n";
    }

    return 0;
}

