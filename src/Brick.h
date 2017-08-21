/*
 * Brick.h
 *
 *  Created on: 6 août 2017
 *      Author: pierre
 */

#ifndef BRICK_H_
#define BRICK_H_
#include <SDL2/SDL.h>
#include <vector>
namespace pierre {

class Brick {
public:
	std::vector<SDL_Rect> m_hitbox;
	SDL_Texture* m_texture;



private:
	int m_pv;
	int m_x;
	int m_y;



public:
	Brick(int x, int y, SDL_Renderer* renderer);
	virtual ~Brick();

	void draw(SDL_Renderer* renderer);
	int lostPV();
	void deleteBrick();

};

} /* namespace pierre */

#endif /* BRICK_H_ */
