#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left, *right;
    int lbit, rbit;
    int childbit;
};
struct node *head = NULL;
struct node *root = NULL;

void insert(int val){
    struct node *temp;
    char direction;

    if(root==NULL){
        root = malloc(sizeof(struct node));
        root->left = root->right = head;
        root->data = val;
        root->lbit = root->rbit = 1;
        root->childbit=0;
        head->left = root;

    }
    else{
        struct node *newptr;
        int flag = 0;
        temp = root;
        do{
            if(val < temp->data){
                direction = 'l';
            }
            else{
                direction = 'r';
            }
            if(direction == 'l'){
                if(temp->lbit == 1){
                    //allocate new node
                    newptr = malloc(sizeof(struct node));
                    newptr->data = val;
                    newptr->lbit = newptr->rbit = 1;
                    newptr->childbit=0;
                    //join thread
                    newptr->left = temp->left;
                    newptr->right = temp;
                    temp->left = newptr;
                    temp->lbit = 0;
                    flag = 1;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(direction == 'r'){
                if(temp->rbit == 1){
                    //allocate new node
                    newptr = malloc(sizeof(struct node));
                    newptr->data = val;
                    newptr->lbit = newptr->rbit =1;
                    newptr->childbit=1;
                    //join thread
                    newptr->left = temp;
                    newptr->right = temp->right;
                    temp->right = newptr;
                    temp->rbit = 0;
                    flag = 1;
                }
                else{
                    temp = temp->right;
                }
            }
        } while(flag == 0);
    }
}

int n, i, val;
void create(){
    head = malloc(sizeof(struct node));
    head->left = head->right = NULL;
    head->lbit = head->rbit = 1;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("Node data: ");
        scanf("%d", &val);
        insert(val);
    }
}

struct node* in_successor(struct node *temp){
    if(temp->rbit == 1){
        return temp->right;
    }
    temp = temp->right;
    while(temp->lbit == 0){
        temp = temp->left;
    }
    return temp;
}

void inorder(){
    struct node *temp = head->left;
    while(temp->lbit != 1){
        temp = temp->left;
    }
    while(temp != head){
        printf("%d ", temp->data);
        temp = in_successor(temp);
    }
}

struct node* pre_succ(struct node* t){
    if(t->lbit==0){
        return t->left;
    }
    if(t->rbit==0){
        return t->right;
    }
    while(t->rbit==1){
        t=t->right;
        if (t==head){
            return t;
        }
        return t->right;
    }
}

void preorder(){
    struct node *temp = head->left;
    temp=root;
    while(temp!=head){
        printf("%d ",temp->data);
        temp=pre_succ(temp);
    }
}

struct node* post_successor(struct node *temp){
    if(temp->childbit == 1){
        while(temp->lbit == 0){
            temp = temp->left;
        }
        return temp->left;
    }
    else{ // temp is left child for the parent
        while(temp->rbit != 1){
            temp = temp->right;
        }
        temp = temp->right; // climb up
        if(temp->rbit == 1){
            return temp;
        }
        else{
            temp = temp->right;
            while(temp->lbit == 0 || temp->rbit == 0){
                while(temp->lbit == 0){
                    temp = temp->left;
                }
                if(temp->rbit == 0){
                    temp = temp->right;
                }
            }
            return temp;
        }
    }
    return temp;
};

void postorder(){
    struct node *temp = head->left;
    while(temp->lbit == 0 || temp->rbit == 0){
        while(temp->lbit == 0){
            temp = temp->left;
        }
        if(temp->rbit == 0){
            temp = temp->right;
        }
    }
    while(temp != head){
        printf("%d ", temp->data);
        temp = post_successor(temp);
    }
}


int main(){
    create();

    printf("\nInorder traversal: \n");
    inorder();
    printf("\nPreorder traversal: \n");
    preorder();
    printf("\nPostorder traversal: \n");
    postorder();
    return 0;
}
