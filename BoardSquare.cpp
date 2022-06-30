#include "BoardSquare.h"
#include "SudokuBoard.h"
#include "utilityFunctions.h"
#include <cstdint>
using std::size_t;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

BoardSquare::BoardSquare() {
    value = 0;
    status = SquareStatus::empty;
}

BoardSquare::BoardSquare(const size_t val) {
    value = val;
    status = SquareStatus::preloaded;
}

void BoardSquare::addNotation(const size_t notation) {
    if(!notations[notation] && status != SquareStatus::preloaded && status != SquareStatus::incorrectPreloaded)  {
        notations[notation] = true;
    }
}

void BoardSquare::removeNotation(const size_t notation) {
    notations[notation] = false;
}


void BoardSquare::tryNum(const size_t val) {
    value = val;
    status = SquareStatus::testing;
}

void BoardSquare::establish(const size_t val) {
    value = val;
    status = SquareStatus::preloaded;
}

void BoardSquare::tryIncorrect(const size_t val) {
    value = val;
    status = SquareStatus::incorrect;
}

void BoardSquare::breakSquare() {

    switch(status) {
        case SquareStatus::preloaded:
        status = SquareStatus::incorrectPreloaded;
        break;
        case SquareStatus::testing:
        status = SquareStatus::incorrect;
        break;
        default: break;
    }
}

void BoardSquare::fix() {
    switch(status) {
        case SquareStatus::incorrect:
        status = SquareStatus::testing;
        break;
        case SquareStatus::incorrectPreloaded:
        status = SquareStatus::preloaded;
        break;
        default: break;
    }
}

