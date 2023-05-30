#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * win = SDL_CreateWindow("Aboge Window", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Surface * screen = SDL_GetWindowSurface(win);

	int run = 1;

	while(run)
	{
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					run = 0;
					break;
			}
		}
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
}
