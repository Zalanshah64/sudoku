#include "utilityFunctions.h"
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
#include <string>
using std::string;
#include <iterator>
using std::size_t;


SudokuBoard::GridNumbers SudokuBoard::gridNumbers =  {{
    {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    {10, 0,  0,  0,  1,  1,  1,  2,  2,  2},
    {10, 0,  0,  0,  1,  1,  1,  2,  2,  2},
    {10, 0,  0,  0,  1,  1,  1,  2,  2,  2},
    {10, 3,  3,  3,  4,  4,  4,  5,  5,  5},
    {10, 3,  3,  3,  4,  4,  4,  5,  5,  5},
    {10, 3,  3,  3,  4,  4,  4,  5,  5,  5},
    {10, 6,  6,  6,  7,  7,  7,  8,  8,  8},
    {10, 6,  6,  6,  7,  7,  7,  8,  8,  8},
    {10, 6,  6,  6,  7,  7,  7,  8,  8,  8}
}};

SudokuBoard::SudokuBoard() {
    for(size_t i = 0; i < boardSize + 1; i++) {
        for(size_t j = 0; j < boardSize + 1; j++) {
            horizontal[i][j] = 0;
            vertical[i][j] = 0;
            grids[i][j] = 0;
        }
    }
}

SudokuBoard::SudokuBoard(ifstream &input) {
    for(size_t i = 0; i < boardSize + 1; i++) {
        for(size_t j = 0; j < boardSize + 1; j++) {
            horizontal[i][j] = 0;
            vertical[i][j] = 0;
            grids[i][j] = 0;
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
                vertical[j][board[i][j].getValue()]++;
                horizontal[i][board[i][j].getValue()]++;
                grids[getGrid(i, j)][board[i][j].getValue()]++;
                numSolved++;
            }
        }
    }
}

void SudokuBoard::clearBoard() {
    for(size_t i = 0; i < boardSize; i++) {
        for(size_t j = 0; j < boardSize; j++) {
            board[i][j].empty();
            horizontal[i + 1][j + 1] = 0;
            vertical[i + 1][j + 1] = 0;
            grids[i + 1][j + 1] = 0;
        }
    }

    numSolved = 0;
}

void SudokuBoard::generate(Difficulty difficulty) {
    clearBoard();

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
            horizontal[row][*it]++;
            vertical[col][*it]++;
            grids[i][*it]++;
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
            numToRemove = 35;
        break;
        case Difficulty::MEDIUM:
            numToRemove = 45;
        break;

        case Difficulty::HARD:
            numToRemove = 50;
        break;

        case Difficulty::IMPOSSIBLE:
            numToRemove = 60;
        break;

    }

    for(size_t i = 0; i < numToRemove; i++) {
        size_t row = 1 + (rand() % 9);
        size_t col = 1 + (rand() % 9);

        if(board[row][col].occupied()) {
            empty(row, col);
        } else {
            i--;
        }
    }

    for(size_t i = 1; i < boardSize + 1; i++) {
        for(size_t j = 1; j < boardSize + 1; j++) {
            if(board[i][j].occupied()) {
                board[i][j].establish(board[i][j].getValue());
            }
        }
    }
}


void SudokuBoard::tryNum(size_t row, size_t col, size_t val) {
    board[row][col].tryNum(val);
    horizontal[row][val]++;
    vertical[col][val]++;
    grids[getGrid(row, col)][val]++;
    numSolved++;
}

void SudokuBoard::tryIncorrect(size_t row, size_t col, size_t val) {
    board[row][col].tryIncorrect(val);

    if(horizontal[row][val]) {
        for(size_t i = 1; i < boardSize + 1; i++) {
            if(board[row][i] == val && i != col) {
                board[row][i].breakSquare();
                numSolved--;
            }
        }
    }

    if(vertical[col][val]) {
        for(size_t i = 1; i < boardSize + 1; i++) {
            if(board[i][col] == val && i != row) {
                board[i][col].breakSquare();
                numSolved--;
            }
        }
    }

    if(grids[getGrid(row, col)][val]) {
        size_t minRow = getMinCoord(row);
        size_t minCol = getMinCoord(col);

        for(size_t i = minRow; i < minRow + 3; i++) {
            for(size_t j = minCol; j < minCol + 3; j++) {
                if(board[i][j] == val && (i != row || j != col)) {
                    board[i][j].breakSquare();
                    numSolved--;
                }
            }
        }
    }

    horizontal[row][val]++;
    vertical[col][val]++;
    grids[getGrid(row, col)][val]++;
}

