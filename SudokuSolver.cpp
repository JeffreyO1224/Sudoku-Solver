/**
 * @file SudokuSolver.cpp
 * @author Jeffrey Oyuela
 * @brief This program aims to solve any given sudoku puzzle if possible. It will utilize recursive backtracking.
 * @date 2023-04-21
 * 
 */

#include "SudokuSolver.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

  /**
   @post Default Constructor that makes an empty 9x9 sudoku board
  */
SudokuSolver::SudokuSolver(){
    //Assign arrays to each pointer in the board array. This will set up the 2D Pointer Array as board[row][column]
    for (int i = 0; i < 9; i++){
        board[i] = new int[9];

        //For the array that was just assigned, fill every element with 0's, indicating an empty board
        for(int j = 0; j < 9; j++){
            board[i][j] = 0;
        }//End Nested For Loop
    }//End For Loop

    //Default to unsolvable
    solvable = false;
}//End Constructor

  /**
   @param CSV file with integers for each element in the board
   @post Initializes the board based on what is read from the input_file
  */
SudokuSolver::SudokuSolver(std::string input_file){
    //Initialize ifstream file to read from the given CSV file
    std::ifstream fin(input_file);
    std::string temp_string;

    //Assign arrays to each pointer in the board array, setting up a 2D Array
    for(int i = 0; i < 9; i++){
        board[i] = new int[9];
        
        //For each element (col) in each array (row), read from the CSV file and assign values for each index.
        for(int j = 0; j < 9; j++){
            
            //If we're not on the last column, keep separating by ','. Otherwise, just read the last number
            if(j != 8){
                getline(fin, temp_string, ',');}
            else{
                getline(fin, temp_string);
            } 

            //Convert the substring extracted from the CSV into an int type and assign it to its respective place on the board.
            std::istringstream(temp_string) >> board[i][j];
        }
    }

    //Solve the puzzle. It will mark the board as solvable if it is. Will mark it unsolvable otherwise.
    puzzleSolver(1, returnNextEmpty());
}//End Parameterized Constructor

  /**
  @return Returns true if the puzzle is solvable, false otherwise.
  */
  bool SudokuSolver::isPuzzleSolvable(){
    return solvable;
  }

  /**
  @post records the puzzle as being solvable.
  */
  void SudokuSolver::setSolvable(){
    solvable = true;
  }

  /**
   @return returns the 2D pointer array representing the puzzle
  */
  int** SudokuSolver::getPuzzleNumbers(){
    return board;
  }

  /**
   @param a pointer to pointer that represents the puzzle
   @post sets the 2D pointer array representing the puzzle to the value of the parameter
  */
  void SudokuSolver::setPuzzleNumbers(int** puzzle){
    board = puzzle;
  }

  /**
   @return returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. If there is no empty space, return location with col and row values of -1
  */
  Sudoku::Location SudokuSolver::returnNextEmpty(){
    //Initialize return Sudoku::Location type
    Sudoku::Location location;

    //Go through each column (j) of each row (i). The first index with a 0 in it will provide the location's row (i) and col (j) values.
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if (board[i][j] == 0){
                location.row = i;
                location.col = j;
                return location;
            }
        }
    }

    //If there are no empty spaces left, return a Sudoku::Location type with its row and col values being -1
    location.row = -1;
    location.col = -1;
    return location;
  }//End returnNextEmpty()

  /**
   @pre value is an integer 1-9 and location's coordinates is empty
   @param an integer and a given location in the 2D array.
   @return returns true if the value parameter can legally be placed at the given location in the 2D array without breaking the rules of sudoku. Returns false if placing value at location is not a legal move.
  */
  bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){

    //Go through each COLUMN in location's ROW i.e. (2,0), (2,1), (2,2)...
    for(int j = 0; j < 9; j++){

        //if(location.col == j){}
        //If the current empty space carries the same integer given with "value," return false
        if(board[location.row][j] == value){
            return false;
        }//End If
    }//End For Loop

    //Go through each ROW in location's COLUMN i.e. (0,2), (1,2), (2,2)...
    for(int i = 0; i < 9; i++){

        //if(location.row == i){}
        //If the current empty space carries the same integer given with "value," return false
        if(board[i][location.col] == value){
            return false;
        }//End If
    }//End Else

    //Go through the location's subgrid. 
    //3*(location.row/3) and 3*(location.col/3) will ALWAYS provide the first index of each row and column in the subgrid respectively. i.e. We are dealing with the fourth subgrid (the middle), then 3*(location.row/3) = 3 and 3*(location.col/3) = 3
    //3+(3*(location.row/3)) 3+(3*(location.col/3)) will ALWAYS provide the last index of each row and column in the subgrid respectively. i.e. We are dealing with the fourth subgrid (the middle), then 3+(3*(location.row/3)) = 6 and 3+(3*(location.col/3)) = 6
    //As a side note, I'm really proud of myself for coming up with that :)
    for(int i = 3*(location.row/3); i < 3+(3*(location.row/3)); i++){
        for(int j = 3*(location.col/3); j < 3+(3*(location.col/3)); j++){

            //if(location.row == i && location.col == j){}

            //If a space in the subgrid already contains the integer given by "value," then return false
            if(board[i][j] == value){
                return false;
            }//End If
        }//End Nested For Loop
    }//End For Loop
    

    //If all checks are passed, then this is a legal space.
    return true;
  }//End checkLegalValue()


