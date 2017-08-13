//============================================================================
// Name        : Brick_Breaker.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include "Ball.h"
#include "Bar.h"
#include "Brick.h"
#include "Level.h"

using namespace std;
using namespace pierre;

int main(int argc, char **argv) {
	Screen mainScreen;

	mainScreen.init();

	SDL_Event event;

	//initialisation of game objects

	Ball ball(mainScreen.m_renderer);
	//cout<<"ball created"<<endl;
	Bar bar(mainScreen.m_renderer, Screen::SCREEN_WIDTH/2, Screen::SCREEN_HEIGHT-40);
	//cout<<"bar created"<<endl;
	//Brick brickTest(20,20,mainScreen.m_renderer);
	Level level1 (mainScreen.m_renderer);
	//cout<<"level created"<<endl;

	int time;
	int elapsedSinceCollision=0;

	bool gameStart = false;
	bool quit = 0;
	// game loop
	while (!quit) {
		time = SDL_GetTicks();
		cout<<time<<endl;
		SDL_RenderClear(mainScreen.m_renderer);

		// update ball;
		ball.update(Screen::SCREEN_HEIGHT,Screen::SCREEN_WIDTH);

		if(ball.collision(mainScreen.gameAreaBound)){
			elapsedSinceCollision=time-elapsedSinceCollision;
		}
		if(ball.advancedCollision(elapsedSinceCollision,bar.m_hitbox)){
			elapsedSinceCollision=time-elapsedSinceCollision;
		}

		for (unsigned int i =0; i<level1.brickArr.size();i++){
			if(ball.advancedCollision(elapsedSinceCollision, level1.brickArr[i].m_hitbox)){
				level1.update(i);
				elapsedSinceCollision=time-elapsedSinceCollision;
				break;
			}
		}


		// update screen
		//mainScreen.update();

		// update brick

		// update bar

		//draw everything on the screen
		ball.draw(mainScreen.m_renderer);
		bar.draw(mainScreen.m_renderer);
		level1.draw(mainScreen.m_renderer);
		//brickTest.draw(mainScreen.m_renderer);

		//event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT :
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				bar.update(event.motion.x, Screen::SCREEN_WIDTH);
				break;
				//ball.update(event.motion.x, event.motion.y);
			default:
				break;
			}
		}

		SDL_RenderPresent(mainScreen.m_renderer);

	}

	// End of programm
	level1.deleteLevel();
	//sdl destructor
	mainScreen.close();
	//ball destructor


	return 0;
}