void SudokuBoard::empty(size_t row, size_t col) {
    if(!board[row][col].occupied()) {
        return;
    }


    if(board[row][col].incorrect()) {
        size_t value = board[row][col].getValue();

        //Fix horizontal
        for(size_t i = 1; i < boardSize + 1; i++) {
            if(board[row][i] == value && i != col) {
                board[row][i].fix();
                numSolved++;
            }
        }

        //Fix vertical
        for(size_t i = 1; i < boardSize + 1; i++) {
            if(board[i][col] == value && i != row) {
                board[i][col].fix();
                numSolved++;
            }
        }


        //Fix grid
        size_t minRow = 0, minCol = 0;

        switch(row) {
            case 1: case 2: case 3:
            minRow = 1;
            break;
            case 4: case 5: case 6:
            minRow = 4;
            break;
            case 7: case 8: case 9:
            minRow = 7;
            break;
        }

        switch(col) {
            case 1: case 2: case 3:
            minCol = 1;
            break;
            case 4: case 5: case 6:
            minCol = 4;
            break;
            case 7: case 8: case 9:
            minCol = 7;
            break;
        }

        for(size_t i = minRow; i < minRow + 3; i++) {
            for(size_t j = minCol; j < minCol + 3; j++) {
                if(board[i][j] == value && (i != row || j != col)) {
                    board[i][j].fix();
                    numSolved++;
                }
            }
        }

        horizontal[row][board[row][col].getValue()]--;
        vertical[col][board[row][col].getValue()]--;
        grids[getGrid(row, col)][board[row][col].getValue()]--;

        board[row][col].empty();
    } else {
        horizontal[row][board[row][col].getValue()]--;
        vertical[col][board[row][col].getValue()]--;
        grids[getGrid(row, col)][board[row][col].getValue()]--;

        board[row][col].empty();
        numSolved--;
    }

}

void SudokuBoard::print() {
    for(size_t i = 1; i < boardSize + 1; i++) {
        if((i - 1) % 3 == 0) {
            if(i != 1) {
                cout << "\n#           #           #           #";
            }
            cout << "\n#####################################"
                 << "\n#           #           #           #\n#  ";
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

void SudokuBoard::print(size_t row, size_t col) {
    size_t gridNum = getGrid(row, col);
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

                string color;
                if(i == row && j == col) {

                    if(board[i][j].incorrect()) {
                        color = "\033[47;31m";
                    } else if(board[i][j].occupied()) {
                        color = "\033[47;30m";
                    } else {
                        color = "\033[47m";
                    }
                    cout << color << board[i][j].getValue() << DEFAULT
                    << (((j) % 3 == 0) ? "  #  " : "  ");
                } else {
                    if(row == i || col == j || getGrid(i, j) == gridNum) {
                        color = "\033[48;5;236m";
                    }

                    if(board[row][col] == board[i][j].getValue() && board[i][j].getValue()) {
                        color = "\033[48;2;125;75;10m";
                    }

                    cout << color <<  board[i][j]
                    << (((j) % 3 == 0) ? "  #  " : "  ");
                    color = "";
                }
            }

    }

    if(!solved()) {
        cout << "\n#           #           #           #"
            << "\n#####################################"
            << "\n            O P T I O N S            "
            << "\nArrow Keys   Move around board"
            << "\nEnter        Focus on selected square"
            << (!board[row][col].pregenerated() && board[row][col].occupied() ? "\nBackspace    Delete selected square" : "\n")
            << "\nS, s         View seed"
            << "\nQ, q         Quit game";
    }

    cout << endl;
}

void SudokuBoard::getSubgrid(const size_t row, const size_t col, BoardSquare *(&grid)[9]) {

    size_t minRow = getMinCoord(row);
    size_t minCol = getMinCoord(col);

    size_t counter = 0;
    for(size_t i = minRow; i < minRow + 3; i++) {
        for(size_t j = minCol; j < minCol + 3; j++) {
            grid[counter++] = &(board[i][j]);
        }
    }
}

void SudokuBoard::print(ofstream &of) {
    for(size_t i = 1; i < boardSize + 1; i++) {
        for(size_t j = 1; j < boardSize + 1; j++) {
            board[i][j].print(of);
        }
        of << "\n";
    }
}