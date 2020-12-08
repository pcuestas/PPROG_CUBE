EXE=game
OBJ=cube.o solver.o print_c.o interface.o bcd.o terminal_funct.o cube_interface.o menu.o lib_funct.o lib_struct.o SDL_interface.o $(EXE).o

TEST=tests
OBJTEST=cube.o solver.o print_c.o interface.o bcd.o terminal_funct.o cube_interface.o menu.o $(TEST).o

LIB2=-lpthread -lSDL2main -lSDL2 -lSDL2_image -lglut -lGLU -lGL -lm -lSDL2_ttf

TEMPEXE=prueba
LIB=-lSDL2main -lSDL2 -lSDL2_ttf -lGLU -lGL 
OBJTEMPEXE=$(TEMPEXE).o cube.o print_c.o solver.o lib_funct.o lib_struct.o interface.o

CFLAGS=-ansi -pedantic -Wall -g
CC=gcc

HEADERS=*.h

all: $(EXE)

prueba: $(TEMPEXE)

run:
	./$(EXE)

run_lib: 
	./$(TEMPEXE)

$(TEST): $(OBJTEST) $(HEADERS)
	$(CC) $(OBJTEXT) $(LIB2) -o  $@

$(EXE): $(OBJ) $(HEADERS)
	$(CC) $(OBJ) $(LIB2) -o  $@

$(MENU): $(OBJ2) $(HEADERS)
	$(CC) $(OBJ2) -o $@

$(TEMPEXE): $(OBJTEMPEXE) $(HEADERS)
	$(CC) $(OBJTEMPEXE) $(LIB) $(LIB2) -o $@

#lib_struct.o: lib_struct.c lib_funct.h
#	$(CC) $(CFLAGS) -c $<
#
#print_c.o: print_c.c print_c.h interface.h cube.h
#	$(CC) $(CFLAGS) -c $<
#
#solver.o: solver.c solver.h cube.h
#	$(CC) $(CFLAGS) -c $<

%.o: %.c $(HEADERS)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXE) $(TEST) $(TEMPEXE) *.gch
cleantrash:
	rm -f *.o *.gch
