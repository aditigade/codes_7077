#include<stdio.h>
#include<stdlib.h> 

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* buildtree(int data){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
   
    return newNode;
}

struct Node* insert(struct Node *root , int data){

    if(root == NULL){
        return buildtree(data);
    }

    if(data < root->data){
        root->left = insert(root->left ,data);
    }
    else if(data > root->data){
        root->right = insert(root->right ,data);
    }
    return root;
}

void inorder(struct Node *root){
    if(root == NULL){
        return;
    }

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while(current != NULL || top != -1) {
        while(current !=  NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

int countNodesOnLongestPath(struct Node* root) {
    if(root == NULL)
        return 0;

    struct Node* queue[100];
    int front = -1, rear = -1;
    int count = 0;
    
    queue[++rear] = root;
    while(front <= rear) {
        int level_nodes = rear - front;
        count = level_nodes;
        for(int i = 0; i <= level_nodes; i++) {
            struct Node* current = queue[++front];
            if(current->left != NULL)
                queue[++rear] = current->left;
            if(current->right != NULL)
                queue[++rear] = current->right;
        }
    }
    return count;
}

void levelOrder(struct Node* root) {
    if(root == NULL)
        return;

    struct Node* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;
    while(front <= rear) {
        struct Node* current = queue[++front];
        printf("%d ", current->data);
        if(current->left != NULL)
            queue[++rear] = current->left;
        if(current->right != NULL)
            queue[++rear] = current->right;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* root) {
    if(root == NULL)
        return 0;

    struct Node* queue[100];
    int front = -1, rear = -1;
    int height = 0;

    queue[++rear] = root;
    while(front <= rear) {
        int level_nodes = rear - front;
        height++;
        for(int i = 0; i <= level_nodes; i++) {
            struct Node* current = queue[++front];
            if(current->left != NULL)
                queue[++rear] = current->left;
            if(current->right != NULL)
                queue[++rear] = current->right;
        }
    }
    return height;
}

int main() {
    struct Node* root = NULL;

    int entrycode ;
    int data;

    printf("1 ==> insert_Node  , 2 ==> Inorder Traversal  , 3 ==> Count nodes on longest path\n");
    printf("4 ==> Display Tree Levelwise  , 5 ==> Display Height of Tree\n");
    printf("continue or not(1/0) : ");
    scanf("%d",&entrycode);

    do {
        if(entrycode == 0) {
            exit(0);
        }
        printf("\nenter option : ");
        int option;
        scanf("%d",&option);
      
        switch(option) {
            case 1:
                printf("\nenter data : ");
                scanf("%d",&data);
                root = insert(root,data);
                break;
            case 2:
                printf("\nInorder Travesal : ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("\nCount of nodes on longest path: %d\n", countNodesOnLongestPath(root));
                break;
            case 4:
                printf("\nTree Levelwise Traversal: ");
                levelOrder(root);
                printf("\n");
                break;
            case 5:
                printf("\nHeight of the tree: %d\n", height(root));
                break;
            default :
                printf("\nenter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    } while(entrycode != 0);
}
