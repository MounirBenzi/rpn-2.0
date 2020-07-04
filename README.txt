
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
