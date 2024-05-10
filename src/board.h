#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>

#include "common.h"


class Board {
private:
    int numRow;
    int numCol;
    std::vector<Color> colors;

public: 
    int** board;
    Board(): numRow(20), numCol(10), board(new int*[numRow]) {
        colors = getCellColors();
        for (int r = 0; r < numRow; ++r) {
            board[r] = new int[numCol];
        }  
    }

    ~Board() {
        for (int r = 0; r < numRow; ++r)
            delete[] board[r];
        delete[] board;
    }

    void initializeBoard() {
        for (int r = 0; r < numRow; ++r) {
            for (int c = 0; c < numCol; ++c)
                board[r][c] = 0;
        }
    }

    void Draw() {
        for (int r = 0; r < numRow; ++r) {
            for (int c = 0; c < numCol; ++c) {
                int cellVal = board[r][c];
                DrawRectangle(c * cellSize+11, r * cellSize+11, cellSize-1, cellSize-1, colors[cellVal]);
            }
        }
    }

    bool isTileOutside(int row, int col) {
        return (row < 0 || row >= numRow || col < 0 || col >= numCol);
    }

    bool isCellEmpty(int r, int c) {
        return board[r][c] == 0;
    }

    // check the row is all filled up or not. 
    bool isRowCompleted(int row) {
        for (int c = 0; c < numCol; ++c) {
            if (board[row][c] == 0)
                return false;
        }
        return true;
    }

    void clearRow(int row) {
        for (int c = 0; c < numCol; ++c) 
            board[row][c] = 0;
    }

    void moveRowDown(int row, int rowCompleted) {
        for (int c = 0; c < numCol; ++c) {
            board[row + rowCompleted][c] = board[row][c];
            board[row][c] = 0;
        }
    }
    
    int clearFullRow() {
        int completedRows = 0;
        for (int r = numRow-1; r >= 0; --r) {
            if (isRowCompleted(r)) {
                clearRow(r);
                ++completedRows;
            } else if (completedRows > 0) {
                moveRowDown(r, completedRows);
            }
        }
        return completedRows;
    }


};

    // void Print() {
    //     for (int r = 0; r < numRow; ++r) {
    //         for (int c = 0; c < numCol; ++c)
    //             std::cout << board[r][c] << " ";
    //         std::cout << std::endl;
    //     }
    // }