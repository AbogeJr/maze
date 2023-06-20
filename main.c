#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8
#define NUM_WALLS 300
#define PI 3.14159265



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
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

const int numRays = SCREEN_WIDTH;  // Number of rays to cast
const float FOV = 60.0f;


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

void renderPlayer(Player* player) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set the player color (white)

    SDL_RenderDrawLine(renderer, player->x, player->y, player->x + 10 * cos(player->angle), player->y + 10 * sin(player->angle));
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
                if (ev.key.keysym.sym == SDLK_UP)
                {
                    player.angle -= 0.1;
                    if(player.angle < 0) {player.angle += 2 * PI;}
                    player.dx = 5 * cos(player.angle);
                    player.dy = 5 * sin(player.angle);
                    renderPlayer(&player);
                }
                if (ev.key.keysym.sym == SDLK_DOWN)
                {
                    player.angle += 0.1;
                    if(player.angle >= 2 * PI) player.angle -= 2 * PI;
                    player.dx = 5 * cos(player.angle);
                    player.dy = 5 * sin(player.angle);
                    renderPlayer(&player);
                }
                if (ev.key.keysym.sym == SDLK_RIGHT)
                {
                    player.x -= player.dx;
                    player.y -= player.dy;
                    renderPlayer(&player);
                }
                if (ev.key.keysym.sym == SDLK_LEFT)
                {
                    player.x += player.dx;
                    player.y += player.dy;
                    renderPlayer(&player);
                }
                
            }
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderClear(renderer);
             // Create your walls
            // Wall walls[NUM_WALLS] = {
            //     {100, 100, 100, 300},
            //     {101, 100, 101, 300},
            //     {102, 100, 102, 300},
            //     {103, 100, 103, 300},
            //     {104, 100, 104, 300},
            //     {105, 100, 106, 300},
               
            // };
            renderPlayer(&player);
            // Render the walls
            // renderWalls(walls, NUM_WALLS);
            // Update the screen
            SDL_RenderPresent(renderer);
        }
        
    }

   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
