/*
 * Screen.cpp
 *
 *  Created on: 31 juil. 2017
 *      Author: pierre
 */

#include "Screen.h"
using namespace std;

namespace pierre {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL) {
}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

bool Screen::init() {

	if (SDL_Init(SDL_INIT_VIDEO)) {
		cout << "Error during initialization" << endl;
		cout << SDL_GetError() << endl;
		close();
		return false;

	} else {
		cout << "SDL init ok" << endl;

		string gameName = "Brick Breaker";
		const char* windowName = gameName.c_str();

		m_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		if (m_window == NULL) {
			cout << "Could not create window" << endl;
			cout << SDL_GetError() << endl;
			close();
			return false;

		} else {
			m_renderer = SDL_CreateRenderer(m_window, -1,
					SDL_RENDERER_PRESENTVSYNC);

			if (m_renderer == NULL) {
				cout << "Could not create renderer" << endl;
				cout << SDL_GetError() << endl;
				close();
				return false;

			} else {
				m_texture = SDL_CreateTexture(m_renderer,
						SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
						SCREEN_WIDTH, SCREEN_HEIGHT);

				if (m_texture == NULL) {
					cout << "Could not create texture" << endl;
					cout << SDL_GetError() << endl;
					close();
					return false;
				}
			}

		}
	}

	return true;
}

void Screen::update() {

}

void Screen::close() {
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	cout <<"programm quit"<<endl;
	SDL_Quit();
}

} /* namespace pierre */
