#pragma once

#include "BoardSquare.h"
#include "SudokuBoard.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <iterator>
using std::size_t;


class SudokuSolver {
    private:

    static const size_t boardSize = 9;
    SudokuBoard& board;

    bool tryCoord(size_t row, size_t col);
    bool promising(size_t row, size_t col, size_t value);
    size_t getGrid(size_t row, size_t col);


    public:
    SudokuSolver(SudokuBoard &board);
    bool solveBoard();

};