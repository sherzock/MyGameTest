#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL2_mixer/include/SDL_mixer.h"
#include <string>

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer/libx86/SDL2_mixer.lib")

//Screen dimension constants
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 480;

bool Initialize();
void Close();
SDL_Texture* LoadTexture(std::string file);

struct Bullet {
	bool shooting;
	SDL_Rect bullet;
};

//The window we'll be rendering to
SDL_Window* window = nullptr;

//The window renderer
SDL_Renderer* renderer = nullptr;

//Current displayed texture
SDL_Texture* background = nullptr;
SDL_Texture* ship = nullptr;
SDL_Texture* shoot = nullptr;

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *shot = NULL;


int main(int argc, char* argv[]) {

	if (Initialize()) {

		//Load music
		music = Mix_LoadMUS("Game/music.ogg");
		//Load sound effects
		shot = Mix_LoadWAV("Game/shot.wav");

		//textures
		background = LoadTexture("background.png");
		ship = LoadTexture("spaceship.png");
		shoot = LoadTexture("laser.png");

		if (background == nullptr || ship == nullptr || shoot == nullptr) {
			return -1;
		}

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Create Key Input
		bool movement_key[5] = { 0,0,0,0,0 };

		enum key { UP, LEFT, DOWN, RIGHT, SPACE };

		//Create bullet
		struct Bullet bullet[10];

		for (int i = 0; i < 10; ++i) {
			bullet[i].shooting = false;
		}

		Uint32 shooting_delay = 0;

		//Create Rect
		SDL_Rect rect;
		rect.x = SCREEN_WIDTH / 2;
		rect.y = SCREEN_HEIGHT / 2;
		rect.w = 50;
		rect.h = 50;


		int FPS = 50;
		
		Mix_PlayMusic(music, -1);

		//While application is running
		while (!quit)
		{
			Uint32 start_time = SDL_GetTicks();

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_w:
						movement_key[UP] = 1;
						break;
					case SDLK_a:
						movement_key[LEFT] = 1;
						break;
					case SDLK_s:
						movement_key[DOWN] = 1;
						break;
					case SDLK_d:
						movement_key[RIGHT] = 1;
						break;
					case SDLK_SPACE:
						movement_key[SPACE] = 1;
						break;
					}
					break;
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
					case SDLK_w:
						movement_key[UP] = 0;
						break;
					case SDLK_a:
						movement_key[LEFT] = 0;
						break;
					case SDLK_s:
						movement_key[DOWN] = 0;
						break;
					case SDLK_d:
						movement_key[RIGHT] = 0;
						break;
					case SDLK_SPACE:
						movement_key[SPACE] = 0;
						break;
					}
					break;
				}
			}

			//Rectangle Movement
			if (movement_key[UP] && rect.y > 0) {
				rect.y--;
			}
			if (movement_key[DOWN] && rect.y < SCREEN_HEIGHT - rect.h) {
				rect.y++;
			}
			if (movement_key[LEFT] && rect.x > 0) {
				rect.x--;
			}
			if (movement_key[RIGHT] && rect.x < SCREEN_WIDTH - rect.w) {
				rect.x++;
			}

			if (movement_key[SPACE]) {
				Mix_PlayChannel(2, shot, 0);
				if (start_time - shooting_delay > 250) {
					for (int i = 0; i < 10 && (start_time - shooting_delay > 250); ++i) {
						if (!bullet[i].shooting) {
							
							shooting_delay = start_time;
							bullet[i].bullet.w = 76;
							bullet[i].bullet.h = 40;
							bullet[i].bullet.x = rect.x + rect.w;
							bullet[i].bullet.y = rect.y + rect.h / 2 - bullet[i].bullet.h / 2; ;
							bullet[i].shooting = true;
						}
					}
				}
			}

			//Clear screen
			SDL_RenderClear(renderer);

			//Render texture to screen
			SDL_RenderCopy(renderer, background, NULL, NULL);

			SDL_RenderCopyEx(renderer, ship, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

			for (int i = 0; i < 10; ++i) {
				if (bullet[i].shooting && bullet[i].bullet.x < SCREEN_WIDTH) {
					bullet[i].bullet.x += 3;
					SDL_RenderCopyEx(renderer, shoot, NULL, &bullet[i].bullet, 360, NULL, SDL_FLIP_NONE);
				}
				else {
					bullet[i].shooting = false;
				}
			}

			//Update screen
			SDL_RenderPresent(renderer);

			//delay
			SDL_Delay(1);
		}
	}
	Close();
	return 0;
}

bool Initialize() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		return false;
	}
	else {
		//Create window
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			return false;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			return false;
		}

		//Initialize SDL_mixer
		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			return false;

		return true;
	}
}

void Close() {

	//Free the sound effects
	Mix_FreeChunk(shot);
	shot = NULL;

	//Free the music
	Mix_FreeMusic(music);
	music = NULL;

	SDL_DestroyWindow(window);
	window = nullptr;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* LoadTexture(std::string file) {
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface != nullptr) {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}