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

// function to find the minimum value node in a tree
struct Node* minValueNode(struct Node* node)
{
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// function to delete the node with given data
struct Node* deleteNode(struct Node* root, int data)
{
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // if key is same as root's key, then This is the node to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// function for inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// driver function
int main() {

    struct Node* root = NULL;
    int entrycode ;
    int data;
    int key;
    int ele;
    int parentnode;
    int position;
    int flag;

    printf("1 ==> Insert Node ,  2 ==> Delete Node , 3 ==> Find Node , 4 ==>> Display Inorder\n");
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
                printf("\nEnter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
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
                printf("\nInorder Traversal: ");
                inorder(root);
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
