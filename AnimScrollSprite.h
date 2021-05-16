#pragma once

#include "ScrollSprite.h"

class AnimScrollSprite : public ScrollSprite
{
private:
	int cellsInRow, cellsInCol, currentRow, currentCol;	// details about the spritesheet
	
	SDL_Rect cellRect;	// which section of the spritesheet to draw

	int timer, speed;	// animation timing

public:
	AnimScrollSprite(Player* _player, SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h, int _cellsPerRow, int _cellsPerCol, int _speed);	//constructor

	void Update();	// update function

	void Draw();	// draw function
};
