#include "SDL2/SDL.h"

int main(int argc, char *argv[]){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int quit = 0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

    while (!quit){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_UP:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderDrawPoint(renderer, 320, 240);
                        break;
                    case SDLK_DOWN:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_RenderDrawPoint(renderer, 320, 240);
                        break;
                    case SDLK_LEFT:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        SDL_RenderDrawPoint(renderer, 320, 240);
                        break;
                    case SDLK_RIGHT:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderDrawPoint(renderer, 320, 240);
                        break;
                }
                break;

        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}