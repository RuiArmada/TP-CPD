CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/

EXEC = tp1
CFLAGS = -Wall -Wextra -Werror -lm
#CFLAGS += -Og -g
CFLAGS += -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --leak-resolution=high

.DEFAULT_GOAL := main

main: $(SRC)main.c $(BIN)kmeans.o $(BIN)utils.o $(BIN)logging.o
	$(CC) $(CFLAGS) $(SRC)main.c $(BIN)*.o -o $(BIN)$(EXEC)

$(BIN)logging.o: $(SRC)logging.c $(INCLUDES)logging.h
	$(CC) $(CFLAGS) -c $(SRC)logging.c -o $(BIN)logging.o

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

$(BIN)kmeans.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h
	$(CC) $(CFLAGS) -c $(SRC)kmeans.c -o $(BIN)kmeans.o

valgrind: clean main
	valgrind $(VALGRIND_FLAGS) $(BIN)$(EXEC)

mklogdir:
	@mkdir -p logs &2> /dev/null

clean_objs:
	@rm -f $(BIN)*.o

clean_exec:
	@rm -f $(BIN)$(EXEC) 

clean: clean_objs clean_exec
	@echo "Done cleaning"

run: main mklogdir 
	./$(BIN)$(EXEC)
	@mv *.log logs &2> /dev/null

# run_batch: clean main back_logs
