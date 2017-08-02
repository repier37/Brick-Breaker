/*
 * Ball.h
 *
 *  Created on: 1 août 2017
 *      Author: pierre gilles
 */

#ifndef BALL_H_
#define BALL_H_
#include <SDL.h>

namespace pierre {

class Ball {
public:
	const static int BALL_WIDTH = 20;
	const static int BALL_HEIGTH = 20;

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
	void drawBall(SDL_Renderer* renderer);
};

} /* namespace pierre */

#endif /* BALL_H_ */
