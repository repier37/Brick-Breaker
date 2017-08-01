/*
 * Screen.h
 *
 *  Created on: 31 juil. 2017
 *      Author: pierre
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL.h>
#include <iostream>

namespace pierre {

class Screen {
private:
	SDL_Window* m_window;
	SDL_Texture* m_texture;


public:
	SDL_Renderer* m_renderer;

public:
	const static int SCREEN_HEIGHT = 768;
	const static int SCREEN_WIDTH = 1024;

public:
	Screen();
	bool init();
	void update();
	void close();
	virtual ~Screen();
};

} /* namespace pierre */

#endif /* SCREEN_H_ */
