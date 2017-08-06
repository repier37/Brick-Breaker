/*
 * Bar.cpp
 *
 *  Created on: 5 août 2017
 *      Author: pierre
 */

#include "Bar.h"
#include <iostream>

namespace pierre {

Bar::Bar(SDL_Renderer* renderer, int posx, int posy) {
	m_x = posx;
	m_y = posy;
	m_height=20;
	m_width=200;

	SDL_Surface* image = IMG_Load("data/bar.png");
	if (image == NULL) {
		std::cout << "could not load bar image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	m_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	m_hitbox.x = m_x-m_width/2;
	m_hitbox.y = m_y+m_height/2;
	m_hitbox.w = m_width;
	m_hitbox.h = m_height;
}

Bar::~Bar() {
	SDL_DestroyTexture(m_texture);
}

void Bar::update(int x, int screenWidth) {

	if (x+m_hitbox.w/2 > screenWidth){
		m_x = screenWidth-m_hitbox.w/2;
	} else if (x - m_hitbox.w/2 < 0){
		m_x = m_hitbox.w/2;
	} else {
		m_x = x;
	}

	m_hitbox.x = m_x-m_width/2;
	m_hitbox.y = m_y+m_height/2;
}

void Bar::draw(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, m_texture, NULL, &m_hitbox);
}

} /* namespace pierre */
