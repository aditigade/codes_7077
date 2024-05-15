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

// function for postorder traversal without recursion
void postorder(struct Node* root){
    if(root == NULL)
        return;

    struct Node* stack[100];
    int top = -1;
    struct Node* prev = NULL;

    do{
        while(root != NULL){
            stack[++top] = root;
            root = root->left;
        }

        while(root == NULL && top != -1){
            root = stack[top];

            if(root->right == NULL || root->right == prev){
                printf("%d ",root->data);
                top--;
                prev = root;
                root = NULL;
            }else{
                root = root->right;
            }
        }
    }while(top != -1);
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

    printf("1 ==> Insert Node ,  2 ==> Mirror Image , 3 ==> Find Node , 4 ==>> Postorder Traversal\n");
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
                postorder(mirrorimage);
                printf("\n");
                break;
            case 3:
                printf("\nEnter data to find: ");
                scanf("%d", &data);
                if (search(root, data) != NULL)
                    printf("\n%d is found in the tree\n", data);
                else
                    printf("\n%d is not found in the tree\n", data);
                break;
            case 4:
                printf("\nPostorder Traversal: ");
                postorder(root);
                printf("\n");
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
