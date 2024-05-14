#include <stdio.h>
#include <stdlib.h>

struct Stack {
    unsigned long long *array;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (unsigned long long*)malloc(stack->capacity * sizeof(unsigned long long));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, unsigned long long item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

unsigned long long pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

unsigned long long factorial(int n) {
    struct Stack* s = createStack(n);
    unsigned long long fact = 1;

    for (int i = 1; i <= n; ++i) {
        push(s, i);
    }

    while (!isEmpty(s)) {
        fact *= pop(s);
    }

    free(s->array);
    free(s);

    return fact;
}

void fibonacci(int n) {
    struct Stack* s = createStack(n);
    unsigned long long prev = 0, curr = 1;

    push(s, curr);
    push(s, prev);

    printf("Fibonacci series up to %d terms: ", n);

    for (int i = 0; i < n; ++i) {
        unsigned long long next = prev + curr;
        printf("%llu ", prev);
        prev = curr;
        curr = next;
        push(s, next);
    }
    printf("\n");

    free(s->array);
    free(s);
}

int main() {
    int num;

    printf("Enter a number to calculate factorial: ");
    scanf("%d", &num);
    printf("Factorial of %d is: %llu\n", num, factorial(num));

    printf("Enter the number of terms in Fibonacci series: ");
    scanf("%d", &num);
    fibonacci(num);

    return 0;
}
