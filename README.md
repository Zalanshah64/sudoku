<div id="top"></div>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## About

This is a terminal-based version of the game Sudoku that will allow players to play, randomly generate, and instantly solve sudoku boards.

### Playing Sudoku
<div id="validity">
Sudoku is played on a 9x9 grid of numbers, broken up into 9 smaller 3x3 subgrids. A player must solve a board by putting a number between 1 and 9 in each square of the board. In addition, in order to be considered valid, every filled in square must:

* have a number that does not appear anywhere else along its row
* have a number that does not appear anywhere else along its column
* have a number that does not appear anywhere else in its subgrid

### Playing the Game

This part of the game is still a work in progress. It depends on being able to generate random boards, which I am still working on making an algorithm for. Stay tuned to be able to play real games soon :)

### Generating Random Boards

This part of the game is still a work in progress. I haven't figured out an algorithm for creating valid boards just yet. Stay tuned to see how I implement this :)

<p align="right">(<a href="#top">back to top</a>)</p>



## Getting Started

### Prerequisites

* Sudoku has only been programmed for Unix systems. Running this program is dependent on a Linux shell, and may not properly work otherwise.

* g++
  ```sh
  sudo apt install g++
  ```

* make
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

A valid input file must be a `.txt` file, and must be exactly 81 characters long. It should be 9 characters per line, each one being either an underscore (i.e. "_" ) or a number between 1 and 9. Additionally, the board must not be <a href="#validity">invalid</a>.  An example of a valid board would be:

```
926__8_1_
_58_2_3_7
___5__82_
_9__57___
__39___7_
___61___5
56____7__
_______8_
2_1___69_
```

<div id="commandLineArguments">
### Command Line Arguments

* -s \<filename\>, --solve \<filename\>
    * Solves a given board from `filename` and prints it out
* -g \<filename\>, --generate \<filename\>
    * Generates a random board and outputs it to `filename` (This is still a work in progress :) )
* -h, --help
    * Prints help information

### Normal Usage
When just running the program, you will be greeted with a menu interface that wil ask you what you'd like to do. These will be largely the same as the <a href="#commandLineArguments">command line arguments,</a> with the addition of:

* P
    * Generates a random board and allows you to play the game (This is still a work in progress :) )

<p align="right">(<a href="#top">back to top</a>)</p>

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

## Contact

Project Link: [https://github.com/zalanshah64/sudoku](https://github.com/zalanshah64/sudoku)

LinkedIn: [https://linkedin.com/in/zalan-shah](linkedin-url)

<p align="right">(<a href="#top">back to top</a>)</p>



## Acknowledgments

* [Othneil Drew for providing the template for this README.md](https://github.com/othneildrew/Best-README-Template)

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
[license-url]: https://github.com/zalanshah64/sudoku/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/zalan-shah