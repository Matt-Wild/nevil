#pragma once

#include <vector>
#include "Fireball.h"

class FireballHandler
{
protected:
	SDL_Renderer* renderer;	// stores renderer object
	Player* player;	// stores player object
	StatsHandler* stats;	// stores the stats handler

	std::vector<Fireball*> fireballs;	// stores the fireballs

public:
	FireballHandler(Player* _player, SDL_Renderer* _renderer, StatsHandler* _stats);	// constructor
	~FireballHandler();	// destructor

	void Update();	// update function

	void Draw();	// draw function

	void DespawnFireballs();	// despawns fireballs that are no longer needed
	void SpawnFireballs();	// spawns new fireballs

	void Reset();	// resetting fireballs
};
