#pragma once

#include "Sprite.h"
#include "StatsHandler.h"

class Enemies
{
protected:
	SDL_Renderer* renderer;	// stores renderer
	StatsHandler* stats;	// stores the stats handler

	Sprite* laserIcon;	// stores laser icon
	Sprite* fireballIcon;	// stores fireball icon
	Sprite* redLaserIcon;	// stores red laser icon

public:
	Enemies(SDL_Renderer* _renderer, StatsHandler* _stats);	// constructor
	~Enemies();	// destructor

	void Draw();	// draw function
};
