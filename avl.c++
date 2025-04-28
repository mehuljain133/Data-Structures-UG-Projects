/* WAP to implement various operations on AVL Tree. */

#include <iostream>
#include <algorithm>
using namespace std;

// Define the structure for the AVL tree nodes
struct Node {
    int data;
    Node *left, *right;
    int height;  // Height of the node

    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    // Function to get the height of a node
    int height(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Function to get the balance factor of a node
    int balanceFactor(Node* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Right rotate the subtree rooted at y
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // Left rotate the subtree rooted at x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Function to insert a new node with key in the AVL tree
    Node* insert(Node* node, int key) {
        // 1. Perform the normal BST insertion
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node;  // Duplicates are not allowed
        }

        // 2. Update height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Get the balance factor of this ancestor node to check whether it became unbalanced
        int balance = balanceFactor(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // return the (unchanged) node pointer
        return node;
    }

    // Function to get the node with the minimum value
    Node* minNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Function to delete a node
    Node* deleteNode(Node* root, int key) {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == nullptr) return root;

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node to be deleted is found

            // Node with only one child or no child
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    // One child case
                    *root = *temp; // Copy the contents of the non-empty child
                }

                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minNode(root->right);

                // Copy the inorder successor's content to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree has only one node, return it
        if (root == nullptr) return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR
        int balance = balanceFactor(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }

        // Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Left Case
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Function to perform inorder traversal
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    // Function to perform preorder traversal
    void preorder(Node* root) {
        if (root != nullptr) {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    // Function to perform postorder traversal
    void postorder(Node* root) {
        if (root != nullptr) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }

public:
    Node* root;

    AVLTree() {
        root = nullptr;
    }

    // Insert a node
    void insert(int key) {
        root = insert(root, key);
    }

    // Delete a node
    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    // Perform inorder traversal
    void inorder() {
        inorder(root);
        cout << endl;
    }

    // Perform preorder traversal
    void preorder() {
        preorder(root);
        cout << endl;
    }

    // Perform postorder traversal
    void postorder() {
        postorder(root);
        cout << endl;
    }

    // Search for a node
    bool search(Node* node, int key) {
        if (node == nullptr) return false;

        if (key < node->data) {
            return search(node->left, key);
        } else if (key > node->data) {
            return search(node->right, key);
        } else {
            return true;
        }
    }

    // Search for a node
    bool search(int key) {
        return search(root, key);
    }
};

int main() {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    cout << "Inorder Traversal: ";
    tree.inorder();

    cout << "Preorder Traversal: ";
    tree.preorder();

    cout << "Postorder Traversal: ";
    tree.postorder();

    // Search for a node
    int searchKey = 15;
    cout << "Searching for " << searchKey << ": ";
    if (tree.search(searchKey)) {
        cout << "Found" << endl;
    } else {
        cout << "Not Found" << endl;
    }

    // Delete a node
    int deleteKey = 20;
    cout << "Deleting " << deleteKey << endl;
    tree.deleteNode(deleteKey);

    cout << "Inorder Traversal after deletion: ";
    tree.inorder();

    return 0;
}
