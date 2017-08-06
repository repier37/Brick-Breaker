/*
 * Brick.cpp
 *
 *  Created on: 6 août 2017
 *      Author: pierre
 */

#include "Brick.h"
#include <SDL_image.h>
#include <iostream>

namespace pierre {

Brick::Brick(int x, int y, SDL_Renderer* renderer) {
	m_x = x;
	m_y = y;
	m_pv = 1;

	SDL_Surface* image = IMG_Load("data/brick.png");
	if (image == NULL) {
		std::cout << "could not load brick image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	m_texture = SDL_CreateTextureFromSurface(renderer, image);
	if (m_texture == NULL) {
		std::cout << "Could not create texture" << std::endl;
		std::cout << SDL_GetError() << std::endl;

	}

	SDL_FreeSurface(image);

	m_hitbox.x = m_x;
	m_hitbox.y = m_y;
	m_hitbox.w = 50;
	m_hitbox.h = 20;
}

Brick::~Brick() {
	//std::cout << "brick destroyed" << std::endl;
	//SDL_DestroyTexture(m_texture);
}

void Brick::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_hitbox);
}

void Brick::deleteBrick(){
	SDL_DestroyTexture(m_texture);
}

int Brick::lostPV(){
	m_pv--;
	if (m_pv<=0){
		deleteBrick();
	}
	return m_pv;
}

} /* namespace pierre */
