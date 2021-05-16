#pragma once

#include "Sprite.h"
#include "Player.h"

class RedLaser
{
protected:
	bool present = false;	// currently active?
	int timer = 600;	// spawning timer
	int x = 0;	// x position

	SDL_Renderer* renderer;	// stores renderer, player and stats handler objects
	Player* player;
	StatsHandler* stats;

	Sprite* laser;	// sprite for laser

	Mix_Chunk* laserSound = Mix_LoadWAV("laser.wav");	// sound effect for laser

public:
	RedLaser(Player* _player, SDL_Renderer* _renderer, StatsHandler* _stats);	// constructor
	~RedLaser();	// destructor

	void Update();	// update function

	void Draw();	// draw function
};
