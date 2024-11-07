#include "Maze.h"
Maze::Maze() {}
void Maze::draw(SDL_Renderer* renderer) {
    SDL_Rect cellRect;
    cellRect.w = CELL_SIZE;    cellRect.h = CELL_SIZE;
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            cellRect.x = col * CELL_SIZE;
            cellRect.y = row * CELL_SIZE;
            if (maze[row][col] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }
            else if (maze[row][col] == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }            SDL_RenderFillRect(renderer, &cellRect);
        }
    }
}
bool Maze::checkCollision(SDL_Rect playerRect) {
    int left = playerRect.x;
    int right = playerRect.x + playerRect.w - 1;    int top = playerRect.y;
    int bottom = playerRect.y + playerRect.h - 1;
    int gridX1 = left / CELL_SIZE;
    int gridY1 = top / CELL_SIZE;    int gridX2 = right / CELL_SIZE;
    int gridY2 = top / CELL_SIZE;    int gridX3 = left / CELL_SIZE;
    int gridY3 = bottom / CELL_SIZE;    int gridX4 = right / CELL_SIZE;
    int gridY4 = bottom / CELL_SIZE;
    if (gridX1 < 0 || gridX1 >= 10 || gridY1 < 0 || gridY1 >= 10 ||
        gridX2 < 0 || gridX2 >= 10 || gridY2 < 0 || gridY2 >= 10 || gridX3 < 0 || gridX3 >= 10 || gridY3 < 0 || gridY3 >= 10 ||
        gridX4 < 0 || gridX4 >= 10 || gridY4 < 0 || gridY4 >= 10) {
        return true;
    }
    if (maze[gridY1][gridX1] == 1 || maze[gridY2][gridX2] == 1 ||
        maze[gridY3][gridX3] == 1 || maze[gridY4][gridX4] == 1) {
        return true;
    }
    return false;
}

bool Maze::reachedExit(SDL_Rect playerRect) {
    int right = playerRect.x + playerRect.w - 1;    int bottom = playerRect.y + playerRect.h - 1;

    int gridX = right / CELL_SIZE;
    int gridY = bottom / CELL_SIZE;
    return maze[gridY][gridX] == 2;
}