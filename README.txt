Author: Mounir Benzineb
Date: 4/04/2019
Description: This is a Reverse Polish Notation Calculator, which is capable of basic arithmetic: addition, subtraction, multiplication and division.
	      The calculator also handles big integers, and now also rational numbers.
              Users should enter operands and operators, making sure no illegal operators have been entered. Allowed operators are (+ , -, x, /)
              The correct number of operators should be used according to how many operands have been entered. It should be noted that there is a maximum of 10 operands.

Usage: This program can be executed from the command line, using the line:  $ ./rpn.exe operands... operators

            For example, basic addition would be carried out as such:
            $ ./rpn.exe 1 1 1 + +
            3
            To demonstrate subtraction:
            $ ./rpn.exe 8 6 1 - -
            3
            This can be slightly confusing, but this operation works as 8 - (6-1)
            The multiplication operator is x
            $ ./rpn.exe 5 6 1 x x
            30
            Program can handle rational numbers, and simplifies
            $ ./rpn.exe 14 3 /
            7/3
            $ ./rpn.exe 7 0 /
            Zero division in 7 / 0
	    Program can handle values outside the range of int
	    $./rpn.exe 10000000000000000000 100000000000000000 /
	    100

            It is also possible to see the version of the program, using:
            $ ./rpn.exe --version
            The usage of the program can also be shown by running
            $ ./rpn.exe --usage

Implementation: All of the functions for the operators, the stack and error checking functions have been implemented and are working. 
		Along with the rational numbers and bigint data types.

Changelog: Changelog:  09 Mar 2019 - Created the stack and its functions.
		       10 Mar 2019 - Created cases function to deal with the various tokens
                       11 Mar 2019 - Altered code to no longer use global variables. In hindsight this should have been done at the very beginning
		       11 Mar 2019 - Created Underflow function and altered my functions to check and deal with overflow and invalid tokens
                       12 Mar 2019 - Fixed bug in cases where arguments leading with an operator would cause the case to run
                       13 Mar 2019 - Added the remainingToken function used tot print out the tokens left on the stack
                       14 Mar 2019 - Fixed bug in detecting operators using the strtol function.
		       02 Apr 2019 - Functions were altered to allow the use of big ints using the bigint typedef provided
		       03 Apr 2019 - Created the rational struct, to allow the usage of rational number	
		       03 Apr 2019 - Began creating the necesary functions to allow for rational number arithmetic and manipulation
		       03 Apr 2019 - Functions were altered again to allow the usage of rational numbers, therefore the stack type had to also be changed into a rational stack
		       04 Apr 2019 - Fized a bug in my rational_print function which caused an additional print line to be printed
		       04 Apr 2019 - Implemented a rational simplifying function using the idea of a gcd.
		       04 Apr 2019 - Fixed an issue where the simplifying function could not handle negative numbers using the .s variable in the bigint struct.

