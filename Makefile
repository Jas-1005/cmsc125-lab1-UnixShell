# all: Compile the shell
# clean: Remove binaries and object files

CC=gcc
CFLAGS= -Wall


_OBJ = main.o parser.o executor.o
OBJ = $(_OBJ)

%.o: %.c parser.h executor.h command.h
	@$(CC) -c -o $@ $< $(CFLAGS)

all: myshell

myshell: $(OBJ)
	@$(CC) -o $@ $^

.PHONY: clean

clean: 
	@rm -f *.o myshell
