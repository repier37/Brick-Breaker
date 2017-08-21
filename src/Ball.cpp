/*
 * Ball.cpp
 *
 *  Created on: 1 août 2017
 *      Author: pierre
 */

#include "Ball.h"
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace pierre {

Ball::Ball() {
	pos= {0,0};
	texture=NULL;
	speed = 0;
	dir.push_back(0);
	dir.push_back(0);
	radius = 10;

}

Ball::~Ball() {
	SDL_DestroyTexture(texture);
}

int Ball::init(SDL_Renderer* renderer, SDL_Point startPos) {
	SDL_Surface* image = IMG_Load("data/ball.png");
	if (image == NULL) {
		std::cout << "could not load ball image" << std::endl;
		std::cout << IMG_GetError() << std::endl;
		return -1;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL) {
		std::cout << "could not load ball image" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -2;
	}
	SDL_FreeSurface(image);
	pos = startPos;
	std::cout << "ball init successful" << std::endl;
	return 0;
}

//draw the ball at its current position
void Ball::draw(SDL_Renderer* renderer) {
	SDL_Rect dstrect;
	dstrect.h = radius * 2;
	dstrect.w = radius * 2;
	dstrect.x = pos.x - radius;
	dstrect.y = pos.y - radius;
	//std::cout<< dstrect.x << " "<< dstrect.y<< " "<<dstrect.w << " "<< dstrect.h<< " "<<std::endl;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}
void Ball::setPos(SDL_Point newPos) {
	pos = newPos;
}

void Ball::setPos(int val, char axis) {
	switch (axis) {
	case 'x': {
		pos.x = val;
		break;
	}
	case 'y': {
		pos.y = val;
		break;
	}
	default:
		break;
	}
}

int Ball::getRadius() {
	return radius;
}

void Ball::launchBall(SDL_Point mousePos, std::vector<double> dir) {
	speed = START_SPEED;
	this->dir = dir;
}

SDL_Point Ball::getPos() {
	return pos;
}

/* met à jour la position de la balle
 * retourne 10000 si la balle est sortie du jeu;
 * retourne l'id de la brique touché si une brique est touché
 * retourn 0 sinon
 */
int Ball::update(Uint32 elapsed, SDL_Rect gameZone, SDL_Rect barreHitbox,
		std::vector<SDL_Rect> briques) {
	bool barrCollide = false;
	// on met à jour la vitesse
	//speed -= 0.01*elapsed;
	if (speed < MIN_SPEED) {
		speed = MIN_SPEED;
	}
	// on met à jour les positions

	pos.x += (speed * dir[0]) * elapsed;

	//on test les bords de l'écran en x
	if (pos.x + radius > gameZone.w) {
		pos.x = gameZone.w - radius;
		dir[0] = dir[0] * (-1);
	} else if (pos.x - radius < 0) {
		pos.x = radius;
		dir[0] = dir[0] * (-1);
	}
	//on test les bords de la barre en x
	if (collision(&barreHitbox)) {
		dir[0] = dir[0] * (-1);
	}
	//on test les briques en x;

	pos.y += (speed * dir[1]) * elapsed;
	// on test en y si on est sorti de l'écran;
	if (pos.y > gameZone.h) {
		return 10000;
	}
	// puis on test les autres bords de la fenetre en y
	if (pos.y < radius) {
		pos.y = radius;
		dir[1] = -1 * dir[1];
	}
	//on test les bords de la barre en y (si on a pas déjà eu une collision
	if (collision(&barreHitbox)) {
		dir[1] = dir[1] * (-1);
	}
	//on test les briques en y;
	return 0;
}

void Ball::reset(SDL_Point startPos) {
	pos = startPos;
	dir[0] = 0;
	dir[1] = 0;
	speed = 0;
}

bool Ball::collision(const SDL_Rect* obst) {

	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (pos.x < obst->x) {
		cX = obst->x;
	} else if (pos.x > obst->x + obst->w) {
		cX = obst->x + obst->w;
	} else {
		cX = pos.x;
	}

	//Find closest y offset
	if (pos.y < obst->y) {
		cY = obst->y;
	} else if (pos.y > obst->y + obst->h) {
		cY = obst->y + obst->h;
	} else {
		cY = pos.y;
	}

	//If the closest point is inside the circle
	if (distanceSquared(pos.x, pos.y, cX, cY) < radius * radius) {
		//This box and the circle have collided
		if (cX == obst->x) {
			pos.x = cX - radius;
		} else if (pos.x == obst->x + obst->w) {
			pos.x = cX + radius;
		}
		if (cY == obst->y) {
			pos.y = cY - radius;
		} else if (pos.y == obst->y + obst->h) {
			pos.y = cY + radius;
		}
		return true;
	} //If the shapes have not collided
	return false;
}/*
 if (leftBall >= rightObs || topBall >= bottomObs || rightBall <= leftObs
 || bottomBall <= topObs) {
 return false;
 }

 SDL_Rect res;
 SDL_IntersectRect(&m_hitBox, obst, &res);

 //std::cout << "collision detected" << std::endl;
 if (res.w >= res.h) {
 //std::cout << "along y axis" << std::endl;
 m_dir *= -1.0;
 } else {
 //std::cout << "along x axis" << std::endl;
 m_dir = M_PI - m_dir;
 }
 return true;
 }*/
/*
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
 */
/*
 bool Ball::advancedCollision(int elapsed, const std::vector<SDL_Rect> hitBox) {
 bool result = false;
 if (collision(hitBox)) {

 m_speed += 160.0 / elapsed;

 result = true;
 }
 if (m_speed > MAX_SPEED) {
 m_speed = MAX_SPEED;
 }
 std::cout << m_speed << std::endl;
 return result;
 }
 */

double Ball::distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

}/* namespace pierre */
