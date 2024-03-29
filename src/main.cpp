#include "main.h"
#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include "utilityFunctions.h"
#include "global.h"
#include <iostream>
using std::cin;
using std::cout;
using std::getline;
using std::cerr;
using std::endl;
using std::flush;
#include <string>
using std::string;
#include <cctype>
using std::isspace;
#include <fstream>
using std::fstream;
#include <sstream>
using std::stringstream;
#include <functional>
using std::hash;
#include <string.h>
#include <fstream>
using std::ifstream;
#include <iterator>
using std::size_t;
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <termios.h>
#include <pwd.h>

extern Settings settings;

void printBanner() {
    cout <<   "************************************************************"
         << "\n*                          SUDOKU                          *"
         << "\n*                Solving, Playing, and More                *"
         << "\n*                                                          *"
         << "\n*                A program by By Zalan Shah                *"
         << "\n************************************************************\n"
         << endl;
}

void printHelp() {
    cout << "Sudoku is a game played on a 9x9 grid. Initially, the board will randomly have numbers filled in. To complete a board, you must fill the grid with numbers, with three main caveats:\n"
    << "\t- A number cannot be repeated in its row\n"
    << "\t- A number cannot be repeated in its column\n"
    << "\t- A number cannot be repeated in its 3x3 sub-grid\n\n"
    << "PROGRAM FLAGS:\n"
    << "\t--help, -h\n"
    << "\t\t- This command will provide you with information on how to use this program, including all flags and options\n"
    << "\t--solve <filename>, -s <filename>\n"
    << "\t\t- Solves a given board in <filename>, and prints the solved board to the terminal\n"
    << "\t--play, -p\n"
    << "\t\t- Play the game. If a seed hasn't been entered, a random seed is generated and a random board is given.\n"
    << "\t\t- Pressing Enter on any given square allows you to focus on that square. This gives you extra information about the square.\n"
    << "\t\t- While focused, you can press N to notate the board, allowing you to take notes.\n"
    << "\t\t- Pressing backspace on a square deletes the number currently in it.\n"
    << "\t\t- Pressing S provides you with the seed.\n"
    << "\t\t- Pressing Q quits the game.\n"
    << "\t\t- At the end, you are given the time it took you to solve the board.\n"
    << "\t--generate [filename], -g [filename]\n"
    << "\t\t- Generates a random sudoku board, and prints it to [filename] if given. If [filename] isn't given, the board is printed to the terminal\n"
    << "\t\t- If the difficulty flag is being used, a board will be generated according to the difficulty specified.\n"
    << "\t\t- If one isn't specified, the default difficulty is set to medium\n"
    << "\t--difficulty < EASY | MEDIUM | HARD | IMPOSSIBLE >, -d < EASY | MEDIUM | HARD | IMPOSSIBLE >\n"
    << "\t--solve <seed>, -S <seed>\n"
    << "\t\t- Seeds all generations with a given seed\n"
    << "\t\t- If this flag isn't specified, a random seed is generated\n"
    << "\t\t- Specifies the difficulty of a randomly generated board, and erases as many board squares as needed\n"
    << "\t--version, -v\n"
    << "\t\t- Prints the current version of this program\n\n"
    << "Running without any flags will provide you with a menu to make decisions from." << endl;
}

void tryValue(SudokuBoard &board, const size_t row, const size_t col, const size_t val) {
    if(board(row, col).pregenerated()) {
        return;
    }

    board.empty(row, col);

    if(board.verify(row, col, val)) {
            board.tryNum(row, col, val);
    } else {
        board.tryIncorrect(row, col, val);
    }
}

void focus(SudokuBoard &board, size_t &row, size_t &col) {
    BoardSquare *horizontal[9];
    BoardSquare *vertical[9];
    BoardSquare *grid[9];
    bool horizontalOccupied[9] = {false};
    bool verticalOccupied[9] = {false};
    bool gridOccupied[9] = {false};

    board.getSubgrid(row, col, grid);
    for(size_t i = 1; i < 10; i++) {
        horizontal[i - 1] = &board(row, i);
        vertical[i - 1] = &board(i, col);

        if(horizontal[i - 1]->getValue()) {
            horizontalOccupied[horizontal[i - 1]->getValue() - 1] = true;
        }
        if(vertical[i - 1]->getValue()) {
            verticalOccupied[vertical[i - 1]->getValue() - 1] = true;
        }
        if(grid[i - 1]->getValue()) {
            gridOccupied[grid[i - 1]->getValue() - 1] = true;
        }
    }

    size_t result = board(row,col).focus(row, col, horizontal, vertical, grid, horizontalOccupied, verticalOccupied, gridOccupied);
    switch(result) {
        case 0:
        if(!board(row, col).pregenerated()) {
            board.empty(row, col);
        }
        break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            tryValue(board, row, col, result);
            if(board.solved()) {
                return;
            }
        break;
        case 10:
        return;

        case 'A':
            row = (row == 1) ? 1 : row - 1;
            break;
        case 'B':
            row = (row == 9) ? 9 : row + 1;
            break;
        case 'C':
            col = (col == 9) ? 9 : col + 1;
            break;
        case 'D':
            col = (col == 1) ? 1 : col - 1;
            break;
    }

    focus(board, row, col);
}

