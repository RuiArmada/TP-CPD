CC = gcc
BIN = bin/
SRC = src/
PRF = prof/
BNC = benchmarks/
INCLUDES = include/
EXEC = tp1

########################################## CFLAGS #################################################
# General purpose flags
CFLAGS = -Wall -Wextra -Werror -lm -fopt-info

#-PERFORMANCE-#
# Performance flags
CFLAGS += -O2 -ffast-math -flto
# unfortunatly, -mfma is not supported by the cluster, speeds things up more than 2x
# CFLAGS += -mfma -msse3 -mfpmath=sse 
CFLAGS += -ftree-loop-if-convert

#-PROFILING-#

# Profiling flags and definitions
PROFILING_EXEC = tp1_profiling
PROFILING_CFLAGS = -g -O0 -pg -lm 

#-VALGRIND-#

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --leak-resolution=high

#- BEST CASE -#

.DEFAULT_GOAL := main

DEFAULT_VALS = -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1

main: $(SRC)main.c $(BIN)kmeans.o $(BIN)utils.o $(INCLUDES)bconsts.h
	$(CC) $(CFLAGS) $(SRC)main.c $(BIN)*.o -o $(BIN)$(EXEC) $(DEFAULT_VALS)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h $(INCLUDES)bconsts.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o $(DEFAULT_VALS)

$(BIN)kmeans.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h $(INCLUDES)bconsts.h
	$(CC) $(CFLAGS) -c $(SRC)kmeans.c -o $(BIN)kmeans.o $(DEFAULT_VALS)

#- BENCHMARKS -#

# Benchmarks take three arguments:
# 1. The CFLASGS to compile with, BNC_CFLAGS
# 2. The suffix to append to the executable and .o files, BNC_SUFFIX
# 3. The name of the executable, BNC_EXEC
# Check include/bconsts.h for the accepted values for the functions

benchmark: $(SRC)main.c $(BIN)bnckmeans$(BNC_SUFFIX).o $(BIN)bncutils$(BNC_SUFFIX).o $(INCLUDES)bconsts.h
	$(CC) $(BNC_CFLAGS) $(SRC)main.c $(BNC)*$(BNC_SUFFIX).o -o $(BNC)/bin/$(BNC_EXEC)$(BNC_SUFFIX)
	rm $(BNC)*.o

$(BIN)bncutils$(BNC_SUFFIX).o: $(SRC)utils.c $(INCLUDES)utils.h $(INCLUDES)bconsts.h
	$(CC) $(BNC_CFLAGS) -c $(SRC)utils.c -o $(BNC)utils$(BNC_SUFFIX).o

$(BIN)bnckmeans$(BNC_SUFFIX).o: $(SRC)kmeans.c $(INCLUDES)kmeans.h $(INCLUDES)bconsts.h
	$(CC) $(BNC_CFLAGS) -c $(SRC)kmeans.c -o $(BNC)kmeans$(BNC_SUFFIX).o

#- PROFILING -#

profiling: $(SRC)main.c $(PRF)kmeans_p.o $(PRF)utils_p.o 
	$(CC) $(PROFILING_CFLAGS) $(SRC)main.c $(PRF)*_p.o -o $(PRF)$(PROFILING_EXEC) $(DEFAULT_VALS)

$(PRF)utils_p.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(PROFILING_CFLAGS) -c $(SRC)utils.c -o $(PRF)utils_p.o $(DEFAULT_VALS)

$(PRF)kmeans_p.o: $(SRC)kmeans.c $(INCLUDES)kmeans.h
	$(CC) $(PROFILING_CFLAGS) -c $(SRC)kmeans.c -o $(PRF)kmeans_p.o $(DEFAULT_VALS)

valgrind: main
	valgrind $(VALGRIND_FLAGS) $(BIN)$(EXEC)

#- Other -#

clean_objs:
	@rm -f $(BIN)*.o
	@rm -f $(PRF)*.o

clean_exec:
	@rm -f $(BIN)$(EXEC)
	@rm -f $(PRF)$(PROFILING_EXEC)

clean_benchmarks:
	@rm -f $(BNC)bin/*
	@rm -f $(BNC)*.o

clean: clean_objs clean_exec clean_benchmarks
	@echo "Done cleaning"

run: main
	./$(BIN)$(EXEC)

run_prof: profiling
	./$(PRF)$(PROFILING_EXEC)
	@gprof $(PRF)$(PROFILING_EXEC) gmon.out > analysis.txt

run_batch: main
	@srun --partition=cpar perf stat -r 15 -e instructions,cycles ./bin/tp1
	
