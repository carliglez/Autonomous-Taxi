# Variables
CC = g++
CFLAGS = -std=c++17

# Directories
BIN = bin
SRC = src
INCLUDE = include

# Source files
SRC_FILES = $(wildcard $(SRC)/*.cc)

# Header files required for compilation
HEADERS = $(INCLUDE)/simulation.h $(INCLUDE)/vector.h $(INCLUDE)/taxi4.h $(INCLUDE)/taxi8.h $(INCLUDE)/world.h $(INCLUDE)/vehicle.h

# Default target: compile executable in bin directory
all: $(BIN)/main

# Create the executable in the bin folder (create bin directory if it does not exist)
$(BIN)/main: $(SRC_FILES) $(HEADERS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/main $(SRC_FILES) -I$(INCLUDE)

# Clean the binary files and the executable in bin
clean:
	rm -f $(BIN)/main