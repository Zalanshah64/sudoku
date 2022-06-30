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

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = (char)getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
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