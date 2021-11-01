ParTester: par.o parstack.o
	gcc -ansi -pedantic -Wall -g par.o parstack.o -o ParTester
parstack.o: parstack.c stackdata.h
	gcc -c -ansi -pedantic -Wall -g parstack.c -o parstack.o
par.o: par.c stackdata.h
	gcc -c -ansi -pedantic -Wall -g par.c -o par.o
