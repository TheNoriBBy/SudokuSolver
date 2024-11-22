#include "SudokuPuzzle.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

SudokuPuzzle::SudokuPuzzle() : debug(false) {
    for (auto& row : board) {
        std::fill(std::begin(row), std::end(row), 0);
    }
}

void SudokuPuzzle::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 9; ++i) {
        std::shuffle(numbers.begin(), numbers.end(), gen);
        for (int j = 0; j < 9; ++j) {
            if (canPlace(i, j, numbers[j])) {
                setBoardValue(i, j, numbers[j]);
            }
        }
    }

    solve();
}

bool SudokuPuzzle::canPlace(int x_cord, int y_cord, int value) {
    for (int i = 0; i < 9; i++) {
        if (board[i][y_cord] == value || board[x_cord][i] == value) {
            return false;
        }
    }

    int box_x = x_cord / 3;
    int box_y = y_cord / 3;
    for (int y_verify = box_y * 3; y_verify < box_y * 3 + 3; y_verify++) {
        for (int x_verify = box_x * 3; x_verify < box_x * 3 + 3; x_verify++) {
            if (board[x_verify][y_verify] == value) {
                return false;
            }
        }
    }

    return true;
}

void SudokuPuzzle::print() const {
    for (int y = 0; y < 9; y++) {
        if (y % 3 == 0) {
            std::cout << "-------------------------------" << std::endl;
        }

        for (int x = 0; x < 9; x++) {
            if (x % 3 == 0) {
                std::cout << "|";
            }
            std::cout << (board[x][y] != 0 ? " " + std::to_string(board[x][y]) + " " : " . ");
        }

        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void SudokuPuzzle::setBoardValue(int x_cord, int y_cord, int value) {
    board[x_cord][y_cord] = value;
}

int SudokuPuzzle::getBoardValue(int x_cord, int y_cord) const {
    return board[x_cord][y_cord];
}

bool SudokuPuzzle::solve() {
    return solve(0, 0);
}

bool SudokuPuzzle::solve(int x_cord, int y_cord) {
    if (board[x_cord][y_cord] != 0) {
        return proceedToNext(x_cord, y_cord);
    }

    for (int val = 1; val <= 9; val++) {
        setBoardValue(x_cord, y_cord, val);
        if (verifyValue(x_cord, y_cord) && proceedToNext(x_cord, y_cord)) {
            return true;
        }
    }

    board[x_cord][y_cord] = 0; // Reset the cell
    return false;
}

bool SudokuPuzzle::proceedToNext(int x_cord, int y_cord) {
    if (x_cord == 8 && y_cord == 8) {
        return true;
    }

    int next_x = (x_cord + 1) % 9;
    int next_y = (next_x == 0) ? y_cord + 1 : y_cord;

    return solve(next_x, next_y);
}

bool SudokuPuzzle::verifyValue(int x_cord, int y_cord) {
    printTracerTryingValue(x_cord, y_cord);
    int value = board[x_cord][y_cord];

    // Check row and column
    for (int i = 0; i < 9; i++) {
        if ((i != x_cord && board[i][y_cord] == value) ||
            (i != y_cord && board[x_cord][i] == value)) {
            return false;
        }
    }

    // Check 3x3 box
    int box_x = x_cord / 3;
    int box_y = y_cord / 3;
    for (int y_verify = box_y * 3; y_verify < box_y * 3 + 3; y_verify++) {
        for (int x_verify = box_x * 3; x_verify < box_x * 3 + 3; x_verify++) {
            if (x_verify != x_cord || y_verify != y_cord) {
                if (board[x_verify][y_verify] == value) {
                    return false;
                }
            }
        }
    }

    return true;
}

void SudokuPuzzle::printTracerTryingValue(int x_cord, int y_cord) {
    if (debug) {
        std::cout << std::string(x_cord + y_cord, ' ')
            << "Trying value " << board[x_cord][y_cord]
            << " at board[" << x_cord << "][" << y_cord << "]"
            << std::endl;
    }
}
