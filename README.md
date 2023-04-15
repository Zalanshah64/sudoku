<div id="top"></div>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

Table of Contents

- [About](#about)
  - [Playing Sudoku](#playing-sudoku)
  - [Playing the Game](#playing-the-game)
  - [Generating Random Boards](#generating-random-boards)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Input files](#input-files)
  - [Command Line Flags](#command-line-flags)
  - [Normal Usage](#normal-usage)
- [License](#license)
- [Contact](#contact)
- [Acknowledgments](#acknowledgments)


## About

This is a terminal-based version of the game Sudoku that will allow players to play, randomly generate, and instantly solve sudoku boards.

### Playing Sudoku
Sudoku is played on a 9x9 grid of numbers, broken up into 9 smaller 3x3 subgrids. A player must solve a board by putting a number between 1 and 9 in each square of the board. In addition, in order to be considered valid, every filled in square must:

- have a number that does not appear anywhere else along its row
- have a number that does not appear anywhere else along its column
- have a number that does not appear anywhere else in its subgrid

### Playing the Game

To play the game, you can either load the program as normal and press ```P``` to play, or you can run ```./sudoku -p```

Updating the difficulty and the seed will generate a completely different board. By default, the difficulty is set to `NORMAL`, and the seed is based on the current time.

When you begin a game, you will be loaded into a randomly generated board. You will be able to move your cursor (the white pip on the board) up, down, left, and right by using the arrow keys. By pressing a number from 1 to 9, you can write that number to the specific square. There are several different colors denoting different things:
- Blue
  - Numbers that were pregenerated. They can not be overwritten or modified.
- Green
  - Squares with valid numbers that you have inputted
- Red
  - Numbers that cause a conflict in their horizontal, vertical, or subgrid set
  - These will take over blue and green colorings
- Gray
  - Squares that belong to the same horizontal, vertical, or subgrid set as your current location
- Orange
  - Squares with the same number as the square you are currently on
- White
  - Your current location

You can either play the game on the main board, or choose to focus into a specific square. Focusing into a square will give you plenty of useful information:
- Notations
  - By pressing `N`, you can add a notation to a specific square. This allows you to keep track of possible numbers a square could be.
  - If you try to notate an invalid square, the game will automatically remove it for you.

- Coordinates

- Minimap
  - A minimap of related squares is shown next to the main square. Related squares consist of squares that fall in the same vertical, horizontal, or subgrid as the selected coordinate

- Fulfilled
  - The horizontal, vertical, and subgrid must each contain 1 through 9 once each. Three lists showing which numbers exist in each set are shown.

### Generating Random Boards

You can generate a random board by using the `-g <filename>` or `--g <filename>` commands, where `filename` is the name of the file where the generated board is outputted to.

This can be affected by the seed and the difficulty given.

<p align="right">(<a href="#top">back to top</a>)</p>



## Getting Started

### Prerequisites

- Sudoku has only been programmed for Unix systems. Running this program is dependent on a Linux shell, and may not properly work otherwise.

- g++
  ```sh
  sudo apt install g++
  ```

- make
  ```sh
  sudo apt install make
  ```

### Installation

```sh
  make
```

<p align="right">(<a href="#top">back to top</a>)</p>



## Usage

### Input files

A valid input file must be a `.txt` file, and must be exactly 81 characters long. It should be 9 characters per line, each one being either a dash (i.e. "-" ) or a number between 1 and 9. Additionally, the board must not be [invalid](#playing-sudoku).  An example of a valid board would be:

```
926--8-1-
-58-2-3-7
---5--82-
-9--57---
--39---7-
---61---5
56----7--
-------8-
2-1---69-
```

### Command Line Flags

- -s \<`filename`\>, --solve \<`filename`\>
    - Solves a given board from `filename` and prints it out
- -g \<`filename`\>, --generate \<`filename`\>
    - Generates a random board with some number of empty squares (based on the difficulty level) and outputs it to `filename`
    - `filename` must be a .txt file
- -d \<`EASY` | `MEDIUM` | `HARD` | `IMPOSSIBLE`\>, --difficulty \<`EASY` | `MEDIUM` | `HARD` | `IMPOSSIBLE`\>
    - Sets the difficulty of the board to be either easy, medium, hard, or impossible
    - The higher the difficulty, the fewer squares a board will start with
- -S <`seed`>, --seed <`seed`>
    - Seeds a board generation with `seed`, ensuring the exact same board given the same seed
    - `seed` may not contain any whitespace
- -h, --help
    - Prints help information
- -v, --version
    - Prints the current version

### Normal Usage
When just running the program, you will be greeted with a menu interface that wil ask you what you'd like to do. These will be largely the same as the [command line flags.](#command-line-flags)

<p align="right">(<a href="#top">back to top</a>)</p>

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

## Contact

Project Link: [https://github.com/zalanshah64/sudoku](https://github.com/zalanshah64/sudoku)

LinkedIn: [https://linkedin.com/in/zalan-shah](linkedin-url)

<p align="right">(<a href="#top">back to top</a>)</p>



## Acknowledgments

- [Othneil Drew for providing the template for this README.md](https://github.com/othneildrew/Best-README-Template)

- [manytools.org for providing the Blocks font for focused squares](https://manytools.org/hacker-tools/ascii-banner/)

<p align="right">(<a href="#top">back to top</a>)</p>



[contributors-shield]: https://img.shields.io/github/contributors/zalanshah64/sudoku.svg?style=for-the-badge
[contributors-url]: https://github.com/zalanshah64/sudoku/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/zalanshah64/sudoku.svg?style=for-the-badge
[forks-url]: https://github.com/zalanshah64/sudoku/network/members
[stars-shield]: https://img.shields.io/github/stars/zalanshah64/sudoku.svg?style=for-the-badge
[stars-url]: https://github.com/zalanshah64/sudoku/stargazers
[issues-shield]: https://img.shields.io/github/issues/zalanshah64/sudoku.svg?style=for-the-badge
[issues-url]: https://github.com/zalanshah64/sudoku/issues
[license-shield]: https://img.shields.io/github/license/zalanshah64/sudoku.svg?style=for-the-badge
[license-url]: https://github.com/zalanshah64/sudoku/blob/master/LICENSE.md
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/zalan-shah
