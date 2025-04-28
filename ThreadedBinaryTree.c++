/* WAP to create a Threaded Binary Tree as per inorder traversal, and implement operations
like finding the successor / predecessor of an element, insert an element, inorder traversal. */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool rightThread;  // True if right pointer is a thread (i.e., points to inorder successor)
    
    Node(int val) {
        data = val;
        left = right = nullptr;
        rightThread = false;
    }
};

class ThreadedBinaryTree {
private:
    Node *root;

    // Utility function for inserting node in threaded binary tree
    void insertHelper(Node *&root, int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        
        Node *current = root;
        Node *parent = nullptr;
        
        // Find the position where the node is to be inserted
        while (current) {
            parent = current;
            if (key < current->data) {
                if (current->left == nullptr) break;
                else current = current->left;
            } else {
                if (current->right == nullptr || current->rightThread) break;
                else current = current->right;
            }
        }

        Node *newNode = new Node(key);
        if (key < parent->data) {
            parent->left = newNode;
        } else {
            if (parent->rightThread) {
                newNode->right = parent->right;
                newNode->rightThread = true;
                parent->rightThread = false;
            }
            parent->right = newNode;
        }
    }

    // Function for inorder traversal using threaded links
    void inorderTraversal(Node *node) {
        Node *current = node;
        while (current) {
            // Go to the leftmost node
            while (current->left) {
                current = current->left;
            }

            // Print the current node's data
            cout << current->data << " ";

            // If there's a thread, follow it to the successor
            if (current->rightThread) {
                current = current->right;
            } else {
                current = current->right;
            }
        }
    }

    // Find the inorder successor of a node
    Node* findSuccessor(Node *node) {
        if (node->rightThread) return node->right;
        
        node = node->right;
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Find the inorder predecessor of a node
    Node* findPredecessor(Node *node) {
        if (node->left) {
            node = node->left;
            while (node && node->right) {
                node = node->right;
            }
            return node;
        }
        return nullptr;
    }

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    // Insert an element in threaded binary tree
    void insert(int key) {
        insertHelper(root, key);
    }

    // Inorder traversal of threaded binary tree
    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    // Find the successor of a given element
    void findSuccessor(int key) {
        Node *node = root;
        while (node) {
            if (node->data == key) {
                Node *succ = findSuccessor(node);
                if (succ) cout << "Successor of " << key << " is: " << succ->data << endl;
                else cout << "Successor not found!" << endl;
                return;
            } else if (key < node->data) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        cout << "Node not found!" << endl;
    }

    // Find the predecessor of a given element
    void findPredecessor(int key) {
        Node *node = root;
        while (node) {
            if (node->data == key) {
                Node *pred = findPredecessor(node);
                if (pred) cout << "Predecessor of " << key << " is: " << pred->data << endl;
                else cout << "Predecessor not found!" << endl;
                return;
            } else if (key < node->data) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        cout << "Node not found!" << endl;
    }
};

int main() {
    ThreadedBinaryTree tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Perform Inorder Traversal
    cout << "Inorder Traversal: ";
    tree.inorder();

    // Find Successor and Predecessor
    tree.findSuccessor(30);
    tree.findPredecessor(70);

    return 0;
}
