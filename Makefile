all: main
CFLAGS=-ansi -pedantic -Wall -g
CC=gcc

main.o: main.c
	gcc $(CFLAGS) -c main.c

main: main.o cube.o print_c.o
	gcc main.o cube.o print_c.o -o main

cube.o: cube.h
	gcc $(CFLAGS) -c cube.c

print_c.o: print_c.h
	gcc $(CFLAGS) -c print_c.c

clean:
	rm *.o