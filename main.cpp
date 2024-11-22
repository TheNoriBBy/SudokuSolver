#include <iostream>
#include "SudokuPuzzle.h"

int main(int argc, char* const argv[]) {
    SudokuPuzzle puzzle;

    puzzle.generate(); 
    puzzle.print(); 

    std::cout << std::endl;

    if (puzzle.solve()) {
        std::cout << "Here is the solution:" << std::endl;
        puzzle.print();
    }
    else {
        std::cout << "Puzzle is not solvable.";
    }

    std::cout << std::endl;

    return 0;
}
