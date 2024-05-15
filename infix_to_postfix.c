#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int max = 30;

char stack[30];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == max - 1;
}

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if(top == -1)
    {
        return -1;
    }
    else{
        return stack[top--];
    }
}

int pre(char x)
{
    if ( x == '*' || x == '/')
    {
        return 2;
    }
    else if ( x == '+' || x == '-')
    {
        return 1;
    }
    return 0;
}

int isOperand(char x)
{
    if (x == '*' || x == '/' || x == '+' || x == '-')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char * InToPost (char *infix)
{
    char *postfix;
    int len = strlen(infix);
    int i =0, j =0;
    postfix =  (char *) malloc((len+2)*sizeof(char));

    while (infix[i] != '\0')
    {
        if(isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        else{
            if(pre(infix[i]) > pre(stack[top]))
            {
                push(infix[i++]);
            }
            else{
                postfix[j++] = pop();
            }
        }
    }

    while(top != -1)
    {
        postfix[j++] = pop();
    }
    postfix[j]= '\0';

    return postfix;
}


int main()
{
    char* infix;
    printf("Enter the expression: \n");

    // Allocate memory for the infix expression
    infix = (char*)malloc(max * sizeof(char));

    // Read the infix expression using fgets
    fgets(infix, max, stdin);

    // Remove the newline character if present
    infix[strcspn(infix, "\n")] = '\0';
    
    push('#'); //initially stack maybe empty and hence precedence cannot be checked in such a case
    //to tackle this, we push a random character in stack

    char *postfix = InToPost(infix);

    printf("%s ", postfix);

    return 0;
}



