/*
 * Ball.cpp
 *
 *  Created on: 1 août 2017
 *      Author: pierre
 */

#include "Ball.h"
#include <iostream>
#include <math.h>
using namespace std;
namespace pierre {

Ball::Ball(SDL_Renderer* renderer) {
	SDL_Surface* image = SDL_LoadBMP("data/ball.bmp");
	if (image == NULL) {
		std::cout << "could not load ball image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	m_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	m_speed = 1;
	m_dir = M_PI / 4.0;
	m_x = 950;
	m_y = 100;
}

Ball::~Ball() {
	SDL_DestroyTexture(m_texture);
}

void Ball::update(int sHeight, int sWidth) {
	m_x += m_speed * cos(m_dir);
	m_y += m_speed * sin(m_dir);
	cout << m_dir << " " << m_x << endl;

	if (m_x < 10) {
		m_dir += M_PI;
		m_dir = fmod(m_dir, M_PI_2);
	}

}

void Ball::drawBall(SDL_Renderer* renderer) {
	SDL_Rect dstrect;
	dstrect.x = m_x - BALL_WIDTH / 2;
	dstrect.y = m_y - BALL_HEIGTH / 2;
	dstrect.w = BALL_WIDTH;
	dstrect.h = BALL_HEIGTH;

	SDL_RenderCopy(renderer, m_texture, NULL, &dstrect);

	//std::cout << SDL_GetError()<<std::endl;
}

} /* namespace pierre */
