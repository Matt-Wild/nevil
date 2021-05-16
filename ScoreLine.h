#pragma once

#include <SDL.h>
#include "Player.h"

class ScoreLine
{
protected:
	SDL_Rect lineRect{ 300, -650, 600, 8};	// rect struct for drawing the line

	int y = -650;	// y position

	SDL_Renderer* renderer;	// stores renderer
	Player* player;	// stores player object

public:
	ScoreLine(Player* _player, SDL_Renderer* _renderer);	// constructor

	void Update();	// update function

	void Draw();	// draw function

	void Reset() { y = -650; }	// resetting score line
};
