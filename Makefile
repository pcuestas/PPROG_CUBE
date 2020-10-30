CFLAGS=-ansi -pedantic -Wall -g
CC=gcc
OBJ=cube.o solver.o print_c.o cube_interface.o
OBJ2=cube.o solver.o print_c.o menu_interface.o
MENU=menu_interface
EXE=cube_interface

all: $(EXE)

menu: $(MENU)

$(EXE): $(OBJ) $(HEADERS)
	gcc $(OBJ) -o $(EXE)

$(MENU): $(OBJ) $(HEADERS)
	gcc $(OBJ) -o $(MENU)

main: main.o cube.o print_c.o
	gcc main.o cube.o print_c.o -o main

%.o: %.c %.h
	gcc $(CFLAGS) -c $^

clean:
	rm -f *.o $(EXE) $(MENU) *.gch