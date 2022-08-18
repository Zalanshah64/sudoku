#pragma once
#include "SudokuBoard.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
#include <iterator>
using std::size_t;


#define ALTERNATESCREEN "\033[?1049h"
#define ORIGINALSCREEN "\033[?1049l"
#define VERSIONNUMBER "1.3.3"

ifstream inputFile;
ofstream outputFile;
string solve;
string generate;
SudokuBoard::Difficulty difficulty = SudokuBoard::Difficulty::MEDIUM;
string seed = to_string((unsigned int)time(NULL));
unsigned int seedNum;

void printBanner();
void printHelp();
void tryValue(SudokuBoard &board, const size_t row, const size_t col, const size_t val);
void focus(SudokuBoard &board, size_t &row, size_t &col);
void seedify();
void play();
void printMenu();
void readArguments(int argc, char** argv);
int main(int argc, char **argv);
