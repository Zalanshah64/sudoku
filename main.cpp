#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include <iostream>
using std::cin;
using std::cout;
using std::getline;
// using std::getch;
using std::cerr;
using std::endl;
using std::flush;
#include <string>
using std::string;
#include <functional>
using std::hash;
#include <string.h>
#include <fstream>
using std::ifstream;
#include <getopt.h>
#include <unistd.h>
#include <termios.h>

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

//Global Vars
ifstream inputFile;
ofstream outputFile;

string solve;
string generate;

SudokuBoard::Difficulty difficulty = SudokuBoard::Difficulty::MEDIUM;
unsigned int seed = (unsigned int)time(NULL);

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
    << "\t--help, -h\n"
    << "\t\t- This command will provide you with information on how to use this program, including all flags and options\n"
    << "\t--solve <filename>, -s <filename>\n"
    << "\t\t- Solves a given board in <filename>, and prints the solved board to the terminal\n"
    << "\t--play, -p\n"
    << "\t\t- Play the game. This command is a work in progress and currently unplayable. Thank you for your understanding :)\n"
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

void clear() {
    if(system("clear") != 0) {
        exit(1);
    }
}

void tryValue(SudokuBoard &board, const size_t row, const size_t col, const size_t val) {
    if(board.verify(row, col, val)) {
            board.tryNum(row, col, val);
    } else {
        board.tryIncorrect(row, col, val);
    }
}

void play() {
    size_t row = 1;
    size_t col = 1;

    SudokuBoard board;
    board.generate(difficulty);

    do {
        clear();
        board.print(row, col);

        cout << "Input a direction, or input a number" << endl;
        char input = getch();

        if(input == 27) {
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
        } else {
            switch(input) {
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

            default:
            break;
            }
        }
    } while(!board.solved());
}

void printMenu() {
    clear();
    printBanner();

    cout << "Welcome to Sudoku. Please select an option below to begin:\n"
    << "s        Solve\n"
    << "G, g     Generate\n"
    << "P, p     Play\n"
    << "S        Seed\n"
    << "D, d     Difficulty\n"
    << "H, h     Help\n"
    << "V, v     Version\n"
    << "Q, q     Quit" << endl;


    char input = getch();

    switch(input) {
        case 's':
            cout << "Enter input file name: " << flush;
            getline(cin, solve);
            inputFile.open(solve);

            if(!inputFile.is_open()) {
                cerr << "Error: File does not exist: " << solve << endl;
                sleep(2);
                printMenu();
                return;
            } else if(solve.substr(solve.find('.'), solve.size()) != ".txt") {
                cerr << "Error: Input must be a text file: " << solve << endl;
                inputFile.close();
                sleep(2);
                printMenu();
                return;
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
                printMenu();
                return;
            }
        break;

        case 'G':
        case 'g':
            cout << "Enter output file name: " << flush;
            getline(cin, generate);
            outputFile.open(generate);

            if(!outputFile.is_open()) {
                cerr << "Error: File does not exist: " << generate << endl;
                sleep(2);
                clear();
                return printMenu();
            } else if(generate.substr(generate.find('.'), generate.size()) != ".txt") {
                cerr << "Error: Input must be a text file: " << generate << endl;
                outputFile.close();
                sleep(2);
                clear();
                return printMenu();
            } else {
                SudokuBoard board;
                board.generate(difficulty);
                board.print(outputFile);

                cout << "Generated output to " << generate << ".\nPress any key to continue" << endl;
                getch();
                outputFile.close();
                return printMenu();
            }
        break;

        case 'P':
        case 'p':
        play();
        return printMenu();
        break;

        case 'S': {
            cout << "Enter Seed: " << flush;
            getline(cin, generate);
            hash<string> hasher;
            seed = (unsigned int)hasher(generate);
            srand(seed);
            cout << "Seed successfully generated. Press any key to continue" << endl;
            getch();
            return printMenu();
        }

        break;

        case 'H':
        case 'h':
        printHelp();
        cout << "Press any key to continue" << endl;
        getch();
        return printMenu();
        break;

        case 'V':
        case 'v':
        cout << "Version 1.2.1\nPress any key to continue" << endl;
        return printMenu();
        break;

        case 'Q':
        case 'q':
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
        printMenu();
        return;
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
                difficulty = SudokuBoard::Difficulty::EASY;
            } else if(strcmp(optarg, "MEDIUM") == 0 || strcmp(optarg, "medium") == 0) {
                difficulty = SudokuBoard::Difficulty::MEDIUM;
            } else if(strcmp(optarg, "HARD") == 0 || strcmp(optarg, "hard") == 0) {
                difficulty = SudokuBoard::Difficulty::HARD;
            } else if(strcmp(optarg, "IMPOSSIBLE") == 0 || strcmp(optarg, "impossible") == 0) {
                difficulty = SudokuBoard::Difficulty::IMPOSSIBLE;
            } else {
                cerr << "Error: Unknown difficulty: " << optarg << ". Difficulty may only be EASY, MEDIUM, HARD, or IMPOSSIBLE" << endl;
                exit(1);
            }
            break;

            case 'S': {
                hash<string> hasher;
                seed = (unsigned int)hasher(optarg);
            }
            break;

            case 'v': {
                cout << "v1.2.1" << endl;
                exit(0);
            }
        }
    }

    srand(seed);
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
        board.generate(difficulty);

        board.print(outputFile);
        exit(0);
    }

    printMenu();
}