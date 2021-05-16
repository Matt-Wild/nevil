#pragma once

#include "AnimScrollSprite.h"

class Fireball
{
protected:
	float y;	// stores the y position of the fireball
	float vy = 1.0f;	// stores the velocity of the fireball

	AnimScrollSprite* fireball;	// stores the fireball sprite

public:
	Fireball(Player* _player, SDL_Renderer* _renderer, int _x, int _y);	// constructor
	~Fireball();	// destructor

	void Update();	// update function

	void Draw();	// draw function

	bool CollidingWith(SDL_Rect _rect);	// returns if colliding with given rect

	// getters
	float GetY() { return y; }	// gets the y position
};
