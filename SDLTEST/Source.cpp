#include "SDL/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")



const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

bool key_up = NULL;
bool key_down = NULL;
bool key_right = NULL;
bool key_left = NULL;
bool key_space = NULL;

int main(int argc, char* argv[]) {

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Create window  "Name at the top", x position, y position, windows width, windows height, SDL_WINDOW_SHOWN makes sure the window is shown when it is created
	window = SDL_CreateWindow("Projecte 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create render
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	bool quit = false;
	SDL_Event close;

	int size_x = 100;
	int size_y = 100;
	int pos_x = (SCREEN_WIDTH / 2) - (size_x / 2);
	int pos_y = (SCREEN_HEIGHT / 2) - (size_y / 2);
	SDL_Rect rect2;

	while (!quit) {
		while (SDL_PollEvent(&close) != 0) {
			//User requests quit
			if (close.type == SDL_QUIT) {
				quit = true;
			}
			if (close.type == SDL_KEYUP) {
				switch (close.key.keysym.sym) {
				case SDLK_UP:
					key_up = false;
					break;

				case SDLK_DOWN:
					key_down = false;
					break;

				case SDLK_LEFT:
					key_left = false;
					break;

				case SDLK_RIGHT:
					key_right = false;
					break;

				case SDLK_SPACE:
					key_space = false;
					break;
				}
			}

			if (close.type == SDL_KEYDOWN) {
				switch (close.key.keysym.sym) {
				case SDLK_UP:
					key_up = true;
					break;

				case SDLK_DOWN:
					key_down = true;
					break;

				case SDLK_LEFT:
					key_left = true;
					break;

				case SDLK_RIGHT:
					key_right = true;
					break;

				case SDLK_SPACE:
					key_space = true;
					break;
				}
			}

			if (key_up) { pos_y -= 5; }

			if (key_down) { pos_y += 5; }

			if (key_right) { pos_x += 5; }

			if (key_left) { pos_x -= 5; }

			if (key_space) {
				rect2 = { pos_x + size_x, pos_y + (size_y / 2), 50, 10 };
			}

			if (pos_x >= SCREEN_WIDTH - size_x) {
				pos_x = SCREEN_WIDTH - size_x;
			}

			if (pos_x <= 0) {
				pos_x = 0;
			}

			if (pos_y >= SCREEN_HEIGHT - size_y) {
				pos_y = SCREEN_HEIGHT - size_y;
			}

			if (pos_y <= 0) {
				pos_y = 0;
			}
		}


		//Clear screen with blue
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Draw
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_Rect rect = { pos_x, pos_y, size_x, size_y };
		SDL_RenderFillRect(renderer, &rect);

		rect2.x += 2;
		if (rect2.x <= SCREEN_WIDTH) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rect2);
			SDL_Delay(1);
		}

		//Show what was drawn
		SDL_RenderPresent(renderer);
	}

	/*
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	*/

	return 0;
}