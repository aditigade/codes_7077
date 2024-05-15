// Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *lchild;
    int data;
    struct Node *rchild;
};

struct Node *root = NULL;

struct Node *createNode(int key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->lchild = newNode->rchild = NULL;
    return newNode;
}

void insert(int key) {
    struct Node *t = root;
    struct Node *r = NULL; // Parent node
    struct Node *newNode;

    if (root == NULL) {
        root = createNode(key);
        return;
    }

    while (t != NULL) {
        r = t;
        if (key == t->data)
            return;
        else if (key < t->data)
            t = t->lchild;
        else
            t = t->rchild;
    }

    newNode = createNode(key);
    if (key < r->data)
        r->lchild = newNode;
    else
        r->rchild = newNode;
}

struct Node* Search(struct Node *t, int key)
{
    while(t!=NULL)
    {
        if (key < t->data)
        {
            t = t->lchild;
        }
        else if (key > t->data)
        {
            t = t->rchild;
        }
        else
        {
            return t;
        }
    }
    printf("No such data found");
    return NULL;
}

#define MAX 1000

struct Node* queue[MAX];
int front = -1;
int rear = -1;

int isQueueEmpty() {
    return front == rear;
}

void enqueue(struct Node* t) {
    if(rear < MAX - 1) {
        queue[++rear] = t;
    }
}

struct Node* dequeue() {
    if(!isQueueEmpty()) {
        return queue[++front];
    }
    return NULL;
}

void leafCount(struct Node *t)
{
    if(t == NULL)
        return;

    enqueue(t);

    while(!isQueueEmpty())
    {
        t = dequeue();

        if (t->lchild == NULL && t->rchild == NULL)
            printf("%d ", t->data);
        if(t->lchild != NULL)
            enqueue(t->lchild);
        if(t->rchild != NULL)
            enqueue(t->rchild);
    }
}

int calculateHeight(struct Node *root) {
    if (root == NULL)
        return 0;

    enqueue(root);
    int height = 0;

    while (1) {
        int nodeCount = rear - front; // Number of nodes at current level
        if (nodeCount == 0) // If no nodes left in the queue
            return height;

        height++; // Increment height for each level

        // Dequeue all nodes of the current level and enqueue all nodes of the next level
        while (nodeCount > 0) {
            struct Node* node = dequeue();
            if (node->lchild != NULL)
                enqueue(node->lchild);
            if (node->rchild != NULL)
                enqueue(node->rchild);
            nodeCount--;
        }
    }
}

// Stack structure to hold Node pointers
struct Node* stack[MAX];
int top = -1;
int count = 0;

int isEmpty()
{
    if(top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull()
{
    if (top == MAX)
    {
        return 1;
    }
    else{
        return 0;
    }
}

struct Node *pop()
{
    if(!isEmpty())
    {
        return stack[top--];
    }
    else
    {
        printf("Stack is empty");
        //return NULL;
        return 0;
    }
}

void push(struct Node *t)
{
    if(!isFull())
    {
        top = top + 1;
        stack[top] = t;
    }
    else
    {
        printf("Stack is full");
    }
}

// Function to create the mirror image of a binary search tree without recursion
void mirrorImage(struct Node *originalRoot) {
    // If the original tree is empty, return
    if (originalRoot == NULL)
        return;

    // Create an empty stack for iterative traversal
    struct Node* stack[100];
    int top = -1;

    // Create a new mirrored root node
    struct Node* mirroredRoot = createNode(originalRoot->data);

    // Push the root node of the original tree onto the stack
    stack[++top] = originalRoot;

    // Create pointers for traversing the original and mirrored trees
    struct Node* current;
    struct Node* mirroredCurrent;

    // Traverse the original tree iteratively
    while (top != -1) {
        // Pop a node from the stack
        current = stack[top--];

        // Create mirrored nodes for the left and right children
        if (current->rchild != NULL) {
            struct Node* mirroredLeftChild = createNode(current->rchild->data);
            mirroredRoot->lchild = mirroredLeftChild;
            stack[++top] = current->rchild;
        }
        if (current->lchild != NULL) {
            struct Node* mirroredRightChild = createNode(current->lchild->data);
            mirroredRoot->rchild = mirroredRightChild;
            stack[++top] = current->lchild;
        }

        // Move to the next node in the mirrored tree
        if (mirroredRoot->lchild != NULL)
            mirroredRoot = mirroredRoot->lchild;
        else if (mirroredRoot->rchild != NULL)
            mirroredRoot = mirroredRoot->rchild;
    }

    // Update the global root pointer to point to the mirrored root
    root = mirroredCurrent;
}

// Postorder traversal using a stack
void Postorder(struct Node *t) {
    struct Node* lastVisited = NULL; //to maintain the last visited node

    while (t != NULL || !isEmpty()) {
        if (t != NULL) {
            push(t); // First push
            t = t->lchild;
        } else {
            struct Node* node = stack[top]; //peek
            if (node->rchild != NULL && lastVisited != node->rchild) {
                // If right child exists and traversing node first time
                t = node->rchild;
            } else {
                printf("%d ", node->data);
                lastVisited = pop();
            }
        }
    }
}

void Preorder(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            printf("%d ", t->data);
            push(t);
            t = t->lchild;
        }
        else
        {
            t = pop();
            t = t->rchild;
        }
    }
}
// Function to find the minimum node in a subtree
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current->lchild != NULL)
        current = current->lchild;
    return current;
}

