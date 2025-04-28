/* Implement Linked List using templates. Include functions for insertion, deletion and search of
a number, reverse the list and concatenate two linked lists (include a function and also overload
operator +). */

#include <iostream>
using namespace std;

// Node structure for Linked List
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

// Linked List class with template
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to delete the linked list
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert an element at the end of the list
    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Delete an element by value
    void deleteValue(T value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            cout << "Element not found.\n";
            return;
        }
        Node<T>* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
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

    // Reverse the linked list
    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // Concatenate another linked list
    void concatenate(LinkedList<T>& other) {
        if (head == nullptr) {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = other.head;
        other.head = nullptr;
    }

    // Overload the + operator for concatenation
    LinkedList<T> operator+(LinkedList<T>& other) {
        LinkedList<T> newList;
        Node<T>* temp = head;
        while (temp != nullptr) {
            newList.insert(temp->data);
            temp = temp->next;
        }
        temp = other.head;
        while (temp != nullptr) {
            newList.insert(temp->data);
            temp = temp->next;
        }
        return newList;
    }

    // Display the list
    void display() {
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
};

int main() {
    LinkedList<int> list1;
    LinkedList<int> list2;

    list1.insert(10);
    list1.insert(20);
    list1.insert(30);
    list2.insert(40);
    list2.insert(50);

    cout << "List 1: ";
    list1.display();
    cout << "List 2: ";
    list2.display();

    // Testing concatenation using a function
    list1.concatenate(list2);
    cout << "List 1 after concatenation with List 2: ";
    list1.display();

    // Testing concatenation using overloaded operator +
    LinkedList<int> list3 = list1 + list2;
    cout << "List 3 (concatenation using + operator): ";
    list3.display();

    // Reversing the list
    list1.reverse();
    cout << "List 1 after reversing: ";
    list1.display();

    // Deleting a value
    list1.deleteValue(20);
    cout << "List 1 after deleting 20: ";
    list1.display();

    // Searching for a value
    if (list1.search(30)) {
        cout << "30 is found in List 1.\n";
    } else {
        cout << "30 is not found in List 1.\n";
    }

    return 0;
}
