CFLAGS=-ansi -pedantic -Wall -g
CC=gcc
OBJ=cube.o solver.o print_c.o cube_interface.o
OBJ2=menu_interface.o menu.o interface.o
HEADERS=cube.h solver.h print_c.h types.h menu.h interface.h
MENU=menu_interface
EXE=cube_interface
LIB=-lSDL2main -lSDL2 -lSDL2_image -lglut -lGLU -lGL -lm

all: $(EXE)

menui: $(MENU)

game: 
	./$(EXE)

$(EXE): $(OBJ) $(HEADERS)
	$(CC) $(OBJ) -o $(EXE)

$(MENU): $(OBJ2) $(HEADERS)
	$(CC) $(OBJ2) -o $(MENU)

main: main.o cube.o print_c.o
	$(CC) main.o cube.o print_c.o -o main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXE) $(MENU) *.gch
cleantrash:
	rm -f *.o *.gch
