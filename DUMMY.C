#include<stdio.h>
#include<stdlib.h>
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int lthread;
    int rthread;
};
struct TreeNode *createNode(int data) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->lthread=1;
    newNode->rthread=1;
    return newNode;
}
void insertnode(struct TreeNode * root, int x){
    struct TreeNode * parent,*temp=root;
    struct TreeNode* newNode=createNode(x);
    while(1){
        if(x<temp->data){
            if(temp->lthread==1){
                newNode->left=temp->left;
                temp->left=newNode;
                temp->lthread=0;
                newNode->right=temp;
                printf("Node attached to left of %d\n",temp->data);
                return;
            }
            temp=temp->left;
        }
        else{
            if(temp->rthread==1){
                newNode->right=temp->right;
                temp->right=newNode;
                temp->rthread=0;
                newNode->left=temp;
                printf("Node attached to right of %d\n",temp->data);
                return;
            }
            temp=temp->right;
        }
    }
}
struct TreeNode* buildTree() {
    int data;
    struct TreeNode* head = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    head->lthread=1;
    head->rthread=1;

    struct TreeNode* root = NULL,*temp;
    do{
        printf("Enter the value of the node (-1 to stop): ");
        scanf("%d", &data);
        if (data == -1)
            return root;
        if(root==NULL){
            root = createNode(data);
            root->left=head;
            root->right=head;
            head->left=root;
            head->lthread=0;
            head->rthread=-1;
            printf("Root Created\n");
        }
        else{
            insertnode(root,data);
        }
    }while (data!=-1);
    return root;
}
void inorderTraversal(struct TreeNode *root) {
    struct TreeNode * temp=root;
    while(temp->lthread!=1){
        temp=temp->left;
    }
    while(temp->rthread!=-1){
        printf("%d ",temp->data);
        if(temp->rthread==1)
        temp=temp->right;
        else{
            temp=temp->right;
            while (temp->lthread==0){
                temp=temp->left;
            }  
        }
    }
}
void preorder(struct TreeNode *root){
    struct TreeNode * temp=root;
    int x=0;
    while(temp->rthread!=-1){
        printf("%d ",temp->data);
        if(temp->lthread==0)
        temp=temp->left;
        else if(temp->rthread==0){
            temp=temp->right;
        }
        else{
            while (temp->rthread==1){
                temp=temp->right;
                if(temp->rthread==-1)
                return;
            }
            temp=temp->right;
        }
    }
}
void postorder(struct TreeNode *root){
    if (root == NULL)
        return;

    struct TreeNode *temp = root->left;

    while (temp != NULL) {
        if (!temp->lthread) {
            temp = temp->left;
        } else if (!temp->rthread) {
            temp = temp->right;
        } else {
            printf("%d ", temp->data);
            if (temp->right == root) {
                return;
            }
            while (temp->rthread && temp->right != root) {
                temp = temp->right;
            }
            temp = temp->right;
        }
    }
}

int main() {
    struct TreeNode *root = buildTree();
    printf("Inorder Traversal:");
    inorderTraversal(root);
    printf("\nPreOrder Traversal:");
    preorder(root);
    printf("\nPostOrder Traversal:");
    postorder(root);
}
/* 
     10
    / \
   7   12
   \   / \
   9  11  15
   /      /
  8      13
          \
          14
*/