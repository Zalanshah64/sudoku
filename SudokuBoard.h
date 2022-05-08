#pragma once
#include "BoardSquare.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

class SudokuBoard {
    private:
    static const size_t boardSize = 9;

    struct GridNumbers {
        size_t numbers[boardSize + 1][boardSize + 1];
    };


    BoardSquare board[boardSize + 1][boardSize + 1];
    size_t numSolved = 0;

    bool horizontal[boardSize + 1][boardSize + 1];
    bool vertical[boardSize + 1][boardSize + 1];
    bool grids[boardSize + 1][boardSize + 1];
    static GridNumbers gridNumbers;

    inline size_t getGrid(size_t row, size_t col) {
        return gridNumbers.numbers[row][col];
    }

    void clearBoard();

    public:

    enum class Difficulty : uint8_t {EASY, MEDIUM, HARD, IMPOSSIBLE};

    SudokuBoard() {}
    SudokuBoard(ifstream &input);

    void generate(Difficulty difficulty);

    void tryNum(size_t row, size_t col, size_t val);
    void empty(size_t row, size_t col);

    void print();
    void print(ofstream &of);

    inline BoardSquare& operator()(size_t row, size_t col) {
        return board[row][col];
    }

    inline size_t getNumSolved() {
        return numSolved;
    }

    inline bool verify(size_t row, size_t col, size_t value) {
    return !(horizontal[row][value] || vertical[col][value] || grids[getGrid(row, col)][value]);
    }
};