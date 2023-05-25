/**
 * @file main.cpp
 * @author Jeffrey Oyuela
 * @brief main file used for testing. Some functions are commented out in order to test the parameterized constructor
 * @date 2023-04-21
 */

#include "SudokuSolver.hpp"
#include <iostream>

int main(){
    SudokuSolver board("puzzle1.csv");
    //board.display();
    //Sudoku::Location location;
    //location.row = 5;
    //location.col = 7;
    //std::cout << board.returnNextEmpty().col << " " << board.returnNextEmpty().row;
    //std::cout << board.getPuzzleNumbers()[location.row][location.col] << std::endl;
    //std::cout << board.checkLegalValue(10, location)<< std::endl;
    //board.puzzleSolver(1, board.returnNextEmpty());
    board.display();
    std::cout << board.isPuzzleSolvable();
}