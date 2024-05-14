#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorderTraversal(struct TreeNode* root) {
    struct TreeNode* stack[100];
    int top = -1;
    struct TreeNode* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

int countNodesLongestPath(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + leftHeight + rightHeight;
}

void displayLevelWise(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct TreeNode* current = queue[++front];
        printf("%d ", current->data);
        if (current->left != NULL)
            queue[++rear] = current->left;
        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

int main() {
    struct TreeNode* root = NULL;
    char choice;

    do {
        int data;
        struct TreeNode* newNode;

        printf("Enter the data for the new node: ");
        scanf("%d", &data);
        newNode = createNode(data);

        if (root == NULL) {
            root = newNode;
        } else {
            struct TreeNode* current = root;
            while (1) {
                printf("Do you want to insert '%d' to the left or right of '%d' (l/r): ", data, current->data);
                scanf(" %c", &choice);
                if (choice == 'l' || choice == 'L') {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else if (choice == 'r' || choice == 'R') {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    printf("Invalid choice! Please enter 'L' or 'R'.\n");
                }
            }
        }

        printf("Do you want to insert another node? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    printf("\nInorder Traversal: ");
    inorderTraversal(root);
    printf("\nNumber of nodes on longest path: %d\n", countNodesLongestPath(root));
    printf("Tree levelwise: ");
    displayLevelWise(root);
    printf("\nHeight of the tree: %d\n", height(root));

    return 0;
}