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

struct Node* inodersucc(struct Node* root){
    
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

struct Node* deleteNode(struct Node* root, int k)
{
    if (root == NULL){
        return root;
    }

    if (root->data > k) {
        root->left = deleteNode(root->left, k);
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            return NULL;
        }
        if (root->left == NULL) {
            return root->right;
        }
        else if (root->right == NULL) {
            return root->left;
        }
        else{
            struct Node* inordersuccnode = inodersucc(root->right);
            root->data = inordersuccnode->data;
            root->right = deleteNode(root->right,inordersuccnode->data);
        }
    }
    return root;
}

// function for level order traversal
void levelOrder(struct Node* root) {
    if (root == NULL) return;
    
    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;
    queue[++rear] = NULL;
    
    while (front != rear - 1) {
        struct Node* current = queue[++front];
        if (current == NULL) {
            if (front != rear - 1) {
                queue[++rear] = NULL;
                printf("\n");
            }
        } else {
            printf("%d ", current->data);
            if (current->left != NULL) queue[++rear] = current->left;
            if (current->right != NULL) queue[++rear] = current->right;
        }
    }
}

int main(){

    struct Node* root = NULL;

    int entrycode ;
    int data;
    int key;
    int ele;


    printf("1 ==> insert_Node  , 2 ==> Delete_node\n");
    printf("3 ==> Level Order Traversal\n");
    printf("continue or not(1/0) : ");
    scanf("%d",&entrycode);

    do{
        if(entrycode == 0){
            exit(0);
        }
        printf("\nenter option : ");
        int option;
        scanf("%d",&option);

        switch(option){
            case 1:
                printf("\nenter data : ");
                scanf("%d",&data);
                root = insert(root,data);
                break;
            case 2:
                printf("\nenter element : ");
                scanf("%d",&ele);
                root = deleteNode(root,ele);
                break;
            case 3:
                printf("\nLevel Order Traversal : ");
                levelOrder(root);
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
