/*
 * Ball.h
 *
 *  Created on: 1 août 2017
 *      Author: pierre gilles
 */

#ifndef BALL_H_
#define BALL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

namespace pierre {

class Ball {
public:
	SDL_Rect m_hitBox;
	const static int BALL_RADIUS=10;

private:
	SDL_Texture* m_texture;
	double m_speed;
	double m_dir;
	double m_x;
	double m_y;

public:
	Ball(SDL_Renderer* renderer);
	virtual ~Ball();

	void update(int screenHeight, int screenWidth);
	void draw(SDL_Renderer* renderer);
	bool collision(const SDL_Rect* obst);
	bool collision(const std::vector<SDL_Rect>);
};

} /* namespace pierre */

#endif /* BALL_H_ */
