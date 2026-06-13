# Set compiler variables
CC = gcc
CXX = g++  # Use g++ for C++ files

# Compiler flags 
# DO NOT REMOVE -ftest-coverage -fprofile-arcs from the compile flags
BASE_CFLAGS = -Wall -Werror -g -ftest-coverage -fprofile-arcs
# DO NOT REMOVE or change either variable below
CFLAGS += $(BASE_CFLAGS)
CXXFLAGS = $(CFLAGS)  # Use the same flags for C++ files

########################################################################################
# Object files variable that contains a list of the object files that will be built
OBJS = main.o data.o operations.o# CODE: add the .o files that need to be created (HINT: find a list of the necessary .o files by executing gcc -MM *.c)
########################################################################################

# Default target all runs the compilation for main and test
all: main.bin

# DO NOT REMOVE CFLAGS from the compile line below
# Main program target
main.bin: $(OBJS)
	$(CC) $(CFLAGS) -o main.bin $(OBJS) 

# DO NOT REMOVE CFLAGS from the compile line below
# Generic rule for building C object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Specific rule for building operations.o with g++

# DO NOT REMOVE CXXFLAGS from the compile line below
# Generic rule for building C++ object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
##########################################################
# CODE HERE: insert all dependencies from .o to .h filess
# You can generate the dependencies using the command:
# 		gcc -MM *.c
# and paste them below
##########################################################
main.o: main.c data.h operations.h
	$(CC) $(CFLAGS) -c main.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

operations.o: operations.c operations.h data.h
	$(CC) $(CFLAGS) -c operations.c
# Clean target
clean:
	find . -type f \( -name '*.o' -o -name '*.gcno' -o -name '*.gcda' -o -name '*.gcov' \) ! -name 'gym.o' -delete

# .PHONY will cause the Makefile to consider the targets "all" and "clean" as always out-of-date
.PHONY: all clean
