#include <stdio.h>
#include "rational.h"

/*Checks for tokens left in stack*/
void remainingToken(rational *stack, int *top);

/*Checks for stack underflow*/
int checkUnderflow(char val, int *top);

/*Pushes elements onto stack*/
int push(rational value,	rational *stack, int *top);

/*Removes the last element off of the stack*/
rational pop(rational *stack, int *top);

/*Adds the last two elements in the stack*/
int add(rational *stack, int *top);

/*Subtracts the last two elements in the stack*/
int subtract(rational *stack, int *top);

/*Multiplies the last two elements in the stack*/
int multiplication(rational *stack, int *top);

/*Divides the last two elements in the stack*/
int division(rational *stack, int *top);

/*Checks if the argument entered by the user is a operator*/
int cases(char token[], rational *stack, int *top);

/*Creates the stack and does basic checks*/
int stackCreation(int argc, char*argv[]);
