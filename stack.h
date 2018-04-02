// C program for array implementation of stack
// Source : https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
// Modified by : Sigitbn
#include "stack1D.h"

#ifndef MAP_GFS_STACK_H
#define MAP_GFS_STACK_H

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    struct Stack1D **array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack *createStack(unsigned capacity);

// Stack is full when top is equal to the last index
int isFull(struct Stack *stack);

// Stack is empty when top is equal to -1
int isEmpty(struct Stack *stack);

// Function to add an item to stack.  It increases top by 1
void push(struct Stack *stack, struct Stack1D *item);

// Function to remove an item from stack.  It decreases top by 1
struct Stack1D *pop(struct Stack *stack);

#endif //MAP_GFS_STACK_H
