edit:
	g++ -O3 -o sudoku utilityFunctions.cpp BoardSquare.cpp SudokuBoard.cpp SudokuSolver.cpp main.cpp

debug:
	g++ -g3 -o sudoku_debug utilityFunctions.cpp BoardSquare.cpp SudokuBoard.cpp SudokuSolver.cpp main.cpp