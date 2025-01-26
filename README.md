# SudokuChallenge

This project involves developing a C++ program for playing and solving Sudoku puzzles. The program provides a user-friendly console interface for interacting with Sudoku puzzles, whether by loading an existing puzzle or generating a new one.

## Project Description

In this Sudoku game application, users can choose to load a Sudoku puzzle from a file or have the program generate a new puzzle. Users can then either manually input the solution or allow the program to automatically solve the puzzle. After each game, the application displays statistical data, including the number of correctly and incorrectly placed numbers and the game iteration count. Users can choose to play multiple iterations.

## Features

- **Game Initialization:**
  - Load command line arguments to handle file names.
  - Load a 9x9 Sudoku puzzle from a file in text format.
  - Save the Sudoku puzzle to a file with a clear and easy-to-understand format.
  - Provide options to load an existing puzzle or generate a new puzzle.

- **Game Mechanics:**
  - Display the Sudoku board in the console with clearly marked fields.
  - Offer options for the user to enter their solution by loading a file or allowing the program to solve it automatically.
  - Validate the user's solution to ensure each number appears only once per row, column, and 3x3 subgrid.
  - Automatically solve the Sudoku puzzle using efficient algorithms.
  - Generate a valid Sudoku puzzle setup with an average of no more than 6 filled cells per subgrid.

- **Game Statistics:**
  - Display the number of correctly and incorrectly placed numbers.
  - Display the iteration count of the game played.

## Implementation Steps

1. Define a class to represent the 9x9 Sudoku puzzle.
2. Implement functionality to load and save puzzles.
3. Implement functionality to validate user inputs.
4. Implement algorithms for solving the puzzle.
5. Implement functionality to generate new puzzle setups.
6. Ensure modularity of functionalities.

## Coding Style

- Include a brief description of functionality, authorship information, and last modification date in every header and source file.
- Comment on key functions, member functions, and class attributes, providing a brief description, input arguments, and return values.
- Pay attention to indentation, code formatting, naming conventions, and line lengths.
- Ensure the code is clean, readable, and well-commented.

