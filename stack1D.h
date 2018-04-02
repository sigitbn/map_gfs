//
// Created by sigitbn on 3/26/18.
//

#ifndef MAP_GFS_SOLUTION_H
#define MAP_GFS_SOLUTION_H

// function to create a stack of given capacity. It initializes size of
// stack as 0
// A structure to represent a stack1D with stack
struct Stack1D {
    int top;
    unsigned capacity;
    int *array;
};

struct Stack1D* createStack1D(unsigned capacity);

// Stack1D is full when top is equal to the last index
int isStack1DFull(struct Stack1D *stack);

// Stack1D is empty when top is equal to -1
int isStack1DEmpty(struct Stack1D *stack);

// Function to add an item to stack.  It increases top by 1
void stack1DPush(struct Stack1D *stack, int item);

// Function to remove an item from stack.  It decreases top by 1
int  stack1DPop(struct Stack1D *stack);

#endif //MAP_GFS_SOLUTION_H
