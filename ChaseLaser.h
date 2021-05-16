#pragma once

#include "ScrollSprite.h"

class ChaseLaser
{
protected:
	bool chasing = false;	// stores if the laser is chasing the player
	float x = 300.0f, y = 900.0f, baseSpeed = 1.0f;	// stores the position of the laser and it's base speed

	SDL_Renderer* renderer;	// stores the renderer and the player objects
	Player* player;

	ScrollSprite* laser;

public:
	ChaseLaser(Player* _player, SDL_Renderer* _renderer);	// constructor

	void Update();	// update function

	void Draw();	// draw function

	void Reset();	// resets laser
};
