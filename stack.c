// C program for array implementation of stack
// Source : https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
// Modified by : Sigitbn

#include <stdio.h>
#include <stdlib.h>
#include "stack1D.h"
#include "stack.h"

int isEmpty(struct Stack *stack) { return stack->top == -1; }

struct Stack *createStack(unsigned capacity) {
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Stack1D **) (struct Stack1D *) malloc(
            stack->capacity * stack->capacity * sizeof(struct Stack1D));
    return stack;
}

int isFull(struct Stack *stack) { return stack->top == stack->capacity - 1; }

void push(struct Stack *stack, struct Stack1D *item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

struct Stack1D * pop(struct Stack *stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

