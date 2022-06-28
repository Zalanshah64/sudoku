#include "utilityFunctions.h"
#include <iostream>
using std::cout;
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

void clear() {
    if(system("clear") != 0) {
        exit(1);
    }
}

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }

 size_t getMinCoord(const size_t coord) {
    switch(coord) {
        case 1: case 2: case 3:
        return 1;
        case 4: case 5: case 6:
        return 4;
        case 7: case 8: case 9:
        return 7;
    }

    while(true) {
        cout << "This shouldn't happen.\n";
    }
    return -1;
}

// "\033" is an escape sequence
// "\033[#A" says go up # spaces
// "\033[#B" says go down # spaces
// "\033[#C" says go right # spaces
// "\033[#D" says go left # spaces
// "\0337" saves a location
// "\0338" goes back to the saved location instantly

void moveUp(size_t numToMove) {
    cout << "\033[" << numToMove << "A";
}

void moveDown(size_t numToMove) {
    cout << "\033[" << numToMove << "B";
}

void moveRight(size_t numToMove) {
    cout << "\033[" << numToMove << "C";
}

void moveLeft(size_t numToMove) {
    cout << "\033[" << numToMove << "D";
}

void saveLocation() {
    cout << "\0337";
}

void returnToSavedLocation() {
    cout << "\0338";
}