# Changelog

## v1.3.5: Restructured code

### Added or Changed
- Moved all source files to src directory
- Moved .h files to inc directory
- Updated Makefile to compile all files to objects first
    - Allows for quicker compilation
- Added bell when incorrect number is written
- Hide cursor when appropriate
- Added framework for settings
    - Will allow for future usage of settings
- Optimized terminal clearing
<br/>
<br/>

## v1.3.4: Why's this still a problem?

### Added or Changed
- Finally fixed bug where compilation didn't work on MacOS
- Added .gitignore to repository
    - Removed .gitignore from personal .gitignore
<br/>
<br/>

## v1.3.3: Man, I hate MacOS

### Added or Changed
- Updated --help flag
- Added new compilation flags for more comprehensive warnings
- Fixed bug where compilation wasn't working on MacOS
    - program now compiles with c++17 rather than older versions that don't support enum classes
<br/>
<br/>

## v1.3.2: Whoops, Forgot a Few Things

### Added or Changed
- Updated seeding algorithm
    - New seed is generated each time a game is played
    - Seed is available to see during a game
- Fixed compilation warnings
- Fixed bug where pregenerated board squares are deletable
- Fixed bug where screen clearing removes terminal history
<br/>
<br/>

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