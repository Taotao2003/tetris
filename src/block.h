#pragma once
#include <vector>
#include <map>
#include "common.h"

struct Position {
    int r; // y
    int c; // x
};

class Block {
private:
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;

public: 
    int BlockId;
    std::map<int, std::vector<Position>> pieces;
    Block(): rotationState(0), rowOffset(0), colOffset(0) {
        colors = getCellColors();
    }

    void Draw(int offsetX, int offsetY) {
        std::vector<Position> tiles = getTilePos();
        for (Position tile : tiles) {
            DrawRectangle(tile.c * cellSize+offsetX, tile.r * cellSize+offsetY, cellSize-1, cellSize-1, colors[BlockId]);
        }
    }

    void moveBlock(int row, int col) {
        rowOffset += row;
        colOffset += col;
    }

    std::vector<Position> getTilePos() {
        std::vector<Position> tiles = pieces[rotationState];
        std::vector<Position> movedTiles;
        for (Position tile : tiles) {
            Position newPos = Position{tile.r + rowOffset, tile.c + colOffset};
            movedTiles.push_back(newPos);
        }
        return movedTiles;
    }

    void rotateBlock() {
        ++rotationState;
        if (rotationState == (int)pieces.size())
            rotationState = 0;
    }

    void undoRotation() {
        --rotationState;
        if (rotationState < 0)
            rotationState = (int)pieces.size()-1;

    }


};

class LBlock: public Block {
public:
    LBlock() {
        BlockId = 1;
        pieces[0] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
        pieces[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
        pieces[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
        pieces[3] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};

class JBlock: public Block {
public:
    JBlock() {
        BlockId = 2;
        pieces[0] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        pieces[1] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
        pieces[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
        pieces[3] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
        moveBlock(0, 3);
    }
};

class IBlock: public Block {
public:
    IBlock() {
        BlockId = 3;
        pieces[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        pieces[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
        pieces[2] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
        pieces[3] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        moveBlock(-1, 3);
    }
};

class OBlock: public Block {
public:
    OBlock() {
        BlockId = 4;
        pieces[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        moveBlock(0, 4);
    }
};

class SBlock: public Block {
public:
    SBlock() {
        BlockId = 5;
        pieces[0] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        pieces[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
        pieces[2] = {{1, 1}, {1, 2}, {2, 0}, {2, 1}};
        pieces[3] = {{0, 0}, {1, 1}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};

class ZBlock: public Block {
public:
    ZBlock() {
        BlockId = 6;
        pieces[0] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        pieces[1] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
        pieces[2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
        pieces[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
        moveBlock(0, 3);
    }
};

class TBlock: public Block {
public:
    TBlock() {
        BlockId = 7;
        pieces[0] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
        pieces[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 1}};
        pieces[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
        pieces[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};


