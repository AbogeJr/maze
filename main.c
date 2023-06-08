#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8



float playerX = 3.0f;
float playerY = 3.0f;
float playerAngle = 0.0f;

// Maze representation (dummy data)
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

const int numRays = SCREEN_WIDTH;  // Number of rays to cast
const float FOV = 60.0f;


// Perform raycasting and rendering
void raycastAndRender(SDL_Renderer* renderer)
{
    for (int rayIndex = 0; rayIndex < numRays; ++rayIndex)
    {
        // Calculate ray angle
        float rayAngle = playerAngle - (FOV / 2) + (rayIndex * (FOV / numRays));

        // Perform raycasting calculations
        float rayX = playerX;
        float rayY = playerY;
        float rayDirectionX = sin(rayAngle);
        float rayDirectionY = cos(rayAngle);

        int hit = 0;
        while (!hit)
        {
            rayX += rayDirectionX;
            rayY += rayDirectionY;

            int gridX = (int)rayX;
            int gridY = (int)rayY;

            if (gridX < 0 || gridX >= MAZE_WIDTH || gridY < 0 || gridY >= MAZE_HEIGHT)
            {
                hit = 1;
                break;
            }

            if (maze[gridY][gridX] == 1)
            {
                hit = 1;

                // Calculate distance to wall
                float distanceToWall = sqrt((rayX - playerX) * (rayX - playerX) + (rayY - playerY) * (rayY - playerY));

                // Calculate wall height
                int wallHeight = (int)(SCREEN_HEIGHT / distanceToWall);

                // Calculate wall color based on distance
                int wallColor = 255 - (int)(255 * distanceToWall / (float)SCREEN_WIDTH);

                // Set wall color
                SDL_SetRenderDrawColor(renderer, wallColor, wallColor, wallColor, 255);

                // Render the wall column on the screen
                SDL_RenderDrawLine(renderer, rayIndex, (SCREEN_HEIGHT - wallHeight) / 2, rayIndex, (SCREEN_HEIGHT + wallHeight) / 2);

                break;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event ev;

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
                switch (ev.key.keysym.sym)
                {
                    case SDLK_UP:
                        // Move player forward
                        playerX += sin(playerAngle) * 0.1;
                        playerY += cos(playerAngle) * 0.1;
                        break;
                    case SDLK_DOWN:
                        // Move player backward
                        playerX -= sin(playerAngle) * 0.1;
                        playerY -= cos(playerAngle) * 0.1;
                        break;
                    case SDLK_LEFT:
                        // Rotate player left
                        playerAngle -= 0.1;
                        break;
                    case SDLK_RIGHT:
                        // Rotate player right
                        playerAngle += 0.1;
                        break;
                    default:
                        break;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
            SDL_RenderClear(renderer);

            // Perform raycasting and rendering
            raycastAndRender(renderer);

            // Update the screen
            SDL_RenderPresent(renderer);
        }
        
    }

   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
