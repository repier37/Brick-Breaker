/*
 * Ball.h
 *
 *  Created on: 1 août 2017
 *      Author: pierre gilles
 */

#ifndef BALL_H_
#define BALL_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

namespace pierre {

class Ball {
public:
	const static int MAX_SPEED = 15;
	const static int MIN_SPEED=5;
	const static int START_SPEED = 7;

private:
	SDL_Texture* texture;
	double speed;
	std::vector <double> dir;
	SDL_Point pos;
	int radius;

public:
	Ball();
	virtual ~Ball();

	int init(SDL_Renderer* renderer,SDL_Point startPos);
	void draw(SDL_Renderer* renderer);
	void setPos(SDL_Point newPos);
	void setPos(int val, char axis);
	int getRadius();
	void launchBall(SDL_Point mousePos, std::vector<double> dir);
	SDL_Point getPos();
	void reset(SDL_Point startPos);

	/* update the ball position
	 * deal with collision on the game zone
	 * return 1 if the ball is lost
	 * return 0 otherwise
	 */
	int update(Uint32 elapsed, SDL_Rect gameZone, SDL_Rect barreHitbox, std::vector<SDL_Rect> briques);

	bool collision(const SDL_Rect* obst);

	double distanceSquared(int x1, int y1, int x2, int y2);
	/*
	bool collision(const std::vector<SDL_Rect>);
	bool advancedCollision(int elapsed, const std::vector<SDL_Rect> hitBox);*/
};

} /* namespace pierre */

#endif /* BALL_H_ */
