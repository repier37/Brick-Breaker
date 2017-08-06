/*
 * Level.h
 *
 *  Created on: 6 août 2017
 *      Author: pierre
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include "Brick.h"

namespace pierre {

class Level {
public:
	std::vector<Brick> brickArr;
private:


	int levelNumb;


public:
	Level(SDL_Renderer* renderer);
	virtual ~Level();

	void draw(SDL_Renderer* renderer);
	void deleteLevel();
	void update(int i);

};



} /* namespace pierre */

#endif /* LEVEL_H_ */
