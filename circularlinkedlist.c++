/* Implement Circular Linked List using templates. Include functions for insertion, deletion and
search of a number, reverse the list. */

#include <iostream>
using namespace std;

// Node structure for Circular Linked List
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

// Circular Linked List class with template
template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    CircularLinkedList() : head(nullptr) {}

    // Destructor to delete the circular linked list
    ~CircularLinkedList() {
        if (head == nullptr)
            return;
        Node<T>* temp = head;
        do {
            Node<T>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
    }

    // Insert an element at the end of the list
    void insertEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;  // Circular link
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;  // Circular link
        }
    }

    // Delete an element by value
    void deleteValue(T value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node<T>* temp = head;
        Node<T>* prev = nullptr;

        // Check if head is the node to be deleted
        if (head->data == value) {
            if (head->next == head) {  // Only one element
                delete head;
                head = nullptr;
            } else {
                prev = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                head = head->next;  // Move head to next node
                temp->next = head;
                delete prev;
            }
            return;
        }

        // Search for the element and delete it
        do {
            prev = temp;
            temp = temp->next;
            if (temp->data == value) {
                prev->next = temp->next;
                delete temp;
                return;
            }
        } while (temp != head);

        cout << "Element not found.\n";
    }

    // Search for an element
    bool search(T value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return false;
        }

        Node<T>* temp = head;
        do {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    // Reverse the circular linked list
    void reverse() {
        if (head == nullptr || head->next == head) {
            return;  // Nothing to reverse if list is empty or has only one element
        }

        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        Node<T>* last = head;

        // Traverse the list to find the last node
        while (last->next != head) {
            last = last->next;
        }

        do {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != head);

        head->next = prev;  // Set the new head node's next to the last node
        head = prev;  // New head is the last node
    }

    // Display the list
    void display() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        Node<T>* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

int main() {
    CircularLinkedList<int> list;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertEnd(40);
    list.insertEnd(50);

    cout << "Circular Linked List: ";
    list.display();

    list.deleteValue(20);
    cout << "List after deleting 20: ";
    list.display();

    list.reverse();
    cout << "List after reversing: ";
    list.display();

    if (list.search(30)) {
        cout << "30 found in the list.\n";
    } else {
        cout << "30 not found in the list.\n";
    }

    list.deleteValue(10);
    list.deleteValue(30);
    list.deleteValue(40);
    list.deleteValue(50);

    cout << "List after deleting all elements: ";
    list.display();

    return 0;
}
