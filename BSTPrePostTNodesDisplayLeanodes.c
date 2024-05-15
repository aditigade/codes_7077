#include <stdio.h>
#include <stdlib.h> 

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* buildtree(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node *root , int data) {
    if(root == NULL) {
        return buildtree(data);
    }

    if(data < root->data) {
        root->left = insert(root->left ,data);
    }
    else if(data > root->data) {
        root->right = insert(root->right ,data);
    }
    return root;
}

void preorder(struct Node* root) {
    if(root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    
    stack[++top] = root;
    
    while(top >= 0) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);
        
        if(current->right != NULL)
            stack[++top] = current->right;
        if(current->left != NULL)
            stack[++top] = current->left;
    }
}

void postorder(struct Node *root) {
    if(root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* prev = NULL;
    do {
        while(root != NULL) {
            stack[++top] = root;
            root = root->left;
        }
        while(root == NULL && top != -1) {
            root = stack[top];
            if(root->right == NULL || root->right == prev) {
                printf("%d ",root->data);
                top--;
                prev = root;
                root = NULL;
            }
            else {
                root = root->right;
            }
        }
    } while(top != -1);
}

int countNodes(struct Node* root) {
    if(root == NULL)
        return 0;

    struct Node* stack[100];
    int top = -1;
    int count = 0;

    stack[++top] = root;
    while(top >= 0) {
        struct Node* current = stack[top--];
        count++;
        if(current->right != NULL)
            stack[++top] = current->right;
        if(current->left != NULL)
            stack[++top] = current->left;
    }
    return count;
}

void leafNodes(struct Node* root) {
    if(root == NULL)
        return;

    struct Node* stack[100];
    int top = -1;

    stack[++top] = root;
    while(top >= 0) {
        struct Node* current = stack[top--];
        if(current->left == NULL && current->right == NULL)
            printf("%d ", current->data);
        if(current->right != NULL)
            stack[++top] = current->right;
        if(current->left != NULL)
            stack[++top] = current->left;
    }
}

int main() {
    struct Node* root = NULL;

    int entrycode ;
    int data;

    printf("1 ==> insert_Node  , 2 ==> Preorder Traversal  , 3 ==> Postorder Traversal\n");
    printf("4 ==> Total Number of Nodes  , 5 ==> Display Leaf Nodes\n");
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
                printf("\nPreorder Traversal : ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("\nPostorder Traversal : ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("\nTotal Number of Nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("\nLeaf Nodes are :  ");
                leafNodes(root);
                printf("\n");
                break;
            default :
                printf("\nenter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    } while(entrycode != 0);
}
