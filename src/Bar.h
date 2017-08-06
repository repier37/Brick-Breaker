/*
 * Bar.h
 *
 *  Created on: 5 août 2017
 *      Author: pierre
 */

#ifndef BAR_H_
#define BAR_H_
#include <SDL.h>
#include <SDL_image.h>

namespace pierre {

class Bar {
public:
	SDL_Rect m_hitbox;

private:
	double m_height;
	double m_width;
	SDL_Texture* m_texture;
	double m_x;
	double m_y;


public:
	Bar(SDL_Renderer* renderer, int posx, int posy);
	virtual ~Bar();
	void update(int x, int screenWidth);
	void draw(SDL_Renderer* renderer);
};

} /* namespace pierre */

#endif /* BAR_H_ */
