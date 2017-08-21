/*
 * BarreSup.cpp
 *
 *  Created on: 15 août 2017
 *      Author: pierre
 */

#include "BarreSup.h"

namespace pierre {

BarreSup::BarreSup() {

	barreSupText = NULL;
	bckgnd = NULL;
	scoreZone = NULL;
	levelZone = NULL;
	menuZoneD = NULL;
	menuZoneU = NULL;
	ballZone = NULL;
	scoreRect= {0,0,0,0};
	levelRect= {0,0,0,0};
	menuRect= {0,0,0,0};
	ballRect= {0,0,0,0};
	fontPath = NULL;
	menuZoneR=menuZoneU;
}
BarreSup::~BarreSup() {

	SDL_DestroyTexture(barreSupText);
	SDL_DestroyTexture(bckgnd);
	SDL_FreeSurface(ballZone);
	SDL_FreeSurface(levelZone);
	SDL_FreeSurface(scoreZone);
	SDL_FreeSurface(menuZoneU);
	SDL_FreeSurface(menuZoneD);
	std::cout << "barresup destroyed" << std::endl;
}

void BarreSup::initBarreSup(SDL_Renderer* mainRenderer, int h, int w) {
	/*
	 SDL_Surface* scoreZone;
	 SDL_Surface* levelZone;
	 SDL_Surface* Menu;
	 SDL_Surface* ballZone;*/

	barreSupText = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, w, h);

	// on charge le background
	SDL_Surface* temp = IMG_Load("data/BarreSup/barreSup.png");
	if (temp == NULL) {
		std::cout << "Could not load barre sup background" << std::endl;
		std::cout << IMG_GetError() << std::endl;
	}

	bckgnd = SDL_CreateTextureFromSurface(mainRenderer, temp);
	if (bckgnd == NULL) {
		std::cout << "Error during barre sup background init" << std::endl;
	}

	SDL_FreeSurface(temp);
	//on met d�s maintenant le background dans la texure de la barre
	SDL_SetRenderTarget(mainRenderer, barreSupText);
	SDL_RenderCopy(mainRenderer, bckgnd, NULL, NULL);
	SDL_SetRenderTarget(mainRenderer, NULL);

	//on charge le bouton
	menuZoneU = IMG_Load("data/BarreSup/backU.png");
	menuZoneD = IMG_Load("data/BarreSup/backD.png");

	menuZoneR = menuZoneU;

	/*d�finition de l'emplacement des 4 zones*/
	double xUnit = w / 970.0;
	int xPadding = 50 * xUnit;
	int longueur = 180 * xUnit;
	double yUnit = h / 100.0;
	int yPadding = 26 * yUnit;
	int hauteur = 48 * yUnit;

	//ballRect = {xPadding,yPadding,longueur,hauteur}; //x,y,w,h
	ballRect.x = xPadding + xUnit * 15;
	ballRect.y = yPadding + 15 * yUnit;
	ballRect.w = longueur - 30 * xUnit;
	ballRect.h = hauteur - 30 * yUnit;

	menuRect = {4*xPadding+3*longueur,yPadding,longueur,hauteur};

	levelRect.x = xPadding * 2 + longueur + xUnit * 15;
	levelRect.y = yPadding + 15 * yUnit;
	levelRect.w = longueur - 30 * xUnit;
	levelRect.h = hauteur - 30 * yUnit;

	scoreRect.x = xPadding * 3 + longueur * 2 + xUnit * 20;
	scoreRect.y = yPadding + 15 * yUnit;
	scoreRect.w = longueur - 30 * xUnit;
	scoreRect.h = hauteur - 30 * yUnit;

	fontPath = "data/fonts/andalemo.ttf";

	ballZone = SDL_CreateRGBSurface(0, ballRect.w, ballRect.h, 32, 0xff000000,
			0x00ff0000, 0x0000ff00, 0x000000ff);

}

SDL_Texture* BarreSup::getTexture() {
	return barreSupText;
}