/**
 @post displays the sudoku board
*/
void SudokuSolver::display(){
    //Go through each row
    for(int i = 0; i < 9; i++){

        //If three rows have passed, print the dashed border
        if (i%3 == 0 && i != 0){
            for(int k = 0; k < 12; k++){
                std::cout << "- ";

            }//End Nested For Loop

            //New line
            std::cout << std::endl;

        }//End If

        //Go through each column
        for(int j = 0; j < 9; j++){

            //If three columns have passed, print a border
            if (j%3 == 0 && j != 0){
                std::cout << " | ";
            }//end if

            //If the square is empty, display it as an X
            if (board[i][j] == 0){
                std::cout << "X ";
            }//end if

            //Otherwise, print the actual number
            else{
                std::cout << board[i][j] << " ";
            }//end else
        }//End for
        
        //New line
        std::cout << std::endl;
    }//End Main For Loop
}//End display()

  /**
   * @param an integer and a given location in the 2D array.
   * @return returns true if the number is able to be placed in the given location. Returns false if it cannot.
   * @post inserts a number at a given location
  */
bool SudokuSolver::insertNumber(int value, Sudoku::Location location){
    //If placing value at location is a legal move, then insert the number at that location and return true
    if(checkLegalValue(value, location)){
        board[location.row][location.col] = value;
        return true;
    }

    //If it's illegal, return false
    return false;
}//End insertNumber()

  /**
   * @brief this is a function that recursively backtracks to find the first possible solution of the sudoku puzzle.
   * @param an integer and a given location in the 2D array.
   * @post finds the first possible solution of the sudoku puzzle. Marks the puzzle as solvable if a solution exists; marks false otherwise.
   */
bool SudokuSolver::puzzleSolver(int value, Sudoku::Location location){

    //Base Case. location.row implies there are no more empty spaces on the board, meaning that the board is solved.
    //Marks the board as solvable if no more empty spaces exist. Basically ends the recursion.
    if (location.row == -1){
        setSolvable();
        return true;
    }//End if

    //Try every possible integer for the given location
    for(int i = 1; i <= 9; i++){
        
        //If the number can be inserted at the given location...
        if(insertNumber(i, location)){

            //Continue the recursion until an end is reached.
            //When the base case is reached, it will return to the very beginning and return true, ending the recursion.
            if(puzzleSolver(1, returnNextEmpty())){
                return true;
            }//End Nested If

            //If a dead end is reached, retract the previous insertion.
            else{
                board[location.row][location.col] = 0;
            }//End Else
        }//End If
    }//End For Loop

    //Indicates a dead end that makes the program backtrack to the previous function instance
    return false;
}//End puzzleSolver   