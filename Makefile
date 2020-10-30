CFLAGS=-ansi -pedantic -Wall -g
CC=gcc
OBJ=cube.o solver.o print_c.o cube_interface.o
OBJ2=menu_interface.o menu.o interface.o
HEADERS=cube.h solver.h print_c.h types.h menu.h interface.h
MENU=menu_interface
EXE=cube_interface

all: $(EXE) cleantrash

menu: $(MENU)

$(EXE): $(OBJ) $(HEADERS)
	gcc $(OBJ) -o $(EXE)

$(MENU): $(OBJ2) $(HEADERS)
	gcc $(OBJ2) -o $(MENU)

main: main.o cube.o print_c.o
	gcc main.o cube.o print_c.o -o main

%.o: %.c %.h
	gcc $(CFLAGS) -c $^

clean:
	rm -f *.o $(EXE) $(MENU) *.gch
cleantrash:
	rm -f *.o *.gch