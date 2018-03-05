#include "SDL/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")



static const int width = 800;
static const int height = 600;

void bullet(SDL_Renderer *renderer, int x0, int y0) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect reco = { x0, y0, 50, 20 };
	SDL_RenderFillRect(renderer, &reco);
}

int main(int argc, char **argv)
{
	//position init
	int x = 288;
	int y = 208;

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("SDL2TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	bool quit = false;
	SDL_Event close;

	while (!quit) {
		/*while (SDL_PollEvent(&close)!= 0) {
			if (close.type == SDL_QUIT) {
				quit = true;
			}*/
		SDL_WaitEvent(&close);



		// Clear screen with blue
		SDL_SetRenderDrawColor(renderer, 100, 120, 10, 255);
		SDL_RenderClear(renderer);

		// Draw
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect rect = { x, y, 200, 200 };
		SDL_RenderFillRect(renderer, &rect);



		switch (close.type)
		{
		case SDL_QUIT:
			quit = true;
			break;


		case SDL_KEYDOWN:
			switch (close.key.keysym.sym) {
			case SDLK_UP:
				y = y - 10 ;
				break;
			case SDLK_DOWN:
				y = y + 10;
				break;
			case SDLK_LEFT:
				x = x - 10;
				break;
			case SDLK_RIGHT:
				x = x + 10;
				break;
			case SDLK_KP_SPACE:
				bullet(renderer,x,y);
				break;
			}
		}

		// Show what was drawn
		SDL_RenderPresent(renderer);


		//delay
		SDL_Delay(1);


	}


	// Release resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
