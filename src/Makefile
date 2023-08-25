CC:=gcc
COBC:=cobc
BIN:=../bin/

all:
	cobble
	
cobble: readsocket.o
	$(CC) readsocket.o -o $(BIN)COBBLE
	
build: readsocket.c
	$(CC) readsocket.c