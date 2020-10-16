all: cube_interface
CFLAGS=-ansi -pedantic -Wall -g
CC=gcc


cube_interface: cube_interface.o cube.o print_c.o
	gcc cube_interface.o cube.o print_c.o -o cube_interface

cube_interface.o: cube_interface.c
	gcc $(CFLAGS) -c cube_interface.c


main: main.o cube.o print_c.o
	gcc main.o cube.o print_c.o -o main

main.o: main.c
	gcc $(CFLAGS) -c main.c



cube.o: cube.h
	gcc $(CFLAGS) -c cube.c

print_c.o: print_c.h
	gcc $(CFLAGS) -c print_c.c

clean:
	rm *.o