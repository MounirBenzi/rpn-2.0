rpn.exe: rpnmain.c
	gcc -std=c99 -Wall rpnmain.c rpn.c rational.c bigint.c -o rpn.exe

test: rpn.exe
	python tests/runtests.py
