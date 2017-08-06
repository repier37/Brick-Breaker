/*
 * Ball.cpp
 *
 *  Created on: 1 août 2017
 *      Author: pierre
 */

#include "Ball.h"
#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

namespace pierre {

Ball::Ball(SDL_Renderer* renderer) {
	SDL_Surface* image = IMG_Load("data/ball.png");
	if (image == NULL) {
		std::cout << "could not load ball image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	m_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	m_speed = 5;
	m_dir = -3.07 * M_PI / 4;
	m_x = 950;
	m_y = 100;

	m_hitBox.x = m_x - BALL_RADIUS;
	m_hitBox.y = m_y - BALL_RADIUS;
	m_hitBox.w = 2 * BALL_RADIUS;
	m_hitBox.h = 2 * BALL_RADIUS;

}

Ball::~Ball() {
	SDL_DestroyTexture(m_texture);
}

void Ball::update(int sHeight, int sWidth) {
	m_x += m_speed * cos(m_dir);

	m_y += m_speed * sin(m_dir);
	/*std::cout << m_dir << " " << cos(m_dir) << std::endl;

	if (m_x > sWidth || m_x < 10) {
	 m_dir = M_PI - m_dir;
	 }

	 if (m_y > sHeight || m_y < 10) {
	 m_dir *= -1.0;

	 }*/

	m_hitBox.x = m_x - BALL_RADIUS;
	m_hitBox.y = m_y - BALL_RADIUS;

}

bool Ball::collision(const SDL_Rect* obst) {
	int leftBall = m_hitBox.x;
	int topBall = m_hitBox.y;
	int rightBall = m_hitBox.x + m_hitBox.w;
	int bottomBall = m_hitBox.y + m_hitBox.h;

	int leftObs = obst->x;
	int topObs = obst->y;
	int rightObs = obst->x + obst->w;
	int bottomObs = obst->y + obst->h;

	if (leftBall >= rightObs || topBall >= bottomObs || rightBall <= leftObs
			|| bottomBall <= topObs) {
		return false;
	}

	SDL_Rect res;
	SDL_IntersectRect(&m_hitBox, obst, &res);

	std::cout << "collision detected" << std::endl;
	if (res.w >= res.h) {
		std::cout << "along y axis" << std::endl;
		m_dir *= -1.0;
	} else {
		std::cout << "along x axis" << std::endl;
		m_dir = M_PI - m_dir;
	}
	return true;
}



bool Ball::collision(const std::vector<SDL_Rect> hitBox) {
	bool result = false;
	for (unsigned int i = 0; i < hitBox.size(); i++) {
		result = collision(&hitBox[i]);
		if (result) {
			break;
		}

	}

	return result;
}

void Ball::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_hitBox);

//std::cout << SDL_GetError()<<std::endl;
}

} /* namespace pierre */
