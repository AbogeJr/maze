#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * win = SDL_CreateWindow("Aboge Window", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Surface * screen = SDL_GetWindowSurface(win);
	SDL_Delay(5000);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
