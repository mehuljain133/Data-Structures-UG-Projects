/* Linked Lists: Singly- linked, doubly-linked and circular lists, analysis of insert, delete and
search operations in all the three types, implementing sparse matrices. Introduction to Sequences */

#include <iostream>
#include <list>
#include <deque>
using namespace std;

// 1. Singly Linked List (SLL)
struct SLLNode {
    int data;
    SLLNode* next;
    SLLNode(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
public:
    SLLNode* head = nullptr;

    void insertFront(int val) {
        SLLNode* newNode = new SLLNode(val);
        newNode->next = head;
        head = newNode;
    }

    void deleteValue(int val) {
        SLLNode* temp = head, *prev = nullptr;
        while (temp && temp->data != val) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) return; // Not found
        if (!prev) head = temp->next; // First node
        else prev->next = temp->next;
        delete temp;
    }

    SLLNode* search(int val) {
        SLLNode* temp = head;
        while (temp) {
            if (temp->data == val) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void display() {
        SLLNode* temp = head;
        cout << "SLL: ";
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

// 2. Doubly Linked List (DLL)
struct DLLNode {
    int data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    DLLNode* head = nullptr;

    void insertFront(int val) {
        DLLNode* newNode = new DLLNode(val);
        if (head) head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    void deleteValue(int val) {
        DLLNode* temp = head;
        while (temp && temp->data != val)
            temp = temp->next;
        if (!temp) return;
        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; // head deletion
        if (temp->next) temp->next->prev = temp->prev;
        delete temp;
    }

    DLLNode* search(int val) {
        DLLNode* temp = head;
        while (temp) {
            if (temp->data == val) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void display() {
        DLLNode* temp = head;
        cout << "DLL: ";
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

// 3. Circular Linked List (CLL)
struct CLLNode {
    int data;
    CLLNode* next;
    CLLNode(int val) : data(val), next(this) {}
};

class CircularLinkedList {
public:
    CLLNode* last = nullptr;

    void insertFront(int val) {
        CLLNode* newNode = new CLLNode(val);
        if (!last) {
            last = newNode;
        } else {
            newNode->next = last->next;
            last->next = newNode;
        }
    }

    void deleteValue(int val) {
        if (!last) return;
        CLLNode *curr = last->next, *prev = last;
        do {
            if (curr->data == val) {
                if (curr == last) {
                    if (curr == curr->next) last = nullptr; // Only one node
                    else {
                        prev->next = curr->next;
                        last = prev;
                    }
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != last->next);
    }

    CLLNode* search(int val) {
        if (!last) return nullptr;
        CLLNode* temp = last->next;
        do {
            if (temp->data == val) return temp;
            temp = temp->next;
        } while (temp != last->next);
        return nullptr;
    }

    void display() {
        if (!last) {
            cout << "CLL: Empty\n";
            return;
        }
        cout << "CLL: ";
        CLLNode* temp = last->next;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != last->next);
        cout << "(back to head)\n";
    }
};

// 4. Sparse Matrix using Linked List
struct SparseNode {
    int row, col, val;
    SparseNode* next;
    SparseNode(int r, int c, int v) : row(r), col(c), val(v), next(nullptr) {}
};

class SparseMatrixLL {
public:
    SparseNode* head = nullptr;

    void insert(int r, int c, int val) {
        SparseNode* newNode = new SparseNode(r, c, val);
        newNode->next = head;
        head = newNode;
    }

    void display() {
        SparseNode* temp = head;
        cout << "Sparse Matrix Elements (row, col, value):\n";
        while (temp) {
            cout << "(" << temp->row << ", " << temp->col << ", " << temp->val << ")\n";
            temp = temp->next;
        }
    }
};

// 5. Introduction to Sequences
void sequenceExample() {
    list<int> l = {1, 2, 3, 4, 5};
    deque<int> d = {10, 20, 30, 40, 50};

    cout << "List elements: ";
    for (int x : l) cout << x << " ";
    cout << endl;

    cout << "Deque elements: ";
    for (int x : d) cout << x << " ";
    cout << endl;
}

// Main Driver
int main() {
    // Singly Linked List
    SinglyLinkedList sll;
    sll.insertFront(10);
    sll.insertFront(20);
    sll.insertFront(30);
    sll.display();
    sll.deleteValue(20);
    sll.display();
    cout << "SLL Search 10: " << (sll.search(10) ? "Found" : "Not Found") << endl;

    // Doubly Linked List
    DoublyLinkedList dll;
    dll.insertFront(100);
    dll.insertFront(200);
    dll.insertFront(300);
    dll.display();
    dll.deleteValue(200);
    dll.display();
    cout << "DLL Search 100: " << (dll.search(100) ? "Found" : "Not Found") << endl;

    // Circular Linked List
    CircularLinkedList cll;
    cll.insertFront(5);
    cll.insertFront(15);
    cll.insertFront(25);
    cll.display();
    cll.deleteValue(15);
    cll.display();
    cout << "CLL Search 5: " << (cll.search(5) ? "Found" : "Not Found") << endl;

    // Sparse Matrix using Linked List
    SparseMatrixLL sparse;
    sparse.insert(0, 2, 5);
    sparse.insert(1, 1, 8);
    sparse.insert(2, 0, 3);
    sparse.display();

    // Sequences example
    sequenceExample();

    return 0;
}
