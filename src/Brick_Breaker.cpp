//============================================================================
// Name        : Brick_Breaker.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Screen.h"
#include "Menu.h"
#include "Game.h"

using namespace std;
using namespace pierre;

int main(int argc, char **argv) {
	Screen mainScreen;

	if (!mainScreen.init()) {
		cout << "Could not initialize the main window" << endl;
		return 0;
	}

	Menu menu(mainScreen.m_renderer);
	std::cout << "menu loaded" << std::endl;
	/*Ball testBall;
	SDL_Point testPoint;
	testPoint.x = 150;
	testPoint.y = 150;
	testBall.init(mainScreen.m_renderer,testPoint);*/


	SDL_Event user_event;

	bool execute = true;
	bool gameOn = true;
	while (execute) {
		// on dessine le menu

		menu.drawMenu(mainScreen.m_renderer);
		//std::cout << "menu drawn" << std::endl;
		mainScreen.render(menu.getTexture());

		/*
		 game.startGame(mainScreen.m_renderer);

		 game.mainRoutine(mainScreen.m_renderer,user_event);
		 std::cout << "game routine done" << std::endl;
		 */

		//On traite les input utilisateurs
		switch (menu.watchEvent(user_event)) {
		case 0: {
			gameOn=true;
			Game game(mainScreen.m_renderer);
			std::cout << "game loaded" << std::endl;
			game.startGame(mainScreen.m_renderer);
			while (gameOn && execute) {
				switch (game.mainRoutine(mainScreen.m_renderer, user_event)) {
				case 0:
					gameOn = true;
					break;
				case 1:
					gameOn = false;
					break;
				case 2:
					execute = false;
					break;
				default:
					break;
				}
				mainScreen.render(game.getTexture());
			}
			gameOn = false;
			break;
		}

		case 1:
			execute = false;
			break;
		case 10:
			execute = false;
			break;
		case -1:
			break;
		default:
			break;

		}

	}

	mainScreen.close();

	return 0;
}
