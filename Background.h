#pragma once

#include "Sprite.h"
#include "Player.h"

class Background
{
protected:
	Player* player;	// stores player object
	Sprite* bg1;	// background image 1
	Sprite* bg2;	// background image 2
	
public:
	Background(Player* _player, SDL_Renderer* _renderer);	// constructor
	virtual ~Background();	// destructor

	virtual void Draw();	// draws background
};


