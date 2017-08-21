/*
 * Bar.h
 *
 *  Created on: 5 août 2017
 *      Author: pierre
 */

#ifndef BAR_H_
#define BAR_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

namespace pierre {

class Bar {
public:
	std::vector<SDL_Rect> m_hitbox;

private:
	double height;
	double width;
	SDL_Texture* texture;
	SDL_Point pos;


public:
	Bar();
	virtual ~Bar();

	void init(SDL_Renderer* renderer, SDL_Point startPos);
	void update(int x, int screenWidth);
	void draw(SDL_Renderer* renderer);
	int getHeight();
	SDL_Point getPos();
};

} /* namespace pierre */

#endif /* BAR_H_ */
