#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


#define SCREEN_HEIGHT 512
#define SCREEN_WIDTH 512
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8
#define NUM_WALLS 300
#define PI 3.14159265
#define CELL_SIZE 64



typedef struct {
    float x, y;
    float dx, dy;
    float angle;
} Player;

typedef struct {
    int x1, y1;  // Starting point of the wall
    int x2, y2;  // Ending point of the wall
} Wall;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event ev;
Player player = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0, 0.0f};


// Maze representation (dummy data)
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

const int numRays = 60;  // Number of rays to cast


void renderWalls(Wall* walls, int numWalls) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set the wall color (white)
    SDL_RenderClear(renderer);  // Clear the renderer

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set the background color (black)
    SDL_RenderFillRect(renderer, NULL);  // Fill the background

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set the wall color (white)

    Wall wall = walls[0];
    for (int i = 0; i < numWalls; i++) {

        SDL_RenderDrawLine(renderer, wall.x1+=5, wall.y1, wall.x2+=5, wall.y2);
    }

    SDL_RenderPresent(renderer);  // Update the screen
}



void drawGrid(SDL_Renderer* renderer) {
    // Set the color for grid lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw vertical grid lines
    for (int x = 0; x <= SCREEN_WIDTH; x += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
    }

    // Draw horizontal grid lines
    for (int y = 0; y <= SCREEN_HEIGHT; y += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
    }
}

void drawMaze(SDL_Renderer* renderer) {
    // Set the color for walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the maze
    for (int row = 0; row < MAZE_HEIGHT; row++) {
        for (int col = 0; col < MAZE_WIDTH; col++) {
            if (maze[row][col] == 1) {
                SDL_Rect wall = {
                    col * CELL_SIZE,
                    row * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };
                SDL_RenderFillRect(renderer, &wall);
            }
        }
    }
}


void drawRays(SDL_Renderer* renderer, Player* player) {
    // Set the color for rays
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the rays
    for (int i = 0; i < numRays; i++) {
        float angle = player->angle - PI/6 + i * PI/180;
        float x = player->x;
        float y = player->y;
        float dx = cos(angle);
        float dy = sin(angle);
        float distance = 0;
        bool hit = false;
        while (!hit && distance < 1000) {
            x += dx;
            y += dy;
            distance += 1;
            if (maze[(int)y/CELL_SIZE][(int)x/CELL_SIZE] == 1) {
                hit = true;
            }
        }
        SDL_RenderDrawLine(renderer, player->x, player->y, x, y);
    }
}


void drawPlayer(SDL_Renderer* renderer, Player* player) {
    // Set the color for the player
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the player
    SDL_RenderDrawLine(renderer, player->x, player->y, player->x + 10 * cos(player->angle), player->y + 10 * sin(player->angle));
}


void draw(SDL_Renderer* renderer, Player* player) {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Draw the grid
    drawGrid(renderer);

    // Draw the maze
    drawMaze(renderer);

    // Draw the rays
    drawRays(renderer, player);

    // Draw the player
    drawPlayer(renderer, player);

    // Update the screen
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    bool isRunning = true;

    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    while(isRunning)
    {
        
        while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_QUIT)
            {
                isRunning = false;
            } else if (ev.type == SDL_KEYDOWN)
            {
                // Handle player movement and rotation
                if (ev.key.keysym.sym == SDLK_LEFT)
                {
                    player.angle -= 0.1;
                    if(player.angle < 0) {player.angle += 2 * PI;}
                    player.dx = 5 * cos(player.angle);
                    player.dy = 5 * sin(player.angle);
                    drawPlayer(renderer, &player);
                }
                if (ev.key.keysym.sym == SDLK_RIGHT)
                {
                    player.angle += 0.1;
                    if(player.angle >= 2 * PI) player.angle -= 2 * PI;
                    player.dx = 5 * cos(player.angle);
                    player.dy = 5 * sin(player.angle);
                    drawPlayer(renderer, &player);
                }
                if (ev.key.keysym.sym == SDLK_DOWN)
                {
                    player.x -= player.dx;
                    player.y -= player.dy;
                    drawPlayer(renderer, &player);
                }
                if (ev.key.keysym.sym == SDLK_UP)
                {
                    player.x += player.dx;
                    player.y += player.dy;
                    drawPlayer(renderer, &player);
                }
                
            }
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderClear(renderer);

            draw(renderer, &player);
            
            SDL_RenderPresent(renderer);
        }
        
    }

   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
