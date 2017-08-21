/*
 * Menu.cpp
 *
 *  Created on: 14 aoï¿½t 2017
 *      Author: pierre.gilles
 */

#include "Menu.h"
#include <iostream>
#include <string>

namespace pierre {

Menu::Menu(SDL_Renderer* mainRenderer) {
	// crï¿½ation d'une texture qui fait tout l'ï¿½cran
	SDL_GetRendererOutputSize(mainRenderer, &w, &h);

	menu = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, w, h);
	if (menu == NULL) {
		std::cout << "Could not create texture" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	addButton("data/menu/startU.png", "data/menu/startD.png");
	std::cout << "start image loaded" << std::endl;
	addButton("data/menu/exitU.png", "data/menu/exitD.png");
}

Menu::~Menu() {
	std::cout << "Menu killed" << std::endl;
	SDL_DestroyTexture(menu);
	for (unsigned int i = 0; i < buttonNorm.size(); i++) {
		SDL_FreeSurface(buttonNorm[i]);
		SDL_FreeSurface(buttonClic[i]);
	}
}

void Menu::addButton(std::string imagePathNormal, std::string imagePathClic) {
	SDL_Surface* button1 = IMG_Load(imagePathNormal.c_str());
	SDL_Surface* button2 = IMG_Load(imagePathClic.c_str());
	if(button1==NULL){
		std::cout<<"Could not create button normal"<<std::endl;
		std::cout<<IMG_GetError()<<std::endl;

	}
	if (button2==NULL){
		std::cout<<"Could not create button hover"<<std::endl;
		std::cout<<IMG_GetError()<<std::endl;
	}
	// default position for the button
	SDL_Rect dstRect;
	dstRect.w = button1->w;
	dstRect.h = button1->h;
	dstRect.x = 0;
	dstRect.y = 0;

	buttonNorm.push_back(button1);
	buttonClic.push_back(button2);
	buttonRend.push_back(button1);
	buttonsPos.push_back(dstRect);
}

SDL_Texture* Menu::getTexture() {
	return menu;
}

void Menu::drawMenu(SDL_Renderer* mainRenderer) {
	// on dessine le menu sur sa texture
	SDL_SetRenderTarget(mainRenderer, menu);

	// on commence par mettre un fond blanc
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mainRenderer);

	//on ajoute les boutons
	int startX = w / 2;
	int yPadding = (h - buttonNorm.size() * buttonsPos[0].h)
			/ (buttonNorm.size() + 1);
	for (unsigned int i = 0; i < buttonNorm.size(); i++) {
		// on crï¿½e une texture ï¿½ partir des donnï¿½es enregistrï¿½es au dï¿½but
		SDL_Texture* temp = SDL_CreateTextureFromSurface(mainRenderer,
				buttonRend[i]);

		// On enregistre la position ï¿½ laquelle le bouton va ï¿½tre dessinï¿½
		buttonsPos[i].x = startX - buttonsPos[i].w / 2;
		buttonsPos[i].y = yPadding * (i + 1) + buttonsPos[i].h * i;

		//on dessine le bouton
		SDL_RenderCopy(mainRenderer, temp, NULL, &buttonsPos[i]);

		SDL_DestroyTexture(temp);
	}

	// on rend la main sur le renderer
	SDL_SetRenderTarget(mainRenderer, NULL);
}

/* watchEvent
 * Gère les input utilisateurs sur le menu
 * Redessinne les boutons en cas de hover
 * Renvoie le numéro du bouton cliqué (0 en partant du haut)
 * Renvoie 10 pour sortir
 * Renvoie -1 dans tous les autres cas
 */
int Menu::watchEvent(SDL_Event event) {
	int result = -1;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_MOUSEMOTION:
			for (unsigned int i = 0; i < buttonsPos.size(); i++) {
				SDL_Point mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				if (SDL_PointInRect(&mousePos, &buttonsPos[i])) {
					buttonRend[i] = buttonClic[i];
				} else {
					buttonRend[i] = buttonNorm[i];
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			for (unsigned int i = 0; i < buttonsPos.size(); i++) {
				SDL_Point mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				if (SDL_PointInRect(&mousePos, &buttonsPos[i])) {
					buttonRend[i] = buttonClic[i];
					switch (i){
					case 0:
						result = 0;
						break;
					case 1:
						result=1;
						break;
					default:
						result = -1;
						break;
					}
				}
			}
			break;
		case SDL_QUIT:
			result = 10;
			break;

		default:
			result = -1;
			break;
		}
	}

	return result;

}

void Menu::startGame(){

}
void options();
void exit();

}/* namespace pierre */
