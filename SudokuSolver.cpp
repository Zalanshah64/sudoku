#include "SudokuSolver.h"
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::flush;
#include <string>
using std::string;
using std::stoi;
using std::to_string;
#include <limits>
using std::numeric_limits;


SudokuSolver::SudokuSolver(SudokuBoard &sudokuBoard) : board{sudokuBoard} {}

bool SudokuSolver::tryCoord(size_t row, size_t col) {
    if(board.getNumSolved() == boardSize * boardSize) {
        return true;
    }

    if(row > 9) {
        return false;
    }

    if(!board(row, col).occupied()) {
        for(size_t i = 1; i < boardSize + 1; i++) {
            if(promising(row, col, i)) {
                board.tryNum(row, col, i);

                if(col < boardSize) {
                    if(tryCoord(row, col + 1)) {
                        return true;
                    }
                } else {
                    if(tryCoord(row + 1, 1)) {
                        return true;
                    }
                }

                board.empty(row, col);
            }
        }
    } else {
        if(col < boardSize) {
            if(tryCoord(row, col + 1)) {
                return true;
            }
        } else {
            if(tryCoord(row + 1, 1)) {
                return true;
            }
        }
    }
    return false;
}

bool SudokuSolver::promising(size_t row, size_t col, size_t value) {
    return board.verify(row, col, value);
}

bool SudokuSolver::solveBoard() {
    return tryCoord(1, 1);
}

void SudokuSolver::printBoard() {
    board.print();
}