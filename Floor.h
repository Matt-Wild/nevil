#pragma once

#include "ScrollSprite.h"

class Floor : public ScrollSprite
{
public:
	Floor(Player* _player, SDL_Renderer* _renderer);	// constructor
};
