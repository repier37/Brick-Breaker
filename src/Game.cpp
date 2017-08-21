/*
 * Game.cpp
 *
 *  Created on: 13 août 2017
 *      Author: pierre
 */

#include "Game.h"
#include <math.h>

namespace pierre {

Game::Game(SDL_Renderer* mainRenderer) {

	int w;
	int h;
	ballLaunched = false;
	lastTime = 0;
	SDL_GetRendererOutputSize(mainRenderer, &w, &h);
	texture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, w, h);
	if (texture == NULL) {
		std::cout << "could not create game texture" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	score = 0;
	lives = 3;
	currentLevel = 1;
	barreSupArea.x = 0;
	barreSupArea.y = 0;
	barreSupArea.w = w;
	barreSupArea.h = 100 * w / 1024;
	barreSup.initBarreSup(mainRenderer, barreSupArea.h, barreSupArea.w);

	gameZone.x = 0;
	gameZone.y = barreSupArea.h;
	gameZone.h = h - barreSupArea.h;
	gameZone.w = w;

	SDL_Point barreStartPos;
	barreStartPos.x = w / 2;
	barreStartPos.y = gameZone.h - barre.getHeight() / 2 - 20;



	barre.init(mainRenderer, barreStartPos);

	SDL_Point balleStartPos;
	balleStartPos.x = barreStartPos.x;
	balleStartPos.y = barreStartPos.y - barre.getHeight()/2 - balle.getRadius();

	if (balle.init(mainRenderer, balleStartPos) != 0) {
		std::cout << "error during ball initialisation" << std::endl;
		return;
	}

	std::cout << "game creation ok" << std::endl;
}

Game::~Game() {
	SDL_DestroyTexture(texture);
}

/* game main routine
 * return 1 to go back to menu
 * return 2 to quit
 * return 0 otherwise (continue)
 */
int Game::mainRoutine(SDL_Renderer* mainRenderer, SDL_Event userInput) {
	int result = 0;
	int update = 0;
	Uint32 timer1 = SDL_GetTicks();
	Uint32 elapsed = timer1 - lastTime;
	//Update ball pos
	//std::cout<<elapsed<<std::endl;
	//2 lignes suivantes sont pour debug

	std::vector<SDL_Rect> briques;
	update = balle.update(elapsed / 10, gameZone, barre.m_hitbox[0], briques);

	if (update == 0) {		// si l'update n'a rien donné, on passe à la suite

	} else if (update == 10000) {//sinon si l'update a détecté que la balle était perdu, on fait ce qu'il faut
		lives--;
		ballLaunched = false;
		SDL_Point startPos;
		startPos.y = barre.getPos().y - barre.getHeight()/2 - balle.getRadius();
		startPos.x = barre.getPos().x;
		balle.reset(startPos);
	} else {	// sinon c'est qu'on a touché une brique, du coup on la détruit

	}
	//update score

	//update vies
	// update barre sup
	barreSup.update(mainRenderer, score, currentLevel, lives);
//std::cout<<lives<<std::endl;
	//dessine le jeu complet
	drawGame(mainRenderer);
	//lit les inputs
	result = gameWatchEvent(userInput);
	lastTime = timer1;
	return result;
	//std::cout << "barre sup drawn" << std::endl;

}

void Game::drawGame(SDL_Renderer* mainRenderer) {
	//on dessine tout sur la texture du jeu
	SDL_SetRenderTarget(mainRenderer, texture);
	if (SDL_RenderSetViewport(mainRenderer, &barreSupArea) != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	//on met un fond blanc
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mainRenderer);

	//on dessine la barre
	SDL_RenderCopy(mainRenderer, barreSup.getTexture(), NULL, NULL);

	// Pour la suite on restreint le rendu au viewport zone de jeu
	//SDL_SetRenderTarget(mainRenderer, NULL);
	//SDL_SetRenderTarget(mainRenderer, texture);

	if (SDL_RenderSetViewport(mainRenderer, &gameZone) != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	//std::cout<<"viewport set"<<std::endl;
	//SDL_SetRenderTarget(mainRenderer, texture);
	//std::cout<< gameZone.x << " "<< gameZone.y<< " "<<gameZone.w << " "<< gameZone.h<< " "<<std::endl;

	// dessin de la barre
	barre.draw(mainRenderer);
	//On dessine la balle

	balle.draw(mainRenderer);

	// dessin des briques
	SDL_RenderSetViewport(mainRenderer, NULL);
	// on rend la main sur le renderer
	SDL_SetRenderTarget(mainRenderer, NULL);
}

void Game::startGame(SDL_Renderer* mainRenderer) {
	//load level1
	std::cout << "Game is starting" << std::endl;
	barreSup.update(mainRenderer, score, currentLevel, lives);
	std::cout << "barredrawn" << std::endl;
	drawGame(mainRenderer);
}
/*
 * Manage all the event while in game
 * Return 1 if back to menu is required
 * Return 2 if exit is required
 * Return 0 otherwise
 */

int Game::gameWatchEvent(SDL_Event userInput) {
	int result = 0;
	while (SDL_PollEvent(&userInput)) {
		switch (userInput.type) {

		case SDL_MOUSEMOTION: {
			SDL_Point mousePos;
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			barreSup.doHover(mousePos);
			if(SDL_PointInRect(&mousePos, &gameZone)){
				barre.update(mousePos.x, gameZone.w);
				if(not ballLaunched){
					balle.setPos(barre.getPos().x, 'x');
				}
			}
			//std::cout<<mousePos.y<<std::endl;
			//barre.update(mousePos.x, 1024);

			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			SDL_Point mousePos;
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			if (barreSup.doHover(mousePos)) {
				result = 1;
			}
			if (SDL_PointInRect(&mousePos, &gameZone) && not ballLaunched) {
				double tempX = mousePos.x - gameZone.w / 2;
				double tempY = mousePos.y - balle.getPos().y;
				double norme = sqrt(tempX * tempX + tempY * tempY);
				std::vector<double> dir;
				dir.push_back(tempX / norme);
				dir.push_back(tempY / norme);
				balle.launchBall(mousePos, dir);
				ballLaunched = true;

			}
			//balle.setPos(mousePos);
			//currentLevel++;
			break;
		}

		case SDL_QUIT:
			result = 2;
			break;

		default:
			result = 0;
			break;
		}
	}
	return result;
}

SDL_Texture * Game::getTexture() {
	return texture;
}

} /* namespace pierre */
