/*
 * Level.cpp
 *
 *  Created on: 6 août 2017
 *      Author: pierre
 */

#include "Level.h"
#include <iostream>

namespace pierre {

Level::Level(SDL_Renderer* renderer) {
	levelNumb = 1;
	int rowNumb=5;
	int colNumb = 20;
	int brickW=50;
	int brickH=20;
	int xPadding=10;
	int yPadding=10;
	int count=0;

	//Brick brick(0, 0, renderer);
	//SDL_QueryTexture(brick.m_texture,NULL,NULL,&brickW,&brickH);
	//std::cout<<brickW<<"  "<<brickH<<std::endl;


	for (int y=10; y<rowNumb*(brickH+yPadding); y+= (brickH+yPadding)){
		//std::cout<<"y: "<<y<<std::endl;
		for (int x = 10; x<colNumb*(brickW+xPadding);x+=brickW+xPadding){
			//std::cout<<x<<"   "<<y<<std::endl;
			//std::cout<<"x: "<<x<<std::endl;

			Brick brick(x, y, renderer);
			brickArr.push_back(brick);

			//std::cout<<"Brick created: "<<brickArr[count].m_x<<"    "<<brickArr[count].m_y<<std::endl;
			count++;
		}

	}
	//std::cout<<"Brick created: "<<brickArr[count-1].m_x<<"    "<<brickArr[count].m_y<<std::endl;

}

Level::~Level() {
	// TODO Auto-generated destructor stub
}


void Level::draw(SDL_Renderer* renderer){
	for (unsigned int i=0; i< brickArr.size();i++){
		//std::cout<<i<<std::endl;
		//std::cout<<"Brick to be rendered: "<<brickArr[i].m_x<<"    "<<brickArr[i].m_y<<std::endl;
		SDL_RenderCopy(renderer, brickArr[i].m_texture, NULL, &(brickArr[i].m_hitbox));
		//std::cout<<SDL_GetError()<<std::endl;
	}

}


void Level::deleteLevel(){
	for (unsigned int i=0; i< brickArr.size();i++){;
			brickArr[i].deleteBrick();
		}
}

void Level::update(int i){
	if (brickArr[i].lostPV()<=0){
		brickArr.erase(brickArr.begin()+i);
	}

}


} /* namespace pierre */
