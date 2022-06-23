#pragma once
#include "SudokuBoard.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;


ifstream inputFile;
ofstream outputFile;
string solve;
string generate;
SudokuBoard::Difficulty difficulty = SudokuBoard::Difficulty::MEDIUM;
unsigned int seed = (unsigned int)time(NULL);

void printBanner();
void printHelp();
void tryValue(SudokuBoard &board, const size_t row, const size_t col, const size_t val);
void focus(SudokuBoard &board, size_t &row, size_t &col);
void play();
void printMenu();
void readArguments(int argc, char** argv);
int main(int argc, char **argv);
