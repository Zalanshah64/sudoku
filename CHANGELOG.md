# Changelog

## v1.3.1: Literally the Whole Game

### Added or Changed
- Added option to change difficulty in main menu
- Added ability to focus on square
    - Added ability to notate squares
    - Added minimap that shows affected squares
    - Added data on vertical, horizontal, and subgrid numbers filled
    - Added ability to remove and add numbers
    - Added ability to move around subgrid during focus
- Added ability to quit game
- Added timing to game
- Fixed bug where version isn't displayed correctly
- Standardized all errors to ask for enter to continue
- Added ability for board to determine when game is over
- Reduced difficulty of difficulties
- Updated README
- Fixed bug where incorrect squares stay incorrect
- Fixed bug where number being hovered over is hidden
<br/>
<br/>
## v1.2.1: It's All About the Game

### Added or Changed
- And how you play it
    - Added functionality to traverse a board
    - Added functionality to catch if a board square is invalid
- It's all about control
    - By using the seed command, you can now consistently generate the same game each time
    - Default is a seed based on the current time
- And if you can take it
    - Rather than "Press Enter to continue", you can now press any key
    - Pressed key doesn't show up on terminal
- It's all about the debt
    - Updated --help flag
    - Updated Readme
- And who's gonna pay it
    - Added difficulty, seed, and version options to main menu
- It's all about pain, and who's gonna make it
    - Fixed issue with makefile taking an excrutiating amount of time to compile
<br/>
<br/>
## v1.1.1: Generate, Difficulties, Splash of Color
### Added or Changed
- Added Generate feature
    - Added options for difficulty when generating board
- Added some colors to distinguish between "given" and "solved" squares when solving a board
- Updated --help flag
- Updated Readme
- Fixed bug where ./sudoku -s \<`filename`\> clears terminal
<br/>
<br/>
## v1.0.0: First implementation
### Added or Changed
- Added Menu
- Added implementation to solve given boards