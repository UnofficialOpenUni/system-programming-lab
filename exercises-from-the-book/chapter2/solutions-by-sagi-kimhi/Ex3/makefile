TextToHx: main.o htoi.o 
	gcc -ansi -pedantic -Wall -g main.o htoi.o -o TextToHx -lm
main.o: main.c data.h
	gcc -c -ansi -pedantic -Wall -g main.c -o main.o
htoi.o: htoi.c data.h
	gcc -c -ansi -pedantic -Wall -g htoi.c -o htoi.o -lm
