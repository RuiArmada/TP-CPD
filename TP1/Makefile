CC = gcc
BIN = bin/
SRC = src/
PRF = prof/
INCLUDES = include/

EXEC = tp1
CFLAGS = -Wall -Wextra -Werror -lm
# Performance flags
CFLAGS += -O3

# Profiling flags and definitions
PROFILING_EXEC = tp1_profiling
PROFILING_CFLAGS = -g -O0 -pg -lm 

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

profiling: $(SRC)main.c $(PRF)kmeans_p.o $(PRF)logging_p.o $(PRF)utils_p.o 
	$(CC) $(PROFILING_CFLAGS) $(SRC)main.c $(PRF)*_p.o -o $(PRF)$(PROFILING_EXEC)

$(PRF)logging_p.o: $(SRC)logging.c $(INCLUDES)logging.h
	$(CC) $(PROFILING_CFLAGS) -c $(SRC)logging.c -o $(PRF)logging_p.o

$(PRF)utils_p.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(PROFILING_CFLAGS) -c $(SRC)utils.c -o $(PRF)utils_p.o

$(PRF)kmeans_p.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h
	$(CC) $(PROFILING_CFLAGS) -c $(SRC)kmeans.c -o $(PRF)kmeans_p.o

valgrind: main
	valgrind $(VALGRIND_FLAGS) $(BIN)$(EXEC)

mklogdir:
	@mkdir -p logs &2> /dev/null

clean_objs:
	@rm -f $(BIN)*.o
	@rm -f $(PRF)*.o

clean_exec:
	@rm -f $(BIN)$(EXEC)
	@rm -f $(PRF)$(PROFILING_EXEC)

clean: clean_objs clean_exec
	@echo "Done cleaning"

run: main mklogdir 
	./$(BIN)$(EXEC)
	@mv *.log logs &2> /dev/null

run_prof: profiling
	./$(PRF)$(PROFILING_EXEC)
	@gprof $(PRF)$(PROFILING_EXEC) gmon.out > analysis.txt
	@mv *.log logs &2> /dev/null

# run_batch: clean main back_logs
