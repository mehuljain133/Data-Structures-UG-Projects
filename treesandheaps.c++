/* Trees and Heaps: Introduction to tree as a data structure; binary trees, binary search trees,
analysis of insert, delete, search operations, recursive and iterative traversals on binary search
trees. Height-balanced trees (AVL), B trees, analysis of insert, delete, search operations on AVL
and B trees.
Introduction to heap as a data structure. analysis of insert, extract-min/max and delete-min/max
operations, applications to priority queues. */

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/////////////////////////////////////////////////
// 1. Binary Search Tree (BST)
/////////////////////////////////////////////////
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    TreeNode* root;

    BST() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);
        if (key < node->data)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return node;
    }

    TreeNode* search(TreeNode* node, int key) {
        if (!node || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

    TreeNode* findMin(TreeNode* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Recursive Inorder Traversal
    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Iterative Inorder Traversal
    void inorderIterative(TreeNode* node) {
        if (!node) return;
        stack<TreeNode*> s;
        TreeNode* curr = node;
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
};

/////////////////////////////////////////////////
// 2. AVL Tree (Self-balancing BST)
/////////////////////////////////////////////////
class AVL {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

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

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    Node* root;

    AVL() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

/////////////////////////////////////////////////
// 3. Heaps (Min-Heap Example)
/////////////////////////////////////////////////
class MinHeap {
private:
    int* harr;
    int capacity;
    int heap_size;

public:
    MinHeap(int cap) {
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];
    }

    void insertKey(int k) {
        if (heap_size == capacity) {
            cout << "Overflow: Could not insertKey\n";
            return;
        }

        int i = heap_size++;
        harr[i] = k;

        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(harr[i], harr[parent(i)]);
            i = parent(i);
        }
    }

    int extractMin() {
        if (heap_size <= 0)
            return INT_MAX;
        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }

        int root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    void deleteMin() {
        extractMin();
    }

    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l] < harr[smallest])
            smallest = l;
        if (r < heap_size && harr[r] < harr[smallest])
            smallest = r;
        if (smallest != i) {
            swap(harr[i], harr[smallest]);
            MinHeapify(smallest);
        }
    }

    void display() {
        cout << "Min Heap Elements: ";
        for (int i = 0; i < heap_size; i++)
            cout << harr[i] << " ";
        cout << endl;
    }

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
};

/////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////
int main() {
    cout << "==== BST Operations ====\n";
    BST bst;
    bst.root = bst.insert(bst.root, 50);
    bst.insert(bst.root, 30);
    bst.insert(bst.root, 20);
    bst.insert(bst.root, 40);
    bst.insert(bst.root, 70);
    bst.insert(bst.root, 60);
    bst.insert(bst.root, 80);

    cout << "Inorder Traversal (Recursive): ";
    bst.inorder(bst.root);
    cout << "\nInorder Traversal (Iterative): ";
    bst.inorderIterative(bst.root);

    bst.root = bst.deleteNode(bst.root, 20);
    cout << "\nAfter Deletion of 20, Inorder: ";
    bst.inorder(bst.root);
    cout << "\n\n";

    cout << "==== AVL Tree Operations ====\n";
    AVL avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    cout << "AVL Inorder Traversal: ";
    avl.display();
    cout << "\n";

    cout << "==== Min Heap Operations ====\n";
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteMin();
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);

    cout << "Heap Elements: ";
    h.display();
    cout << "Extracted Min: " << h.extractMin() << "\n";
    h.display();

    return 0;
}
