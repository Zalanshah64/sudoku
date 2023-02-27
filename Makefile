CXX = g++
CFLAGS = -Wall -std=c++17 -pedantic -Wextra -Wshadow -Wconversion -I inc
BIN = sudoku
BIN_DEBUG = sudoku_debug
SRCS = $(wildcard src/*.cpp)
HEADS = $(wildcard src/*.h)
OBJ := $(SRCS:src/%.cpp=obj/%.o)
OBJ_DEBUG := $(SRCS:src/%.cpp=obj/%_debug.o)
OBJDIR = obj
# UTIL = $(src/utilityFunctions.h)

.PHONY: all
all: $(BIN)

.PHONY: debug
debug: $(BIN_DEBUG)

.PHONY: clean
clean:
	rm -rf $(BIN) $(BIN_DEBUG) $(OBJDIR) $(OBJ_DEBUG)

$(OBJ): obj/%.o : src/%.cpp inc/%.h
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -O3 -c $< -o $@

$(OBJ_DEBUG): obj/%_debug.o : src/%.cpp inc/%.h
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -g3 -c $< -o $@

$(BIN): $(OBJ)
	$(CXX) $(CFLAGS) -O3 $^ -o $@

$(BIN_DEBUG): $(OBJ_DEBUG)
	$(CXX) $(CFLAGS) -g3 $^ -o $@
