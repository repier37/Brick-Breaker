/*
 * Menu.h
 *
 *  Created on: 14 ao�t 2017
 *      Author: pierre.gilles
 */

#ifndef MENU_H_
#define MENU_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>


namespace pierre {
class Menu {
private :
	SDL_Texture* menu;
	std::vector<SDL_Rect> buttonsPos;
	std::vector<SDL_Surface*> buttonNorm;
	std::vector<SDL_Surface*> buttonClic;
	std::vector<SDL_Surface*> buttonRend;
	int w;
	int h;

public:
	Menu(SDL_Renderer* mainRenderer);
	virtual ~Menu();
	SDL_Texture* getTexture();

	void addButton(std::string imagePathNormal,std::string imagePathHover);

	void drawMenu(SDL_Renderer* mainRenderer);

	void hover(int index);

	int watchEvent(SDL_Event event);

	void startGame();
	void options();
	void exit();
};


} /*namespace pierre;*/
#endif /* MENU_H_ */