void BarreSup::update(SDL_Renderer* mainRenderer, int score, int level,
		int lives) {
// on dessine la barre sur sa texture
	SDL_SetRenderTarget(mainRenderer, barreSupText);

//on met à jour toutes les surfaces
	updateScore(score);
	//std::cout << "score updated" << std::endl;
	updateLevel(level);
	updateLives(lives);

//on desssine le score
	SDL_Texture* temp = SDL_CreateTextureFromSurface(mainRenderer, scoreZone);
	if (temp == NULL) {
		std::cout << "Could not draw scoreZone" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_RenderCopy(mainRenderer, temp, NULL, &scoreRect);

	SDL_DestroyTexture(temp);

//on dessine le bouton menu
	temp = SDL_CreateTextureFromSurface(mainRenderer, menuZoneR);
	if (temp == NULL) {
		std::cout << "Could not draw menuZone" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_RenderCopy(mainRenderer, temp, NULL, &menuRect);
	SDL_DestroyTexture(temp);

//on dessine la zone niveau
	temp = SDL_CreateTextureFromSurface(mainRenderer, levelZone);
	if (temp == NULL) {
		std::cout << "Could not draw levelZone" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_RenderCopy(mainRenderer, temp, NULL, &levelRect);
	SDL_DestroyTexture(temp);

	//on dessine la zone vies
	temp = SDL_CreateTextureFromSurface(mainRenderer, ballZone);
	if (temp == NULL) {
		std::cout << "Could not draw ballzone" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_RenderCopy(mainRenderer, temp, NULL, &ballRect);
	SDL_DestroyTexture(temp);

//on rend la main sur le renderer
	SDL_SetRenderTarget(mainRenderer, NULL);
}

void BarreSup::updateScore(int score) {
//std::cout << fontPath << std::endl;
	TTF_Font* font = TTF_OpenFont(fontPath, 60);
	if (font == NULL) {
		std::cout << "Could not load font" << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}
	SDL_FreeSurface(scoreZone);
	SDL_Color color = { 0, 0, 0 }, bgcolor = { 0xff, 0xff, 0xff };

	std::string text = std::to_string(score);

	text = std::string(9 - text.length(), '0') + text;
//std::cout << text << std::endl;

	scoreZone = TTF_RenderText_Shaded(font, text.c_str(), color, bgcolor);
	if (scoreZone == NULL) {
		std::cout << "Error during score update" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	TTF_CloseFont(font);
}

void BarreSup::updateLevel(int level) {
//std::cout << fontPath << std::endl;
	TTF_Font* font = TTF_OpenFont(fontPath, 60);
	if (font == NULL) {
		std::cout << "Could not load font" << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}
	SDL_FreeSurface(levelZone);
	SDL_Color color = { 0, 0, 0 }, bgcolor = { 0xff, 0xff, 0xff };

	std::string text = std::to_string(level);

	text = std::string(3 - text.length(), '0') + text;

	text = "Level: " + text;
	//std::cout << text << std::endl;

	levelZone = TTF_RenderText_Shaded(font, text.c_str(), color, bgcolor);
	if (levelZone == NULL) {
		std::cout << "Error during level update" << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}
	TTF_CloseFont(font);
}

void BarreSup::updateLives(int lives) {
	SDL_Surface* balle = IMG_Load("data/ball_flat.png");
	if (balle == NULL) {
		std::cout << "Could not draw ballzone" << std::endl;
		std::cout << IMG_GetError() << std::endl;
	}
	int h = ballRect.h;
	int w = h;
	// we cap the rendering of lives to 6
	if (lives>6){
		lives = 6;
	}
	SDL_FillRect(ballZone, NULL, SDL_MapRGBA(ballZone->format, 255, 255, 255,255));
	for (int i = 0; i < lives; i++) {
		SDL_Rect dstRect;
		dstRect.x = (w + 10) * i;
		dstRect.y = 0;
		dstRect.h = h;
		dstRect.w = w;
		;
		if (SDL_BlitScaled(balle, NULL, ballZone, &dstRect) < 0) {
			std::cout << "Could not draw ballzone" << std::endl;
			std::cout << SDL_GetError() << std::endl;
		}

	}



	SDL_FreeSurface(balle);
}

bool BarreSup::doHover(SDL_Point mousePos) {
	bool res = false;
	if (SDL_PointInRect(&mousePos, &menuRect)) {
		res = true;
		menuZoneR = menuZoneD;
	} else {
		menuZoneR = menuZoneU;
	}
	return res;
}

} /* namespace pierre */