void seedify() {
    hash<string> hasher;
    seedNum = (unsigned int)hasher(seed);
    srand(seedNum);
}

void play() {
    size_t row = 5;
    size_t col = 5;

    SudokuBoard board;
    board.generate(settings.difficulty);
    time_t beginTime, endTime;
    time(&beginTime);

    do {
        clear();
        board.print(row, col);

        char input = getch();

        switch(input) {
            case 27:
            getch();
            switch(getch()) {
                case 'A':
                    row = (row == 1) ? 1 : row - 1;
                    break;
                case 'B':
                    row = (row == 9) ? 9 : row + 1;
                    break;
                case 'C':
                    col = (col == 9) ? 9 : col + 1;
                    break;
                case 'D':
                    col = (col == 1) ? 1 : col - 1;
                    break;
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
            tryValue(board, row, col, input - 48);
            break;
            case 'S':
            case 's':
            cout << "Seed: " << seed
            << "\nPress any key to continue" << flush;
            getch();
            break;
            case 'Q':
            case 'q':
            seed = to_string(((unsigned int)time(NULL)));
            seedify();
            return;
            break;
            case 10:
            focus(board, row, col);
            break;
            case 127:
            if(!board(row, col).pregenerated()) {
                board.empty(row, col);
            }
        }
    } while(!board.solved());

    time(&endTime);
    time_t timeElapsed =  endTime - beginTime;
    struct tm *timeInfo = gmtime(&timeElapsed);
    char buffer[9];
    strftime(buffer, 9, "%H:%M:%S", timeInfo);
    seed = to_string(((unsigned int)time(NULL)));
    seedify();

    clear();

    cout << "    B O A R D   C O M P L E T E D    ";
    board.print();
    cout << "You completed this board in " << buffer << "\nPress any key to continue" << endl;
    getch();

    return printMenu();
}

void printMenu() {
    clear();
    printBanner();

    cout << "Welcome to Sudoku. Please select an option below to begin:\n"
    << "P, p     Play\n"
    << "S        Seed\n"
    << "D, d     Difficulty\n"
    << "G, g     Generate\n"
    << "s        Solve\n"
    << "H, h     Help\n"
    << "V, v     Version\n"
    << "Q, q     Quit" << endl;


    char input = getch();

    switch(input) {
        case 's':
            cout << "Enter input file name: " << SHOWCURSOR << flush;
            getline(cin, solve);
            cout << HIDECURSOR << flush;
            inputFile.open(solve);

            if(!inputFile.is_open()) {
                cerr << "Error: File does not exist: " << solve << endl;
                cout << "Press any key to continue";
                getch();
                return printMenu();
            } else if(solve.substr(solve.find('.'), solve.size()) != ".txt") {
                cerr << "Error: Input must be a text file: " << solve << endl;
                cout << "Press any key to continue";
                getch();
                return printMenu();
            } else {
                SudokuBoard board(inputFile);
                SudokuSolver solver(board);

                if(solver.solveBoard()) {
                    board.print();
                } else {
                    cerr << "Error: The given board has no valid solution" << endl;
                }
                cout << "Press any key to continue" << endl;
                inputFile.close();
                getch();
                return printMenu();
            }
        break;

        case 'G': case 'g':
            cout << "Enter output file name: " << SHOWCURSOR << flush;
            getline(cin, generate);
            cout << HIDECURSOR << flush;
            outputFile.open(generate);

            if(!outputFile.is_open()) {
                cerr << "Error: File does not exist: " << generate << endl;
                cout << "Press any key to continue";
                getch();
                return printMenu();
            } else if(generate.substr(generate.find('.'), generate.size()) != ".txt") {
                cerr << "Error: Input must be a text file: " << generate << endl;
                cout << "Press any key to continue";
                outputFile.close();
                getch();
                return printMenu();
            } else {
                SudokuBoard board;
                board.generate(settings.difficulty);
                board.print(outputFile);

                cout << "Generated output to " << generate << "\nPress any key to continue" << endl;
                getch();
                outputFile.close();
                return printMenu();
            }
        break;

        case 'P': case 'p':
        play();
        return printMenu();
        break;

        case 'S':
        cout << "Enter Seed: " << SHOWCURSOR << flush;
        getline(cin, seed);
        cout << HIDECURSOR << flush;
        seedify();
        return printMenu();
        break;

        case 'D': case 'd': {
            cout << "Difficulty must be either EASY MEDIUM HARD or IMPOSSIBLE\nEnter difficulty: " << SHOWCURSOR << flush;

            string newDifficulty;
            getline(cin, newDifficulty);

            cout << HIDECURSOR << flush;

            if(newDifficulty == "EASY" || newDifficulty == "easy") {
                settings.difficulty = SudokuBoard::Difficulty::EASY;
            } else if(newDifficulty == "MEDIUM" || newDifficulty == "medium") {
                settings.difficulty = SudokuBoard::Difficulty::MEDIUM;
            } else if(newDifficulty == "HARD" || newDifficulty == "hard") {
                settings.difficulty = SudokuBoard::Difficulty::HARD;
            } else if(newDifficulty == "IMPOSSIBLE" || newDifficulty == "impossible") {
                settings.difficulty = SudokuBoard::Difficulty::IMPOSSIBLE;
            } else {
                cerr << "Error: Unknown difficulty. Difficulty may only be EASY, MEDIUM, HARD, or IMPOSSIBLE\nPress any key to continue" << flush;
                getch();
                return printMenu();
            }

            return printMenu();
        }

        case 'H': case 'h':
        printHelp();
        cout << "Press any key to continue" << endl;
        getch();
        return printMenu();
        break;

        case 'V': case 'v':
        cout << "v"<< VERSIONNUMBER <<"\nPress any key to continue" << endl;
        getch();
        return printMenu();
        break;

        case 'Q': case 'q':
            clear();
            cout << SHOWCURSOR << ORIGINALSCREEN << flush;
            exit(0);
        break;

        default:
        cerr << "Error: Invalid option: " << input
        << "\nPress anywhere to continue" << flush;
        getch();
        return printMenu();
        break;
    }
}

void readArguments(int argc, char** argv) {
    int choice;
    int option_index = 0;
    option long_options[] = {
        { "help",       no_argument,       nullptr, 'h'  },
        { "solve",      required_argument, nullptr, 's'  },
        { "play",       no_argument,       nullptr, 'p'  },
        { "generate",   required_argument, nullptr, 'g'  },
        { "difficulty", required_argument, nullptr, 'd'  },
        { "seed",       required_argument, nullptr, 'S'  },
        { "version",    no_argument,       nullptr, 'v'  },
        { nullptr,      no_argument,       nullptr, '\0' }
    };

    while((choice = getopt_long(argc, argv, "hs:pg:d:S:v", long_options, &option_index)) != -1) {
        switch(choice) {
            case 'h': {
                printHelp();
                exit(0);
            }
            break;

            case 's':
            solve = optarg;
            inputFile.open(solve);

            if(!inputFile.is_open()) {
                cerr << "Error: File does not exist: " << solve << endl;
                exit(1);
            } else if(solve.substr(solve.find('.'), solve.size()) != ".txt") {
                cerr << "Error: Input file must be a text file: " << solve << endl;
                inputFile.close();
                exit(1);
            }
            break;

            case 'p':
                play();
            break;

            case 'g':
            generate = optarg;
            outputFile.open(generate);

            if(!outputFile.is_open()) {
                cerr << "Error: File does not exist: " << generate << endl;
                exit(1);
            } else if(generate.substr(generate.find('.'), generate.size()) != ".txt") {
                cerr << "Error: Output file must be a text file: " << generate << endl;
                outputFile.close();
                exit(1);
            }
            break;

            case 'd':
            if(strcmp(optarg, "EASY") == 0 || strcmp(optarg, "easy") == 0) {
                settings.difficulty = SudokuBoard::Difficulty::EASY;
            } else if(strcmp(optarg, "MEDIUM") == 0 || strcmp(optarg, "medium") == 0) {
                settings.difficulty = SudokuBoard::Difficulty::MEDIUM;
            } else if(strcmp(optarg, "HARD") == 0 || strcmp(optarg, "hard") == 0) {
                settings.difficulty = SudokuBoard::Difficulty::HARD;
            } else if(strcmp(optarg, "IMPOSSIBLE") == 0 || strcmp(optarg, "impossible") == 0) {
                settings.difficulty = SudokuBoard::Difficulty::IMPOSSIBLE;
            } else {
                cerr << "Error: Unknown difficulty: " << optarg << ". Difficulty may only be EASY, MEDIUM, HARD, or IMPOSSIBLE" << endl;
                exit(1);
            }
            break;

            case 'S': {
                seed = optarg;
                seedify();
            }
            break;

            case 'v': {
                cout << "v" << VERSIONNUMBER << endl;
                exit(0);
            }
        }
    }

    srand(seedNum);
}

int main(int argc, char **argv) {
    readArguments(argc, argv);

    if(solve != "") {
        SudokuBoard board(inputFile);
        inputFile.close();
        SudokuSolver solver(board);

        if(solver.solveBoard()) {
            board.print();
            exit(0);
        } else {
            cerr << "Error: The given board has no valid solution" << endl;
            exit(1);
        }
    } else if(generate != "") {
        SudokuBoard board;
        board.generate(settings.difficulty);

        board.print(outputFile);
        exit(0);
    }

    cout << ALTERNATESCREEN << HIDECURSOR << flush;

    printMenu();
}