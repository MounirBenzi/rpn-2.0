
/* Function definitions */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "rpn.h"


/*function to print out the remaining stack values*/
void remainingToken(rational *stack, int *top){
	fprintf(stderr, "Tokens left on stack:\n");
	for (int j=0; j <= *top; j++){
		fprintf(stderr, "stack[%d] = ", j);
		rational_print(stack[j], 0);
		fputc('\n', stderr);
	}
}

/* chekcUnderflow checks that at least two elements are in the stack.
This function is called in the cases function*/
int checkUnderflow(char val, int *top){
	if(*top == 0){ //Checks to see if the stack pointer is on the second element, which means that there is only one element on the stack
		fprintf(stderr, "Stack underflow at \"%c\"\n", val);
		exit(1);
	}
	else{
		return 0;
	}
}

/* This function adds items to the stack and increments the top counter by one.
The top counter tells us where we are in the stack*/
int push(rational value, rational *stack, int *top){
	if(*top == 9){//checking to see if stack is full for stack overflow
			fprintf(stderr, "Stack overflow at \"");
			rational_print(value, 0); //used to print rational values
			fprintf(stderr, "\"\n");
			exit(1);
	}
	*top = *top + 1;
	stack[*top] = value;
	return 0;
}

/* This function removes items from the stack and checks if the stack is empty*/
rational pop(rational *stack, int *top){
	if (*top == -1){ //The pointer starts at -1, so if it is still at -1, the stack is empty and nothing can be removed.
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else{
		rational popped = stack[*top];
		*top = *top -1; //To remove an item from the stack we simply move the stack pointer down by 1
		return popped;
	}
}

int add(rational *stack, int *top){
	rational val1 = pop(stack, top); //We get the values from the stack by popping them off the stack
	rational val2 = pop(stack, top);
	push(rational_add(val2, val1), stack, top); //Adds the result of the operation back to the stack
	return 0;
}

int subtract(rational *stack, int *top){
	rational val1 = pop(stack, top);//We get the values from the stack by popping them off the stack
	rational val2 = pop(stack, top);
	push(rational_sub(val2, val1), stack, top);//Adds the result of the operation back to the stack
	return 0;
}


int multiplication(rational *stack, int *top){
	rational val1 = pop(stack, top);//We get the values from the stack by popping them off the stack
	rational val2 = pop(stack, top);
	push(rational_mul(val2, val1), stack, top);//Adds the result of the operation back to the stack
	return 0;
}


int division(rational *stack, int *top){
	rational val1 = pop(stack, top);//We get the values from the stack by popping them off the stack
	rational val2 = pop(stack, top);
	push(rational_div(val2, val1), stack, top);//Adds the result of the operation back to the stack
	return 0;
}

/*The cases function checks to whether a valid token has been entered by the
user. If not an error message is printed and the code is exitted  */
int cases(char token[], rational *stack, int *top){
	int size = strlen(token); //getting the size of of the entered token
	if(size > 1){//If the token length is greater than 1, print error
		fprintf(stderr, "Invalid token \"%s\"\n", token);
		exit(1);
	}
	switch(token[0]){//using a switch to check what argument was entered. where argv[0] is the operator
		case '+': //if + is entered
			if (*top==-1 && size==1){ //ensuring that an operator is not the first element
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){//checks for underflow
					add(stack, top);
					return 0;
				}
		case '-':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				subtract(stack, top);
				return 0;
			}
		case 'x':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				multiplication(stack, top);
				return 0;
			}
		case '/':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				division(stack, top);
				return 0;
			}
		default:
			fprintf(stderr, "Invalid token \"%s\"\n", token);
			exit(1);
	}
}

/*This function takes the user input, creates the stack and is what drives the
operations*/
int stackCreation(int argc, char*argv[]){
	rational stack[10]; //creates our stack
	rational fraction;
	int top = -1; // pointer to stack
	char *endptr; //pointer used to find the end of string in strtol
	for(int i=0; i<argc; i++){
		strtol(argv[i], &endptr, 10);
		/*Checks if the value is an integer.
		If there is no text in the entered argument and the first element
		is not '+' (accounts for arguments starting with +) then push to stack*/
		if (*endptr == '\0' && argv[0][0] != '+'){
			fraction = rational_from_bigint(bigint_from_string_d(argv[i]), bigint_from_string_d("1"));
			push(fraction, stack, &top);
		}
			else if(argv[0][0] != '/' && !isRational(argv[i])){
				push(rational_true(argv[i]), stack, &top);
			}
			else{ // if the argument is not an integer, check if its an operator
				cases(argv[i], stack, &top);
			}
	}
	//checks if there are multiple tokens left on the stack
	if (top != 0){
		remainingToken(stack, &top);
		return 1;
	}
	else{
		rational_print(rational_simplify(stack[0]), 1); //printing the final value on the stack
		return 0;
	}
}
