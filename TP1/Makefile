CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/

EXEC = tp1
CFLAGS = -Wall -Wextra -Werror -lm
#CFLAGS += -Og -g
CFLAGS += -O3
#CFLAGS += -funroll-loops

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --leak-resolution=high

.DEFAULT_GOAL := main

main: $(SRC)main.c $(BIN)kmeans.o $(BIN)utils.o
	$(CC) $(CFLAGS) $(SRC)main.c $(BIN)*.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

$(BIN)kmeans.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h
	$(CC) $(CFLAGS) -c $(SRC)kmeans.c -o $(BIN)kmeans.o

valgrind: clean main
	valgrind $(VALGRIND_FLAGS) $(BIN)$(EXEC)

back_logs:
	@mkdir -p logs
	@mv *.log logs

clean_objs:
	@rm -f $(BIN)*.o

clean_exec:
	@rm -f $(BIN)$(EXEC) 

clean: clean_objs clean_exec
	@echo "Done cleaning"

run: clean main
	./$(BIN)$(EXEC)

# run_batch: clean main back_logs
