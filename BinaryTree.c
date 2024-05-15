#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 1000

// Stack structure to hold Node pointers
struct Node* stack[MAX];
int top = -1;
int count = 0;

struct Node 
{
    struct Node *lchild;
    int data;
    struct Node *rchild;
} *root=NULL ;

int isEmpty()
{
    if(top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull()
{
    if (top == MAX)
    {
        return 1;
    }
    else{
        return 0;
    }
}

struct Node *pop()
{   
    if(!isEmpty())
    {
        return stack[top--];
    }
    else
    {
        printf("Stack is empty");
        //return NULL;
        return 0;
    }
}

void push(struct Node *t)
{
    if(!isFull())
    {
        top = top + 1;
        stack[top] = t;
    }
    else
    {
        printf("Stack is full");
    }
}

void Insert(int key)
{
    struct Node *p;
    struct Node *r;

    if(root==NULL)
    {
        p=(struct Node *)malloc(sizeof(struct Node));
        p->data = key;
        p->lchild = p->rchild = NULL;
        root = p;
        return;
    }
    
    else
    {
        struct Node *t=root;
        char direction;
        int flag=0;
        do
        {
            if(t!=NULL)
            {
                printf("Do you want to insert the node to the left or right of %d", t->data);
                printf(" ?\n");
                scanf(" %c",&direction);
            }

            if(direction=='l')
            {
                if(t==NULL)
                {
                    p = (struct Node *)malloc(sizeof(struct Node));
                    r->lchild = p;
                    p->data=key;
                    p->lchild = p->rchild = NULL;
                    flag=1;
                }
                else{
                    r = t;
                    t = t->lchild;
                }
            }

            else if(direction=='r')
            {
                if(t==NULL)
                {
                    p = (struct Node *)malloc(sizeof(struct Node));
                    r->rchild=p;
                    p->data=key;
                    p->lchild = p->rchild = NULL;

                    flag=1;
                }
                else{
                    r = t;
                    t = t->rchild;
                }
            }

        } while (flag!=1);    
    }
}

void Preorder(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            printf("%d ", t->data);
            push(t);
            t = t->lchild;
        }
        else
        {
            t = pop();
            t = t->rchild;
        }
    }
}

void Inorder(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            push(t);
            t = t->lchild;
        }
        else{
            t = pop();
            printf("%d ", t->data);
            t = t->rchild;
        }
    }
}

void countNodes(struct Node *t)
{
    while(t!=NULL || !isEmpty())
    {
        if(t!=NULL)
        {
            push(t);
            t = t->lchild;
        }
        else{
            t = pop();
            count++;
            t = t->rchild;
        }
    }
    printf("%d", count);
}

// Postorder traversal using a stack
void Postorder(struct Node *t) {
    struct Node* lastVisited = NULL; //to maintain the last visited node

    while (t != NULL || !isEmpty()) {
        if (t != NULL) {
            push(t); // First push
            t = t->lchild;
        } else {
            struct Node* node = stack[top]; //peek
            if (node->rchild != NULL && lastVisited != node->rchild) {
                // If right child exists and traversing node first time
                t = node->rchild;
            } else {
                printf("%d ", node->data);
                lastVisited = pop();
            }
        }
    }
}

// Queue implementation for level order traversal
struct Node* queue[MAX];
int front = -1;
int rear = -1;

int isQueueEmpty() {
    return front == rear;
}

void enqueue(struct Node* t) {
    if(rear < MAX - 1) {
        queue[++rear] = t;
    }
}

struct Node* dequeue() {
    if(!isQueueEmpty()) {
        return queue[++front];
    }
    return NULL;
}

void levelorder(struct Node *t)
{
    if(t == NULL) 
        return;

    enqueue(t);

    while(!isQueueEmpty()) 
    {
        t = dequeue();
        printf("%d ", t->data);

        if(t->lchild != NULL) 
            enqueue(t->lchild);
        if(t->rchild != NULL) 
            enqueue(t->rchild);
    }
}

int calculateHeight(struct Node *root) {
    if (root == NULL) 
        return 0;

    enqueue(root);
    int height = 0;

    while (1) {
        int nodeCount = rear - front; // Number of nodes at current level
        if (nodeCount == 0) // If no nodes left in the queue
            return height;

        height++; // Increment height for each level

        // Dequeue all nodes of the current level and enqueue all nodes of the next level
        while (nodeCount > 0) {
            struct Node* node = dequeue();
            if (node->lchild != NULL)
                enqueue(node->lchild);
            if (node->rchild != NULL)
                enqueue(node->rchild);
            nodeCount--;
        }
    }
}

int main()
{
    int key;
    int x = 0;

    do
    {
        char ans;
        printf("Do you want to Insert a Node?\n");
        scanf(" %c",&ans);
        if(ans=='y')
        {
            printf("Enter the value to be inserted ");
            scanf("%d",&key);
            Insert(key);
        }
        else{
            x=1;
        }
    } while (x!=1);
    
    int height;

    printf("\nPostorder Traversal: ");
    Postorder(root);

    printf("\nPreorder Traversal: ");
    Preorder(root);

    printf("\nInorder Traversal: ");
    Inorder(root);

    printf("\nLevelorder Traversal: ");
    levelorder(root);

    printf("\nNumber of Nodes in the tree: ");
    countNodes(root);

    printf("\nHeight of the tree is: ");
    height = calculateHeight(root);
    printf("%d",height);

    return 0;
}
