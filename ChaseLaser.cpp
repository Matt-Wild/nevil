#include "ChaseLaser.h"

ChaseLaser::ChaseLaser(Player* _player, SDL_Renderer* _renderer)
{
	player = _player;	// getting player and renderer objects
	renderer = _renderer;
	
	laser = new ScrollSprite(player, renderer, "laser.bmp", 300, 900, 600, 50);	// creating laser sprite
}

void ChaseLaser::Update()
{
	if (chasing)	// is laser chasing player?
	{
		float speedAdj = (y - (player->GetY() + 48)) / 100.0f;	// calculating speed adjustment
		if (speedAdj < 0)	// if speed adjustment is negative, disregard it
			speedAdj = 0;

		y -= baseSpeed + speedAdj;	// moving laser

		if (player->GetY() > y)	// player caught in laser
		{
			player->RemoveHealth(1);	// damage player
			player->SetVY(-30.0f);	// shooting player upwards
		}
	}
	else 
	{
		if (player->GetYOffset() > 50)	// player starting to move
		{
			chasing = true;	// being to chase
		}
	}
}

void ChaseLaser::Draw()
{
	laser->SetY(y);	// updating sprite position
	laser->Draw();	// drawing laser
}

void ChaseLaser::Reset()
{
	chasing = false;	// resetting values
	y = 900.0f;
}
