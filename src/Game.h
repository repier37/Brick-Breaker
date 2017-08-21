/*
 * Game.h
 *
 *  Created on: 13 août 2017
 *      Author: pierre
 */

#ifndef GAME_H_
#define GAME_H_
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Level.h"
#include "BarreSup.h"
#include "Ball.h"
#include "Bar.h"

namespace pierre {

class Game {
private:
	int score;
	int lives;
	int currentLevel;
	BarreSup barreSup;
	SDL_Texture* texture;
	SDL_Rect barreSupArea;
	SDL_Rect gameZone;
	std::vector<SDL_Rect> gameZoneBord;
	Ball balle;
	Bar barre;
	bool ballLaunched;
	Uint32 lastTime;



public:
	Game(SDL_Renderer* mainRenderer);
	virtual ~Game();
	int mainRoutine(SDL_Renderer* mainRenderer, SDL_Event userInput);
	void drawGame(SDL_Renderer* mainRenderer);
	void startGame(SDL_Renderer* mainRenderer);
	int gameWatchEvent(SDL_Event userInput);
	SDL_Texture* getTexture();
};

} /* namespace pierre */

#endif /* GAME_H_ */
