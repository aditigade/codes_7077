#include<stdio.h>
#include<stdlib.h>

// creating structure to store treenode info
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

// function to create Node
struct Node* buildtree(int data){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// function for insert node
struct Node* insert(struct Node* root,int data){
    if(root == NULL){
        return buildtree(data);
    }

    if(data < root->data){
        root->left = insert(root->left,data);
    }
    else if(data > root->data){
        root->right = insert(root->right,data);
    }

    return root;
}

// function for search
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
}

// function for mirror image
struct Node* mirror(struct Node* root){
    if(root == NULL){
        return NULL;
    }

    struct Node* newnode = buildtree(root->data);

    newnode->right = mirror(root->left);
    newnode->left = mirror(root->right);

    return newnode;
}

// function for preorder traversal without recursion
void preorder(struct Node* root){
    if(root == NULL)
        return;

    struct Node* stack[100];
    int top = -1;

    do{
        while(root != NULL){
            printf("%d ", root->data);
            stack[++top] = root;
            root = root->left;
        }

        if(top != -1){
            root = stack[top--];
            root = root->right;
        }
    }while(top != -1);
}

// function for inorder traversal without recursion
void inorder(struct Node* root){
    if(root == NULL)
        return;

    struct Node* stack[100];
    int top = -1;

    do{
        while(root != NULL){
            stack[++top] = root;
            root = root->left;
        }

        if(top != -1){
            root = stack[top--];
            printf("%d ", root->data);
            root = root->right;
        }
    }while(top != -1);
}

// function for counting leaf nodes
int countLeafNodes(struct Node* root){
    if(root == NULL)
        return 0;

    if(root->left == NULL && root->right == NULL)
        return 1;
    else
        return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// driver function
int main(){

    struct Node* root = NULL;

    int entrycode ;
    int data;
    int key;
    int ele;
    int flag;

    struct Node* mirrorimage;

    printf("1 ==> Insert Node ,  2 ==> Mirror Image , 3 ==> Preorder Traversal , 4 ==>> Inorder Traversal\n");
    printf("5 ==> Count Leaf Nodes\n");
    printf("\ncontinue or not(1/0) : ");
    scanf("%d",&entrycode);

    do {
        if (entrycode == 0)
            exit(0);

        printf("\nEnter option : ");
        int option;
        scanf("%d",&option);

        switch(option) {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&data);
                root = insert(root, data);
                break;
            case 2:
                mirrorimage = mirror(root);
                printf("\nMirror Image: \n");
                preorder(mirrorimage);
                printf("\n");
                break;
            case 3:
                printf("\nPreorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("\nInorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("\nNumber of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            default:
                printf("\nEnter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    } while(entrycode != 0);

    return 0;
}
