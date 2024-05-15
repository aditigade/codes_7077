#include<stdio.h>
#include<stdlib.h> 

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* insert(struct Node *root , int data){

    if(root == NULL){
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
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

void postorder(struct Node *root){
    if(root == NULL){
        return;
    }
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
            }
            else{
                root = root->right;
            }
        }
    }while(top != -1);
}

int main(){

    struct Node* root = NULL;

    int entrycode ;
    int data;
    int ele;

    printf("1 ==> insert_Node  , 2 ==> Delete_node\n");
    printf("3 ==> Postorder Traversal\n");
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
                deleteNode(root,ele);
                break;
            case 3:
                printf("\nPostorder Traversal : ");
                postorder(root);
                printf("\n");
                break;
            default :
                printf("\nenter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    }while(entrycode != 0);
}
