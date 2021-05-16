#pragma once

#include "Sprite.h"
#include "Player.h"

class HealthBar
{
protected:
	SDL_Renderer* renderer;	// stores renderer
	Player* player;	// stores player

	Sprite* full;	// sprite for full heart
	Sprite* half;	// sprite for half heart

public:
	HealthBar(Player* _player, SDL_Renderer* _renderer);	// constructor
	~HealthBar();	// destructor

	void Draw();	// draw function
};
