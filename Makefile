CC = g++
CFLAGS = --std=c++11 -pedantic -lncurses -ltinfo -Wall 
SRC = main.cpp engine.cpp net.cpp lot.cpp
BIN = a.out

all:
	$(CC) $(SRC) $(CFLAGS) -o $(BIN)

release:
	$(CC) $(SRC) --static $(CFLAGS) -o $(BIN)

check_leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)

install:
	sudo cp $(BIN) /usr/bin/

uninstall:
	sudo rm /usr/bin/$(BIN)

preprocess:
	$(CC) $(CFLAGS) -E -o preproc.i main.c
