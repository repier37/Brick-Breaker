//============================================================================
// Name        : qsdfqs.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
using namespace std;

int main() {

	const int SCREEN_WIDTH = 1204;
	const int SCREEN_HEIGHT = 768;


	// SDL initialisation
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		cout << "SDL initialisé correctement" << endl;
	} else {
		cout << SDL_GetError() << endl;
	}

	string gameName = "Brick Breaker";
	const char* windowName = gameName.c_str();

	SDL_Window* window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (window == NULL) {
		cout << "could not create the window" << endl;
		cout << SDL_GetError() << endl;
		return 1;
	}

	SDL_Event event;

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

	bool quit = 0;
	// game loop
	while (!quit) {

		//clear screen
		SDL_RenderClear (renderer);





		//update screen
		SDL_RenderPresent(renderer);

		//event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT :
				quit = true;
				break;
			default:
				break;
			}
		}

	}

	// SDL destruction
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
