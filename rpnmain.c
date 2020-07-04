/* Importing Modules*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "rpn.h"

int main(int argc, char *argv[]){
	if(argc == 2 && !strcmp(argv[1], "--version")){
		printf("2.0\n");
		return 0;
	}
	else if(argc == 2 && !strcmp(argv[1], "--usage")){
		printf("./rpn.exe --usage\n");
		printf("./rpn.exe --version\n");
		printf("./rpn.exe TOKENS...\n");
		return 0;
	}
	else if(argc == 1){
		fprintf(stderr, "./rpn.exe --usage\n");
		fprintf(stderr,"./rpn.exe --version\n");
		fprintf(stderr,"./rpn.exe TOKENS...\n");
		return 1;
	}
	else {
		 return stackCreation(argc-1, argv+1);
	}
}
