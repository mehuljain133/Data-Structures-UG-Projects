/* WAP to create a Binary Search Tree and include following operations in tree: (a) Insertion
(Recursive and Iterative Implementation) (b) Deletion by copying (c) Deletion by Merging (d)
Search a no. in BST (e) Display its preorder, postorder and inorder traversals Recursively (f)
Display its preorder, postorder and inorder traversals Iteratively (g) Display its level-by-level
traversals (h) Count the non-leaf nodes and leaf nodes (i) Display height of tree (j) Create a
mirror image of tree (k) Check whether two BSTs are equal or not */

#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// BST class to encapsulate the tree and its operations
class BST {
private:
    Node* root;

    // Helper function for recursive insertion
    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) return new Node(value);
        if (value < node->data)
            node->left = insertRecursive(node->left, value);
        else
            node->right = insertRecursive(node->right, value);
        return node;
    }

    // Helper function for iterative insertion
    Node* insertIterative(Node* node, int value) {
        if (node == nullptr) return new Node(value);
        Node* current = node;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (value < parent->data)
            parent->left = new Node(value);
        else
            parent->right = new Node(value);

        return node;
    }

    // Recursive search function
    Node* searchRecursive(Node* node, int key) {
        if (node == nullptr || node->data == key)
            return node;
        if (key < node->data)
            return searchRecursive(node->left, key);
        else
            return searchRecursive(node->right, key);
    }

    // Deletion by copying: Remove a node and copy its right child
    Node* deleteByCopy(Node* root, int value) {
        if (root == nullptr) return root;
        if (value < root->data)
            root->left = deleteByCopy(root->left, value);
        else if (value > root->data)
            root->right = deleteByCopy(root->right, value);
        else {
            // Node to be deleted found
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            // Node with two children: Get the inorder successor
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteByCopy(root->right, temp->data);
        }
        return root;
    }

    // Deletion by merging: Merge left and right subtrees
    Node* deleteByMerging(Node* root, int value) {
        if (root == nullptr) return root;
        if (value < root->data)
            root->left = deleteByMerging(root->left, value);
        else if (value > root->data)
            root->right = deleteByMerging(root->right, value);
        else {
            // Node to be deleted found
            if (root->left == nullptr)
                return root->right;
            else if (root->right == nullptr)
                return root->left;

            // Node with two children: Merge left and right subtrees
            Node* temp = root->left;
            root = root->right;
            temp->right = root;
            return temp;
        }
        return root;
    }

    // Find minimum node in a tree
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Preorder traversal (recursive)
    void preorderRecursive(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }

    // Inorder traversal (recursive)
    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }

    // Postorder traversal (recursive)
    void postorderRecursive(Node* node) {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << node->data << " ";
        }
    }

    // Preorder traversal (iterative)
    void preorderIterative(Node* root) {
        if (root == nullptr) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* node = s.top();
            s.pop();
            cout << node->data << " ";
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
    }

    // Inorder traversal (iterative)
    void inorderIterative(Node* root) {
        stack<Node*> s;
        Node* current = root;
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }

    // Postorder traversal (iterative)
    void postorderIterative(Node* root) {
        if (root == nullptr) return;
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* node = s1.top();
            s1.pop();
            s2.push(node);
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }

    // Level-order traversal
    void levelOrderTraversal(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            cout << node->data << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    // Count non-leaf and leaf nodes
    void countNodes(Node* root, int &leafCount, int &nonLeafCount) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) {
            leafCount++;
        } else {
            nonLeafCount++;
        }
        countNodes(root->left, leafCount, nonLeafCount);
        countNodes(root->right, leafCount, nonLeafCount);
    }

    // Calculate height of the tree
    int height(Node* root) {
        if (root == nullptr) return -1;
        return max(height(root->left), height(root->right)) + 1;
    }

    // Create a mirror image of the tree
    Node* createMirror(Node* root) {
        if (root == nullptr) return nullptr;
        Node* left = createMirror(root->left);
        Node* right = createMirror(root->right);
        root->left = right;
        root->right = left;
        return root;
    }

    // Check if two trees are equal
    bool isEqual(Node* root1, Node* root2) {
        if (root1 == nullptr && root2 == nullptr) return true;
        if (root1 == nullptr || root2 == nullptr) return false;
        return (root1->data == root2->data) && isEqual(root1->left, root2->left) && isEqual(root1->right, root2->right);
    }

public:
    BST() : root(nullptr) {}

    // Public insert function
    void insert(int value) {
        root = insertRecursive(root, value); // Use recursive insertion
    }

    void insertIterative(int value) {
        root = insertIterative(root, value); // Use iterative insertion
    }

    // Public delete function (by copying)
    void deleteByCopy(int value) {
        root = deleteByCopy(root, value);
    }

    // Public delete function (by merging)
    void deleteByMerging(int value) {
        root = deleteByMerging(root, value);
    }

    // Public search function
    Node* search(int value) {
        return searchRecursive(root, value);
    }

    // Public display functions (recursively)
    void preorderRecursive() { preorderRecursive(root); }
    void inorderRecursive() { inorderRecursive(root); }
    void postorderRecursive() { postorderRecursive(root); }

    // Public display functions (iteratively)
    void preorderIterative() { preorderIterative(root); }
    void inorderIterative() { inorderIterative(root); }
    void postorderIterative() { postorderIterative(root); }

    // Public level-order traversal
    void levelOrderTraversal() { levelOrderTraversal(root); }

    // Public count function
    void countNodes(int &leafCount, int &nonLeafCount) { countNodes(root, leafCount, nonLeafCount); }

    // Public height function
    int height() { return height(root); }

    // Public mirror creation function
    void createMirror() { root = createMirror(root); }

    // Public equality check function
    bool isEqual(BST& other) {
        return isEqual(root, other.root);
    }
};

int main() {
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder Traversal (Recursive): ";
    bst.inorderRecursive();
    cout << endl;

    cout << "Preorder Traversal (Recursive): ";
    bst.preorderRecursive();
    cout << endl;

    cout << "Postorder Traversal (Recursive): ";
    bst.postorderRecursive();
    cout << endl;

    cout << "Inorder Traversal (Iterative): ";
    bst.inorderIterative();
    cout << endl;

    cout << "Preorder Traversal (Iterative): ";
    bst.preorderIterative();
    cout << endl;

    cout << "Postorder Traversal (Iterative): ";
    bst.postorderIterative();
    cout << endl;

    cout << "Level-order Traversal: ";
    bst.levelOrderTraversal();
    cout << endl;

    int leafCount = 0, nonLeafCount = 0;
    bst.countNodes(leafCount, nonLeafCount);
    cout << "Leaf nodes: " << leafCount << ", Non-leaf nodes: " << nonLeafCount << endl;

    cout << "Height of the tree: " << bst.height() << endl;

    bst.createMirror();
    cout << "Mirror tree Inorder Traversal: ";
    bst.inorderRecursive();
    cout << endl;

    BST bst2;
    bst2.insert(50);
    bst2.insert(30);
    bst2.insert(20);
    bst2.insert(40);
    bst2.insert(70);
    bst2.insert(60);
    bst2.insert(80);
    cout << "Are the trees equal? " << (bst.isEqual(bst2) ? "Yes" : "No") << endl;

    return 0;
}