size_t BoardSquare::focus(size_t row, size_t col,
            BoardSquare *(&horizontal)[9],
            BoardSquare *(&vertical)[9],
            BoardSquare *(&grid)[9],
            const bool (&horizontalOccupied)[9],
            const bool (&verticalOccupied)[9],
            const bool (&gridOccupied)[9]
            ) {
    clear();
    string color;
    switch(status) {
        case SquareStatus::preloaded:
        color = BLUEBOLDTEXT;
        break;
        case SquareStatus::testing:
        color = GREENTEXT;
        break;
        case SquareStatus::incorrectPreloaded: case SquareStatus::incorrect:
        color = REDTEXT;
        break;
        case SquareStatus::empty: break;
    }

    //Depending on the number, print the correct square
    switch(value) {
        case 0:
        cout << " .----------------. "
           << "\n| .--------------. |"
           << "\n| |              | |"
           << "\n| |              | |"
           << "\n| |    ______    | |"
           << "\n| |   |______|   | |"
           << "\n| |              | |"
           << "\n| |              | |"
           << "\n| |    (" << row << ", " << col << ")    | |"
           << "\n| '--------------' |"
           << "\n '----------------' \n";
           break;
        case 1:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |   " << color << "  __   " << DEFAULT << "    | |"
             << "\n| |   " << color << " /  |  " << DEFAULT << "    | |"
             << "\n| |   " << color << " `| |  " << DEFAULT << "    | |"
             << "\n| |   " << color << "  | |  " << DEFAULT << "    | |"
             << "\n| |   " << color << " _| |_ " << DEFAULT << "    | |"
             << "\n| |   " << color << "|_____|" << DEFAULT << "    | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 2:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << "  _____   " << DEFAULT << "  | |"
             << "\n| |  " << color << " / ___ `. " << DEFAULT << "  | |"
             << "\n| |  " << color << "|_/___) | " << DEFAULT << "  | |"
             << "\n| |  " << color << " .'____.' " << DEFAULT << "  | |"
             << "\n| |  " << color << "/ /____   " << DEFAULT << "  | |"
             << "\n| |  " << color << "|_______| " << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 3:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << "  ______   " << DEFAULT << " | |"
             << "\n| |  " << color << " / ____ `. " << DEFAULT << " | |"
             << "\n| |  " << color << " `'  __) | " << DEFAULT << " | |"
             << "\n| |  " << color << " _  |__ '. " << DEFAULT << " | |"
             << "\n| |  " << color << "| \\____) | " << DEFAULT << " | |"
             << "\n| |  " << color << " \\______.' " << DEFAULT << " | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 4:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << " _    _   " << DEFAULT << "  | |"
             << "\n| |  " << color << "| |  | |  " << DEFAULT << "  | |"
             << "\n| |  " << color << "| |__| |_ " << DEFAULT << "  | |"
             << "\n| |  " << color << "|____   _|" << DEFAULT << "  | |"
             << "\n| |  " << color << "    _| |_ " << DEFAULT << "  | |"
             << "\n| |  " << color << "   |_____|" << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
             break;
        case 5:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << " _______  " << DEFAULT << "  | |"
             << "\n| |  " << color << "|  _____| " << DEFAULT << "  | |"
             << "\n| |  " << color << "| |____   " << DEFAULT << "  | |"
             << "\n| |  " << color << "'_.____''." << DEFAULT << "  | |"
             << "\n| |  " << color << "| \\____) |" << DEFAULT << "  | |"
             << "\n| |  " << color << " \\______.'" << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 6:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << "  ______  " << DEFAULT << "  | |"
             << "\n| |  " << color << ".' ____ \\ " << DEFAULT << "  | |"
             << "\n| |  " << color << "| |____\\_|" << DEFAULT << "  | |"
             << "\n| |  " << color << "| '____`'." << DEFAULT << "  | |"
             << "\n| |  " << color << "| (____) |" << DEFAULT << "  | |"
             << "\n| |  " << color << "'.______.'" << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 7:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << " _______ " << DEFAULT << "   | |"
             << "\n| |  " << color << "|  ___  |" << DEFAULT << "   | |"
             << "\n| |  " << color << "|_/  / / " << DEFAULT << "   | |"
             << "\n| |  " << color << "    / /  " << DEFAULT << "   | |"
             << "\n| |  " << color << "   / /   " << DEFAULT << "   | |"
             << "\n| |  " << color << "  /_/    " << DEFAULT << "   | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 8:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << "   ____   " << DEFAULT << "  | |"
             << "\n| |  " << color << " .' __ '. " << DEFAULT << "  | |"
             << "\n| |  " << color << " | (__) | " << DEFAULT << "  | |"
             << "\n| |  " << color << " .`____'. " << DEFAULT << "  | |"
             << "\n| |  " << color << "| (____) |" << DEFAULT << "  | |"
             << "\n| |  " << color << "`.______.'" << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
        case 9:
        cout << " .----------------. "
             << "\n| .--------------. |"
             << "\n| |  " << color << "  ______  " << DEFAULT << "  | |"
             << "\n| |  " << color << ".' ____ '." << DEFAULT << "  | |"
             << "\n| |  " << color << "| (____) |" << DEFAULT << "  | |"
             << "\n| |  " << color << "'_.____. |" << DEFAULT << "  | |"
             << "\n| |  " << color << "| \\____| |" << DEFAULT << "  | |"
             << "\n| |  " << color << " \\______,'" << DEFAULT << "  | |"
             << "\n| |    (" << row << ", " << col << ")    | |"
             << "\n| '--------------' |"
             << "\n '----------------' \n";
            break;
    }

    //By using escape sequences, you can go back through output to
    //print over what is already on the terminal. Instead of doing
    //the logic to add the minimap during a focus inside the logic
    //to add the main image, it'd just be easier to do it after the fact

    //First, save the location where the option menu will be
    //and move up to the corresponding row of the coordinate
    //Then, move 25 right
    saveLocation();
    moveUp(11 - row);
    moveRight(25);

    for(size_t i = 0; i < 9; i++) {
        cout << *(horizontal[i]);
    }

    //Go back to the saved position, and move up 10 to the top
    //of the minimap and over to the corresponding column
    //of the current coordinate
    returnToSavedLocation();
    moveUp(10);
    moveRight(24 + col);

    //Each time, print, and then move one row down, and move
    //one column left to realign with the relevant column
    for(size_t i = 0; i < 9; i++) {
        cout << *(vertical[i]) << "\033[1B\033[1D";
    }

    //Go back to the saved location, then move to the top left
    //of the relevant subgrid
    returnToSavedLocation();
    moveUp(11 - getMinCoord(row));
    moveRight(24 + getMinCoord(col));

    //Once each row is printed, move back to the first column of
    //said subgrid and one row down
    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            cout << *(grid[(i * 3) + j]);
        }
        moveLeft(3);
        moveDown(1);
    }

    //To get the white pip in the right location,
    //first move up so you're in the correct row
    switch(row % 3) {
        case 1:
        moveUp(3);
        break;
        case 2:
        moveUp(2);
        break;
        case 0:
        moveUp(1);
        break;
    }

    //Then move left
    switch(col % 3) {
        case 2:
        moveRight(1);
        break;
        case 0:
        moveRight(2);
        break;
    }

    //Print the white pip, go back
    //to the default colors and return to the
    //original position
    cout << "\033[47m " << DEFAULT;
    returnToSavedLocation();

    //Go up 10, right 44, then print the header of this section
    //Then go 23 left and 1 down
    moveUp(8);
    moveRight(44);
    cout << "NUMBERS  FULLFILLED";
    moveLeft(22);
    moveDown(1);
    cout << "HORIZONTALLY: [";

    for(size_t i = 0; i < 9; i++) {
        if(horizontalOccupied[i]) {
            cout << i + 1;
        } else {
            cout << " ";
        }
    }
    cout << ']';

    moveLeft(25);
    moveDown(1);
    cout << "VERTICALLY:   [";

    for(size_t i = 0; i < 9; i++) {
        if(verticalOccupied[i]) {
            cout << i + 1;
        } else {
            cout << " ";
        }
    }
    cout << ']';

    moveLeft(25);
    moveDown(1);
    cout << "IN SUBGRID:   [";
    for(size_t i = 0; i < 9; i++) {
        if(gridOccupied[i]) {
            cout << i + 1;
        } else {
            cout << " ";
        }
    }
    cout << ']';

    returnToSavedLocation();

    if(!pregenerated()) {
        cout << "NOTES:   [";
        for(size_t i = 0; i < 9; i++) {
            if(horizontalOccupied[i] || verticalOccupied[i] || gridOccupied[i]) {
                notations[i] = false;
            }

            if(notations[i]) {
                cout << i + 1;
            } else {
                cout << " ";
            }
        }
        cout << ']';
    }

    cout << "\n      OPTIONS:      "
    << "\n1-9         Assign a number"
    << "\nArrow keys  Move around board"
    << (!pregenerated() ? "\nN, n        Notate this square" : "\n")
    << ((occupied() && !pregenerated()) ? "\nBackspace   Erase" : "\n")
    << "\nEnter       Back to board" << endl;

    char input = getch();

    switch(input) {
        case 127:
        return 0;
        break;

        case 'N':
        case 'n': {
            if(!pregenerated()) {
                cout << "Press number to add or remove it from annotations" << endl;
                input = getch();

                if(input < '0' || input > '9') {
                    cout << "Error: Not a valid move. Press anywhere to continue\n" << endl;
                    getch();
                } else {
                    notations[input - '1'] = !(notations[input - '1']);
                }
            }
        }
        break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return input - '0';
        break;

        case '\n':
        return 10;
        break;

        case 27:
        getch();
        return getch();
        break;
    }
    return focus(row, col, vertical, horizontal, grid, horizontalOccupied, verticalOccupied, gridOccupied);
}

void BoardSquare::empty() {
    value = 0;
    status = SquareStatus::empty;
}

bool BoardSquare::operator!=(size_t val) const {
    return value != val;
}

bool BoardSquare::operator==(size_t val) const {
    return value == val;
}

BoardSquare& BoardSquare::operator=(size_t val) {
    value = val;
    status = SquareStatus::preloaded;
    return *this;
}

bool BoardSquare::occupied() const {
    return status != SquareStatus::empty;
}