#ifndef _SUDOKU_PUZZLE_H
#define _SUDOKU_PUZZLE_H

class SudokuPuzzle {
private:
    bool debug;

    void printTracerTryingValue(int x_cord, int y_cord);
    bool solve(int x_cord, int y_cord);
    bool proceedToNext(int x_cord, int y_cord);
    bool verifyValue(int x_cord, int y_cord);
    bool canPlace(int x_cord, int y_cord, int value);

public:
    short int board[9][9];
    SudokuPuzzle();
    void print() const;
    void setBoardValue(int x_cord, int y_cord, int value);
    int getBoardValue(int x_cord, int y_cord) const;
    bool solve();
    bool generate(int x, int y);
    void removeNumbers(int count);
};

#endif
