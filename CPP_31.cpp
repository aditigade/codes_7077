#include <iostream>

using namespace std;

// Node structure for threaded binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded;

    Node(int val) : data(val), left(nullptr), right(nullptr), isThreaded(false) {}
};

// Function to create threaded binary tree
Node* createThreadedTree(int arr[], int size) {
    Node* root = new Node(arr[0]);
    Node* current = root;

    for (int i = 1; i < size; ++i) {
        Node* newNode = new Node(arr[i]);

        if (arr[i] < current->data) {
            newNode->left = current->left;
            current->left = newNode;
        } else {
            newNode->left = current;
            while (current->right != nullptr && current->right->data < arr[i]) {
                current = current->right;
            }
            newNode->right = current->right;
            current->right = newNode;
            current->isThreaded = true;
        }

        current = newNode;
    }

    return root;
}

// Function to find the leftmost node in a subtree
Node* leftmostNode(Node* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Function to traverse threaded binary tree in postorder
void postorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    Node* current = leftmostNode(root);

    while (current != nullptr) {
        if (!current->isThreaded) {
            current = leftmostNode(current->right);
        } else {
            cout << current->data << " ";
            if (current->right != nullptr) {
                current = current->right;
            } else {
                current = leftmostNode(current->right);
            }
        }
    }
}

int main() {
    // Example input array
    int arr[] = {4, 2, 6, 1, 3, 5, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Create threaded binary tree
    Node* root = createThreadedTree(arr, size);

    cout << "Postorder traversal of threaded binary tree: ";
    postorderTraversal(root);
    cout << endl;

    return 0;
}