void deleteNode(struct Node* root, int key) {
    struct Node* current = root;
    struct Node* parent = NULL;
    struct Node* nodeToDelete = NULL;

    // Find the node to delete
    while (current != NULL) {
        if (key == current->data) {
            nodeToDelete = current;
            break;
        } else if (key < current->data) {
            parent = current;
            current = current->lchild;
        } else {
            parent = current;
            current = current->rchild;
        }
    }

    // If nodeToDelete is NULL, the key doesn't exist in the tree
    if (nodeToDelete == NULL)
        return;

    // Case 1: If the node to be deleted has no children
    if (nodeToDelete->lchild == NULL && nodeToDelete->rchild == NULL) {
        if (parent == NULL)
            root = NULL;
        else if (parent->lchild == nodeToDelete)
            parent->lchild = NULL;
        else
            parent->rchild = NULL;
        free(nodeToDelete);
    }
    // Case 2: If the node to be deleted has only one child
    else if (nodeToDelete->lchild == NULL || nodeToDelete->rchild == NULL) {
        struct Node* child = (nodeToDelete->lchild != NULL) ? nodeToDelete->lchild : nodeToDelete->rchild;
        if (parent == NULL)
            root = child;
        else if (parent->lchild == nodeToDelete)
            parent->lchild = child;
        else
            parent->rchild = child;
        free(nodeToDelete);
    }
    // Case 3: If the node to be deleted has two children
    else {
        struct Node* successor = findMinNode(nodeToDelete->rchild);
        nodeToDelete->data = successor->data;
        deleteNode(nodeToDelete->rchild, successor->data);
    }
}
void Inorder(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            push(t);
            t = t->lchild;
        }
        else{
            t = pop();
            printf("%d ", t->data);
            t = t->rchild;
        }
    }
}

void countNodes(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            push(t);
            t = t->lchild;
        }
        else{
            t = pop();
            count++;
            t = t->rchild;
        }
    }
    printf("%d", count);
}
int main() {
    int choice, key;
    struct Node *found;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Count Nodes\n");
        printf("8. Calculate Height\n");
        printf("9. Leaf Nodes\n");
        printf("10. Mirror Image\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteNode(root, key);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                found = Search(root, key);
                if (found != NULL)
                    printf("Value Found! Value is: %d\n", found->data);
                break;
            case 4:
                printf("Inorder Traversal: ");
                Inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                Preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                Postorder(root);
                printf("\n");
                break;
            case 7:
                count = 0;
                countNodes(root);
                printf("\nNumber of Nodes in the tree: %d\n", count);
                break;
            case 8:
                printf("Height of the tree is: %d\n", calculateHeight(root));
                break;
            case 9:
                printf("The leaf nodes are: ");
                leafCount(root);
                printf("\n");
                break;
            case 10:
                mirrorImage(root);
                printf("Mirror image created successfully.\n");
                break;
            case 11:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
