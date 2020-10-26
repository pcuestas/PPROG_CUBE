CFLAGS=-ansi -pedantic -Wall -g
CC=gcc
OBJ=cube.o solver.o print_c.o cube_interface.o
HEADERS=cube.h solver.h print_c.h
EXE=cube_interface


all: $(EXE)

$(EXE): $(OBJ) $(HEADERS)
	gcc $(OBJ) -o $(EXE)

main: main.o cube.o print_c.o
	gcc main.o cube.o print_c.o -o main

%.o: %.c %.h
	gcc $(CFLAGS) -c $^


clean:
	rm -f *.o $(EXE)