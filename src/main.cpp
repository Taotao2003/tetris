#include <raylib.h>
#include "game.h"
#include <iostream>


const int boardWidth = 400+300;
const int boardHeight = 800+20;


int main() {    
    Game game = Game();
    InitWindow(boardWidth, boardHeight, "TETRIS");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        game.getInput();
        BeginDrawing();
        DrawRectangle(0, 0, boardWidth, boardHeight, BLACK);
        DrawText("Score:", 460, 50, 50, WHITE);
        DrawRectangleRounded({460, 120, 165, 80}, .3, 6, WHITE);
        DrawText("Next", 460, 250, 50, WHITE);
        DrawRectangleRounded({430, 300, 250 , 250}, .3, 6, WHITE);
        
        char scoreText[10];
        sprintf(scoreText, "%i", game.score);
        int textSize = MeasureText(scoreText, 50); 
        DrawText(scoreText, 460 + (165 - textSize)/2, 140 , 50, BLACK);


        game.Draw();  
        game.Gravity();  
        if (game.gameOver) {
            DrawRectangle(0, 0, boardWidth, boardHeight, RED);
            DrawText("GAME OVER", 145 , 300 , 75, WHITE);
            DrawText("Final Score:", 75, 400, 50, WHITE);
            DrawText(scoreText, 400, 400, 50, WHITE);  
            DrawText("Press [ENTER] to play again", 75, 475, 35, WHITE);
        }
        
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}