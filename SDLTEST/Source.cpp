#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")


//screen size
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

bool keyup = 0;
bool keydown = 0;
bool keyright = 0;
bool keyleft = 0;
bool space = 0;

int main(int argc, char* argv[]) {

	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	
	
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	
	//Create window 
	window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	
	//Create render
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	
	bool quit = false;
	SDL_Event event;
	
	
	int size_x = 40;
	int size_y = 40;
	int pos_x = (SCREEN_WIDTH / 2) - (size_x / 2);
	int pos_y = (SCREEN_HEIGHT / 2) - (size_y / 2);
	SDL_Rect rectangle2;


	while (!quit) {
		
		
		//Clear screen with blue
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		
		//Draw rectangle
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_Rect rectangle = { pos_x, pos_y, size_x, size_y };
		SDL_RenderFillRect(renderer, &rectangle);


		while (SDL_PollEvent(&event) != 0) {
			
			
			//User requests quit
			if (event.type == SDL_QUIT) {
				
				quit = true;

			}
			//setting keyup
			
			if (event.type == SDL_KEYUP) {
				
				switch (event.key.keysym.sym) {
				
				case SDLK_UP:
					keyup = false;
					break;
				
				case SDLK_DOWN:
					keydown = false;
					break;
				
				case SDLK_LEFT:
					keyleft = false;
					break;
				
				case SDLK_RIGHT:
					keyright = false;
					break;
				
				case SDLK_SPACE:
					space = false;
					break;
				}
			}
			//setting keydown
			if (event.type == SDL_KEYDOWN) {
				
				switch (event.key.keysym.sym) {
				
				case SDLK_UP:
					keyup = true;
					break;
				
				case SDLK_DOWN:
					keydown = true;
					break;
				
				case SDLK_LEFT:
					keyleft = true;
					break;
				
				case SDLK_RIGHT:
					keyright = true;
					break;
				
				case SDLK_SPACE:
					space = true;
					break;
				}
			}
		}
		//setting movement
		if (keyup && (rectangle.y >= 0)) { pos_y -= 1; }

		if (keydown && (rectangle.y <= SCREEN_HEIGHT - size_y)) { pos_y += 1; }

		if (keyright && (rectangle.x <= SCREEN_WIDTH - size_x)) { pos_x += 1; }

		if (keyleft && (rectangle.x >= 0)) { pos_x -= 1; }

		if (space) {rectangle2 = { pos_x + size_x, pos_y + (size_y / 2) - 4, 20, 10 };}

		rectangle2.x +=2;
		if (rectangle2.x <= SCREEN_WIDTH) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rectangle2);
		}
		
		SDL_Delay(1);
		
		//Show what was drawn
		SDL_RenderPresent(renderer);
	}
	
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0; 
}