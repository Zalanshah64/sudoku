#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
#include <list>
using std::list;
#include <iterator>
using std::advance;
#include <algorithm>
using std::pair;


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

    numSolved = 0;
}

void SudokuBoard::generate(Difficulty difficulty) {
    clearBoard();
    srand((unsigned int)time(NULL));
    for(size_t i = 1; i < boardSize + 1; i++) {
        for(size_t j = 1; j < boardSize + 1; j++) {
            horizontal[i][j] = false;
            vertical[i][j] = false;
            grids[i][j] = false;
        }
    }
    size_t row, col, value;

    for(size_t i = 0; i < 9; i += 4) {
        list<size_t> valuesRemaining = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        list< pair<size_t, size_t> > coordsRemaining;

        switch(i) {
            case 0:
                coordsRemaining = {
                    {1, 1}, {1, 2}, {1, 3},
                    {2, 1}, {2, 2}, {2, 3},
                    {3, 1}, {3, 2}, {3, 3}
                };
            break;
            case 4:
                coordsRemaining = {
                    {4, 4}, {4, 5}, {4, 6},
                    {5, 4}, {5, 5}, {5, 6},
                    {6, 4}, {6, 5}, {6, 6}
                };
            break;
            case 8:
                coordsRemaining = {
                    {7, 7}, {7, 8}, {7, 9},
                    {8, 7}, {8, 8}, {8, 9},
                    {9, 7}, {9, 8}, {9, 9}
                };
            break;
        }

        while(valuesRemaining.size() > 0) {
            auto coordIt = coordsRemaining.begin();
            advance(coordIt, (rand() % coordsRemaining.size()));
            size_t row = coordIt->first;
            size_t col = coordIt->second;

            auto it = valuesRemaining.begin();
            advance(it, (rand() % valuesRemaining.size()));

            board[row][col] = *it;
            horizontal[row][*it] = true;
            vertical[col][*it] = true;
            grids[i][*it] = true;
            numSolved++;

            valuesRemaining.erase(it);
            coordsRemaining.erase(coordIt);
        }
    }

    SudokuSolver solver(*this);

    if(!solver.solveBoard()) {
        return generate(difficulty);
    }

    size_t numToRemove = 0;
    switch(difficulty) {
        case Difficulty::EASY:
            numToRemove = 40;
        break;
        case Difficulty::MEDIUM:
            numToRemove = 50;
        break;

        case Difficulty::HARD:
            numToRemove = 60;
        break;

        case Difficulty::IMPOSSIBLE:
            numToRemove = 70;
        break;

    }

    for(size_t i = 0; i < numToRemove; i++) {
        size_t row = 1 + (rand() % 9);
        size_t col = 1 + (rand() % 9);

        if(board[row][col].occupied()) {
            board[row][col].empty();
        } else {
            i--;
        }
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
            cout << "\n#####################################\n"
                 << "#           #           #           #\n#  ";
        } else {
            cout << "\n#           #           #           #\n#  ";
        }
            for(size_t j = 1; j < boardSize + 1; j++) {
                cout << board[i][j]
                << (((j) % 3 == 0) ? "  #  " : "  ");
            }

    }
    cout << "\n#           #           #           #\n"
         <<   "#####################################\n";
}

void SudokuBoard::print(ofstream &of) {
    for(size_t i = 1; i < boardSize + 1; i++) {
        for(size_t j = 1; j < boardSize + 1; j++) {
            board[i][j].print(of);
        }
        of << "\n";
    }
}