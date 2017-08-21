/*
 * Bar.cpp
 *
 *  Created on: 5 août 2017
 *      Author: pierre
 */

#include "Bar.h"
#include <iostream>

namespace pierre {

Bar::Bar() {
	height = 20;
	width=200;
	pos.x=0;
	pos.y=0;
	texture=NULL;
}

Bar::~Bar() {
	SDL_DestroyTexture(texture);
}

void Bar::init(SDL_Renderer* renderer, SDL_Point startPos) {


	SDL_Surface* image = IMG_Load("data/bar.png");
	if (image == NULL) {
		std::cout << "could not load bar image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	pos = startPos;

	SDL_Rect hitBox;

	hitBox.x = pos.x - width / 2;
	hitBox.y = pos.y - height / 2;
	hitBox.w = width;
	hitBox.h = height;

	m_hitbox.push_back(hitBox);
}

void Bar::update(int x, int screenWidth) {

	if (x + m_hitbox[0].w / 2 > screenWidth) {
		pos.x = screenWidth - m_hitbox[0].w / 2;
	} else if (x - m_hitbox[0].w / 2 < 0) {
		pos.x = m_hitbox[0].w / 2;
	} else {
		pos.x = x;
	}

	m_hitbox[0].x = pos.x - width / 2;
}

int Bar::getHeight(){
	return height;
}

void Bar::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &m_hitbox[0]);
}

SDL_Point Bar::getPos(){
	return pos;
}


} /* namespace pierre */
