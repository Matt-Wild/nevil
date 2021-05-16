#pragma once

#include "Sprite.h"
#include "Player.h"

class ScrollSprite : public Sprite
{
protected:
	Player* player;

public:
	ScrollSprite(Player* _player, SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);	// constructor

	void Draw();	// draw function
};
