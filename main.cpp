#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include <iostream>
using std::cin;
using std::cout;
using std::getline;
using std::cerr;
using std::endl;
using std::flush;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <getopt.h>
#include <unistd.h>

//Global Vars
ifstream inputFile;
ofstream outputFile;

bool solve = false;



void printBanner() {
    cout << "************************************************************\n*                          SUDOKU                          *\n*                Solving, Playing, and More                *\n*                                                          *\n*                A program by By Zalan Shah                *\n************************************************************\n"
         << endl;
}

void printHelp() {
    cout << "Sudoku is a game played on a 9x9 grid. Initially, the board will randomly have numbers filled in. To complete a board, you must fill the grid with numbers, with three main caveats:\n"
    << "\t- A number cannot be repeated in its row\n"
    << "\t- A number cannot be repeated in its column\n"
    << "\t- A number cannot be repeated in its 3x3 sub-grid\n\n"
    << "PROGRAM FLAGS:\n"
    << "\t--help, -t\n"
    << "\t\t- This command will provide you with information on how to use this program, including all flags and options\n"
    << "\t--solve <filename>, -s <filename>\n"
    << "\t\t- Takes a .txt file that contains an unsolved 9x9 board, and prints the solved board\n"
    << "\t--play, -p\n"
    << "\t\t- This command is a work in progress :)\n"
    << "\t--generate [filename], -g [filename]\n"
    << "\t\t- This command is a work in progreess :)\n"
    << "\t--version, -v\n"
    << "\t\t- Prints the current version of this program\n\n"
    << "Running without any flags will provide you with a menu to make decisions from" << endl;
}


void clear() {
    if(system("clear") != 0) {
        exit(1);
    }
}

void printMenu() {
    printBanner();

    cout << "Welcome to Sudoku. Please select an option below to begin:\n"
    << "S [filename], s [filename]     Solve\n"
    << "G [filename], g [filename]     Generate\n"
    << "P, p                           Play\n"
    << "H, h                           Help\n"
    << "Q, q                           Quit" << endl;


    string input;
    getline(cin, input);

    switch(toupper(input[0])) {
        case 'S':
            if(input.length() == 1) {
                cout << "Enter input file name: " << flush;
                getline(cin, input);
            } else {
                input = input.substr(2, input.size());
            }
            inputFile.open(input);

            if(!inputFile.is_open()) {
                cerr << "Error: File does not exist: " << input << endl;
                sleep(2);
                clear();
                printMenu();
                return;
            } else if(input.substr(input.find('.'), input.size()) != ".txt") {
                cerr << "Error: Input must be a text file: " << input << endl;
                inputFile.close();
                sleep(2);
                clear();
                printMenu();
                return;
            } else {
                SudokuBoard board(inputFile);
                SudokuSolver solver(board);

                if(solver.solveBoard()) {
                    solver.printBoard();
                } else {
                    cerr << "Error: The given board has no valid solution" << endl;
                }
                cout << "Press Enter to continue" << endl;
                inputFile.close();
                cin.get();
                clear();
                printMenu();
                return;
            }
        break;

        case 'G':
        cout << "This is currently a work in progress. Press Enter to continue." << endl;
            // if(input.length() == 1) {
            //     cout << "Enter output file name: " << flush;
            //     getline(cin, input);
            // } else {
            //     input = input.substr(2, input.size());
            // }
            // outputFile.open(input);

            // if(!outputFile.is_open()) {
            //     cerr << "Error: File does not exist: " << input << endl;
            //     sleep(2);
            //     clear();
            //     return printMenu();
            // } else if(input.substr(input.find('.'), input.size()) != ".txt") {
            //     cerr << "Error: Input must be a text file: " << input << endl;
            //     outputFile.close();
            //     sleep(2);
            //     clear();
            //     return printMenu();
            // } else {
            //     SudokuBoard board;
            //     board.generate();
            //     board.print(outputFile);

            //     cout << "Generated output to " << input << ".\nPress Enter to continue" << endl;
            //     outputFile.close();
                cin.get();
                clear();
                return printMenu();
            // }

        break;
        case 'P':
        cout << "This is currently a work in progress. Press Enter to continue." << endl;
        cin.get();
        clear();
        return printMenu();

        break;
        case 'H':
        printHelp();
        cout << "Press ENTER to exit..." << endl;
        cin.get();
        case 'Q':
            clear();
            printBanner();
            sleep(2);
            clear();
            exit(0);
        break;

        default:
        cerr << "Error: Invalid option: " << input
        << "\nPress anywhere to continue" << flush;
        cin.get();
        clear();
        printMenu();
        return;
        break;
    }
}

void readArguments(int argc, char** argv) {
    int choice;
    int option_index = 0;
    option long_options[] = {
        { "help",        no_argument,       nullptr, 'h'  },
        { "solve",       required_argument, nullptr, 's'  },
        { "play",        no_argument,       nullptr, 'p'  },
        { "generate",    required_argument, nullptr, 'g'  },
        { "version",     no_argument,       nullptr, 'v'  },
        { nullptr,       no_argument,       nullptr, '\0' }
    };

    // while((choice = getopt_long(argc, argv, "hi:o:", long_options, &option_index)) != -1) {
    while((choice = getopt_long(argc, argv, "hs:pg:v", long_options, &option_index)) != -1) {
        switch(choice) {
            case 'h': {
                printHelp();
                exit(0);
            }
            break;

            case 's': {
                string fileName = optarg;
                inputFile.open(fileName);

                if(!inputFile.is_open()) {
                    cerr << "Error: File does not exist: " << fileName << endl;
                    exit(1);
                } else if(fileName.substr(fileName.find('.'), fileName.size()) != ".txt") {
                    cerr << "Error: Input must be a text file: " << fileName << endl;
                    exit(1);
                }
                solve = true;
            }
            break;

            case 'p': {
                cout << "This is a work in progress :)" << endl;
                exit(0);
            }
            break;

            case 'g': {
                cout << "This is a work in progress :)" << endl;
                exit(0);
            }
            break;

            case 'v': {
                cout << "v1.0.0" << endl;
                exit(0);
            }
        }
    }
}

int main(int argc, char **argv) {
    readArguments(argc, argv);

    if(system("clear") != 0) {
        exit(1);
    }



    if(solve) {
        SudokuBoard board(inputFile);
        SudokuSolver solver(board);

        if(solver.solveBoard()) {
            solver.printBoard();
            exit(0);
        } else {
            cerr << "Error: The given board has no valid solution" << endl;
            exit(1);
        }
    }
    clear();
    printMenu();




    // SudokuSolver sudoku(argc, argv);
}