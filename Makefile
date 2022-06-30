CC = g++
CFLAGS = -Wall -std=c++17 -pedantic -Wextra -Wshadow -Wconversion

edit:
	$(CC) $(CFLAGS) -O3 -o sudoku utilityFunctions.cpp BoardSquare.cpp SudokuBoard.cpp SudokuSolver.cpp main.cpp

debug:
	$(CC) $(CFLAGS) -g3 -o sudoku_debug utilityFunctions.cpp BoardSquare.cpp SudokuBoard.cpp SudokuSolver.cpp main.cpp