#include <stdio.h>
#include <stdlib.h> 

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* insert(struct Node *root , int data) {
    if(root == NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if(data < root->data) {
        root->left = insert(root->left ,data);
    }
    else if(data > root->data) {
        root->right = insert(root->right ,data);
    }
    return root;
}

void inorder(struct Node *root) {
    if(root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void mirror(struct Node* root) {
    if (root == NULL) 
        return;
    
    struct Node* temp;
    mirror(root->left);
    mirror(root->right);
    
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

int height(struct Node* root) {
    if (root == NULL) 
        return -1;
    
    int max_height = -1;
    int current_height = -1;
    struct Node* stack[100];
    int height_stack[100];
    int top = -1;

    while (1) {
        while (root) {
            stack[++top] = root;
            root = root->left;
            current_height++;
            height_stack[top] = current_height;
            if (current_height > max_height) {
                max_height = current_height;
            }
        }

        if (top == -1) {
            break;
        }

        root = stack[top--];
        current_height = height_stack[top+1];

        root = root->right;
    }

    return max_height;
}

int main() {
    struct Node* root = NULL;

    int entrycode ;
    int data;
    int ele;

    printf("1 ==> insert_Node\n");
    printf("2 ==> Display original tree\n");
    printf("3 ==> Display Mirror Image without disturbing original tree\n");
    printf("4 ==> Height of the tree\n");
    printf("continue or not(1/0) : ");
    scanf("%d",&entrycode);

    do{
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
                printf("\nOriginal tree in inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("\nMirror Image without disturbing original tree:\n");
                mirror(root);
                inorder(root);
                printf("\n");
                mirror(root); // Restoring the original tree
                break;
            case 4:
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
