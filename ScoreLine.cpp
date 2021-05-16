#include "ScoreLine.h"

ScoreLine::ScoreLine(Player* _player, SDL_Renderer* _renderer)
{
	player = _player;	// getting player and renderer
	renderer = _renderer;
}

void ScoreLine::Update()
{
	if (player->GetY() <= y + 8)	// player caught up with score line
	{
		player->GainScore(rand() % 500 + 1000);	// reward player
		y -= 2600;	// move line
	}
}

void ScoreLine::Draw()
{
	lineRect.y = y + player->GetYOffset();	// correcting y position for drawing

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);	// setting colour for drawing
	SDL_RenderFillRect(renderer, &lineRect);	// drawing line
}
