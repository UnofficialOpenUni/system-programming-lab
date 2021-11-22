all: GenerateLine LongestLine

GenerateLine: GenerateLine.o
	gcc -ansi -pedantic -Wall -g GenerateLine.o -o GenerateLine
GenerateLine.o: GenerateLine.c
	gcc -c -ansi -pedantic -Wall -g GenerateLine.c -o GenerateLine.o
LongestLine: LongestLine.o
	gcc -ansi -pedantic -Wall -g LongestLine.o -o LongestLine
LongestLine.o: LongestLine.c
	gcc -c -ansi -pedantic -Wall -g LongestLine.c -o LongestLine.o
