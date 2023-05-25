/**
 * @file SudokuSolver.hpp
 * @author Jeffrey Oyuela
 * @brief This program aims to solve any given sudoku puzzle if possible. It will utilize recursive backtracking.
 * @date 2023-04-21
 * 
 */

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>


//We define Location within the Sudoku namespace.

namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
 
//Add your public members here
  
  /**
   @post Default Constructor that makes an empty 9x9 sudoku board
  */
  SudokuSolver();

  /**
   @param CSV file with integers for each element in the board
   @post Initializes the board based on what is read from the input_file
  */
  SudokuSolver(std::string input_file);

  /**
  @return Returns true if the puzzle is solvable, false otherwise.
  */
  bool isPuzzleSolvable();

  /**
  @post records the puzzle as being solvable.
  */
  void setSolvable();

  /**
   @return returns the 2D pointer array representing the puzzle
  */
  int** getPuzzleNumbers();

  /**
   @param a pointer to pointer that represents the puzzle
   @post sets the 2D pointer array representing the puzzle to the value of the parameter
  */
  void setPuzzleNumbers(int** puzzle);

  /**
   @return returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board.
  */
  Sudoku::Location returnNextEmpty();

  /**
   @param an integer and a given location in the 2D array.
   @return returns true if the value parameter can legally be placed at the given location in the 2D array without breaking the rules of sudoku. Returns false if placing value at location is not a legal move.
  */
  bool checkLegalValue(int value, Sudoku::Location location);

  /**
   @post displays the board
  */
  void display();

  /**
   * @param an integer and a given location in the 2D array.
   * @return returns true if the number is able to be placed in the given location. Returns false if it cannot.
   * @post inserts a number at a given location
  */
  bool insertNumber(int value, Sudoku::Location location);

  bool puzzleSolver(int value, Sudoku::Location location);

private:
//Add your private members here
  //Sudoku::Location location;
  bool solvable;
  int **board = new int*[9];

};

#endif