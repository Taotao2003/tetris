#pragma once
#include <vector>
#include "block.h"
#include <random>
#include "board.h"
#include <iostream>
#include <time.h>

using namespace std;
class Game {
private:
    std::vector<Block> blocks;
    Block currBlock;
    Block nextBlock;
    Block holdBlock;
    double gravity;
    double prevTime = 0;
    
    

public:
    int score;
    Board board = Board();
    bool gameOver = false;
    Game() {
        gravity = .5;
        blocks = {IBlock(), JBlock(), ZBlock(), SBlock(), OBlock(), TBlock(), LBlock()};
        currBlock = getRandomBlock();
        nextBlock = getRandomBlock();
        srand(time(NULL));
        score = 0;
    }

    Block getRandomBlock() {
        srand(time(NULL));
        if (blocks.empty()) 
            blocks = getAllBlocks();
        
        int randIdx = rand() % blocks.size();
        Block block = blocks[randIdx];
        blocks.erase(blocks.begin() + randIdx);
        return block;
    }

    std::vector<Block> getAllBlocks() {
        return {IBlock(), JBlock(), ZBlock(), SBlock(), OBlock(), TBlock(), LBlock()};
    }

    void Draw() {
        board.Draw();
        currBlock.Draw(11, 11);
        nextBlock.Draw(360, 390);
    }

    void getInput() {
        int keyPressed = GetKeyPressed();

        if (keyPressed == KEY_LEFT) {
            currBlock.moveBlock(0, -1);
            if (isBlockOutside() || !blockFits())
                currBlock.moveBlock(0, 1);
        }
        if (keyPressed == KEY_RIGHT) {
            currBlock.moveBlock(0, 1);
            if (isBlockOutside() || !blockFits())
                currBlock.moveBlock(0, -1);
        }
        if (keyPressed == KEY_DOWN) {
            currBlock.moveBlock(1, 0);
            updateScore(0, 1);
            if (isBlockOutside() || !blockFits()) {
                currBlock.moveBlock(-1, 0);
                lockBlock();
            }  
        }
        if (keyPressed == KEY_UP) {
            currBlock.rotateBlock();
            if (isBlockOutside() || !blockFits()) {
                currBlock.undoRotation();
            }
        }
        if (keyPressed == KEY_Z) {
            currBlock.undoRotation();
            if (isBlockOutside() || !blockFits()) {
                currBlock.rotateBlock();
            }
        }
        if (keyPressed == KEY_SPACE) {
            if (!(isBlockOutside() || !blockFits())) {
                hardDrop();
            }
        }
        // resetting the board
        if (gameOver && keyPressed == KEY_ENTER) {
            gameOver = false;
            board.initializeBoard();
            blocks = getAllBlocks();
            currBlock = getRandomBlock();
            nextBlock = getRandomBlock();
            score = 0;
        }

    }

    void hardDrop() {
        int maxDrop = 20; // rowSize = 20
        vector<Position> tiles = currBlock.getTilePos();
        for (Position tile : tiles) {
            int dropDistance = 0;
            while (!board.isTileOutside(tile.r + dropDistance + 1, tile.c) && board.isCellEmpty(tile.r + dropDistance + 1, tile.c)) {
                ++dropDistance;
            }
            maxDrop = min(maxDrop, dropDistance); 
        }
        currBlock.moveBlock(maxDrop, 0);
        updateScore(0, 2);
        lockBlock();

    }

    // checks if the block is outside the board
    bool isBlockOutside() {
        std::vector<Position> tiles = currBlock.getTilePos();
        for (Position tile : tiles) {
            if (board.isTileOutside(tile.r, tile.c))
                return true;
        }
        return false;
    }

    void Gravity() {
        if (gravitySpeed()) {
            currBlock.moveBlock(1, 0);
            if (isBlockOutside() || !blockFits()) {
                currBlock.moveBlock(-1, 0);
                lockBlock();
            }
                
        }
    }
    bool gravitySpeed() {
        double currTime = GetTime();
        if (currTime - prevTime >= gravity) {
            prevTime = currTime;
            return true;
        } return false;
    }
    
    void lockBlock() {
        std::vector<Position> tiles = currBlock.getTilePos();
        // locking the block by changing the grid's color
        for (Position tile: tiles) 
            board.board[tile.r][tile.c] = currBlock.BlockId;
        // get the next block
        currBlock = nextBlock;
        // game over condition if the block does not fit anywhere on the board
        if (!blockFits()) {
            gameOver = true;
        } else { 
            nextBlock = getRandomBlock();
        }

        int n = board.clearFullRow();
        updateScore(n, 0);
    }

    bool blockFits() {
        // check if there exists one tile that obstructs the block, return false
        std::vector<Position> tiles = currBlock.getTilePos();
        for (Position tile: tiles) {
            if (!board.isCellEmpty(tile.r, tile.c)) {
                return false;
            }
        }
        return true;    
    }

    void updateScore(int linesCleared, int moveDownPoints) {
        if (linesCleared == 1) 
            score += 100;
        else if (linesCleared == 2) 
            score += 300;
        else if (linesCleared >= 3) 
            score += 500;
        score += moveDownPoints;
        // cout << "score: " << score << endl;
        
    }

};
