#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;

SudokuBoard::GridNumbers SudokuBoard::gridNumbers =  {{
    {10, 10, 10, 10, 10, 10, 10, 10, 10},
    {10, 0, 0, 0, 1, 1, 1, 2, 2, 2},
    {10, 0, 0, 0, 1, 1, 1, 2, 2, 2},
    {10, 0, 0, 0, 1, 1, 1, 2, 2, 2},
    {10, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {10, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {10, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {10, 6, 6, 6, 7, 7, 7, 8, 8, 8},
    {10, 6, 6, 6, 7, 7, 7, 8, 8, 8},
    {10, 6, 6, 6, 7, 7, 7, 8, 8, 8}
}};

SudokuBoard::SudokuBoard(ifstream &input) {
    for(size_t i = 0; i < boardSize + 1; i++) {
        for(size_t j = 0; j < boardSize + 1; j++) {
            horizontal[i][j] = false;
            vertical[i][j] = false;
            grids[i][j] = false;
        }
    }

    char value;
    for(size_t i = 1; i < boardSize + 1; i++) {
        for(size_t j = 1; j < boardSize + 1; j++) {
            input >> value;

            if((value > '9' || value < '1') && value != '-') {
                cerr << "Error: Invalid character for board: " << value << endl;
                exit(1);
            } else if(value == '-') {
                board[i][j].empty();
            } else {
                board[i][j] = value - '0';
                vertical[j][board[i][j].getValue()] = true;
                horizontal[i][board[i][j].getValue()] = true;
                grids[getGrid(i, j)][board[i][j].getValue()] = true;
                numSolved++;
            }
        }
    }
}

void SudokuBoard::clearBoard() {
    for(size_t i = 0; i < boardSize; i++) {
        for(size_t j = 0; j < boardSize; j++) {
            board[i][j].empty();
        }
    }
}

void SudokuBoard::generate() {
    clearBoard();
    srand((unsigned int)time(NULL));
    size_t row, col, value;

    for(size_t i = 0; i < 30; i++) {
        row = rand() % boardSize + 1;
        col = rand() % boardSize + 1;

        if(!board[row][col].occupied()) {
            value = rand() % boardSize + 1;

            if(verify(row, col, value)) {
                board[row][col] = value;
                horizontal[row][value] = true;
                vertical[col][value] = true;
                grids[getGrid(row, col)][value] = true;
            } else {
                i--;
            }
        } else {
            i--;
        }
    }

    print();

    SudokuSolver solver(*this);

    print();
    if(!solver.solveBoard()) {
        return generate();
    }
}


void SudokuBoard::tryNum(size_t row, size_t col, size_t val) {
    board[row][col].tryNum(val);
    horizontal[row][val] = true;
    vertical[col][val] = true;
    grids[getGrid(row, col)][val] = true;
    numSolved++;
}

void SudokuBoard::empty(size_t row, size_t col) {
    horizontal[row][board[row][col].getValue()] = false;
    vertical[col][board[row][col].getValue()] = false;
    grids[getGrid(row, col)][board[row][col].getValue()] = false;

    board[row][col].empty();
    numSolved--;
}

void SudokuBoard::print() {
    for(size_t i = 1; i < boardSize + 1; i++) {
        if((i - 1) % 3 == 0) {
            if(i != 1) {
                cout << "\n#           #           #           #";
            }
            cout << "\n#####################################\n#           #           #           #\n#  ";
        } else {
            cout << "\n#           #           #           #\n#  ";
        }
            for(size_t j = 1; j < boardSize + 1; j++) {
                cout << board[i][j]
                << (((j) % 3 == 0) ? "  #  " : "  ");
            }

    }
    cout << "\n#           #           #           #\n#####################################\n";
}

void SudokuBoard::print(ofstream &of) {
    for(size_t i = 0; i < boardSize; i++) {
        for(size_t j = 0; j < boardSize; j++) {
            of << board[i][j];
        }
        of << "\n";
    }
}