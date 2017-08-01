//============================================================================
// Name        : Brick Breaker.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include "Ball.h"
using namespace std;
using namespace pierre;

int main(int argc, char **argv) {
	Screen mainScreen;

	mainScreen.init();

	SDL_Event event;

	//initialisation of game objects

	Ball ball(mainScreen.m_renderer);
	int time;

	bool quit = 0;
	// game loop
	while (!quit) {
		time = SDL_GetTicks();
		SDL_RenderClear(mainScreen.m_renderer);

		// update ball;
		ball.update();
		// update screen
		//mainScreen.update();

		// update brick

		// update bar

		//draw everything on the screen
		ball.drawBall(mainScreen.m_renderer);
		//event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT :
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				//ball.update(event.motion.x, event.motion.y);
			default:
				break;
			}
		}
		SDL_RenderPresent(mainScreen.m_renderer);

	}

	// End of programm
	//sdl destructor
	mainScreen.close();
	//ball destructor


	return 0;
}
