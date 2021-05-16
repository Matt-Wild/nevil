#pragma once

#include "ScrollSprite.h"

class Platform : public ScrollSprite
{
protected:
	std::string addon = "NONE";	// stores if the platform has an addon

	bool InXRange();	// tests if in x range of player
	bool Collidable();	// returns if nevil can currently collide with the platform

public:
	Platform(Player* _player, SDL_Renderer* _renderer, int _y);	// constructor

	void Update();	// update function

	std::string GetAddon() { return addon; }	// gets if the platform has an addon
};
