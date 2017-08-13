/*
 * Game.h
 *
 *  Created on: 13 août 2017
 *      Author: pierre
 */

#ifndef GAME_H_
#define GAME_H_
#include "Ball.h"
#include "SDL.h"
#include "Brick.h"
#include "Bar.h"

namespace pierre {

class Game {
private:

public:
	Game();
	virtual ~Game();
	bool newGame()
};

} /* namespace pierre */

#endif /* GAME_H_ */
