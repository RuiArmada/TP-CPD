CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/

EXEC = tp1
CFLAGS = -Wall -Wextra -lm
# CFLAGS += -Werror

.DEFAULT_GOAL := main

main: $(SRC)main.c $(BIN)kmeans.o $(BIN)utils.o
	$(CC) $(CFLAGS) $(SRC)main.c $(BIN)*.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

$(BIN)kmeans.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h
	$(CC) $(CFLAGS) -c $(SRC)kmeans.c -o $(BIN)kmeans.o

clean:
	rm $(BIN)*.o $(BIN)$(EXEC) &2> /dev/null
	clear

run:
	./$(BIN)$(EXEC)
