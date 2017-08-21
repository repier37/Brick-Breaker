/*
 * BarreSup.h
 *
 *  Created on: 15 août 2017
 *      Author: pierre
 */

#ifndef BARRESUP_H_
#define BARRESUP_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

namespace pierre {

class BarreSup {
private:
	SDL_Texture* barreSupText; // texture principale qui regroupe l'ensemble
	SDL_Surface* scoreZone;
	SDL_Surface* levelZone;
	SDL_Surface* menuZoneU;
	SDL_Surface* menuZoneD;
	SDL_Surface* menuZoneR;
	SDL_Surface* ballZone;
	SDL_Texture* bckgnd;
	SDL_Rect scoreRect;
	SDL_Rect levelRect;
	SDL_Rect menuRect;
	SDL_Rect ballRect;
	char* fontPath;

public:
	BarreSup();

	virtual ~BarreSup();

	void initBarreSup(SDL_Renderer* mainRenderer, int h, int w);
	SDL_Texture* getTexture();


	void updateScore(int score);
	void updateLevel(int level);
	void updateLives(int lives);

	void drawLevel(int level);
	void drawMenu();
	void drawBallZone(int lives);
	void update(SDL_Renderer* mainRenderer, int score, int level, int lives);
	bool doHover(SDL_Point mousePos);
};

} /* namespace pierre */

#endif /* BARRESUP_H_ */
