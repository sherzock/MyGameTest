#include "SDL/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")



static const int width = 800;
static const int height = 600;

int main(int argc, char **argv)
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("SDL2TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	
	bool running = true;
	SDL_Event event;
	while (running)
	{
		// Process events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		for (int i = 0; i < 400; i++) {
			// Clear screen with blue
			SDL_SetRenderDrawColor(renderer, 0, 125, 255, 255);
			SDL_RenderClear(renderer);

			// Draw
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_Rect rect = { 50+i, 50+i, 200, 200 };
			SDL_RenderFillRect(renderer, &rect);
		
		

		// Show what was drawn
			SDL_RenderPresent(renderer);

		}
				
		
	}

	// Release resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}