#include "SudokuBoard.h"
#include <string>
using std::string;
#include <fstream>
using std::fstream;

struct Settings {
    SudokuBoard::Difficulty difficulty;
    string rcFileName;
    fstream rcFile;
};