//
// Created by sigitbn on 3/26/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack1D.h"

struct Stack1D *createStack1D(unsigned capacity) {
    struct Stack1D *stack1D = (struct Stack1D *) malloc(sizeof(struct Stack1D));
    stack1D->capacity = capacity;
    stack1D->top = -1;
    stack1D->array = (int *) malloc(stack1D->capacity * stack1D->capacity * sizeof(int));
    return stack1D;
}

int isStack1DEmpty(struct Stack1D *stack1D) { return stack1D->top == -1; }

int isStack1DFull(struct Stack1D *stack1D) { return stack1D->top == stack1D->capacity - 1; }

void stack1DPush(struct Stack1D *stack1D, int item) {
    if (isStack1DFull(stack1D))
        return;
    stack1D->array[++stack1D->top] = item;
//    printf("%d pushed to stack1D\n", item);
}

int stack1DPop(struct Stack1D *stack1D) {
    if (isStack1DEmpty(stack1D))
        return -1;
    return stack1D->array[stack1D->top--];
}

