#pragma once
#include <cstddef>
using std::size_t;

void clear();
char getch(void);
size_t getMinCoord(const size_t coord);

void moveUp(size_t numToMove);
void moveDown(size_t numToMove);
void moveRight(size_t numToMove);
void moveLeft(size_t numToMove);
void saveLocation();
void returnToSavedLocation();