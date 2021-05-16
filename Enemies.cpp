#include "Enemies.h"

Enemies::Enemies(SDL_Renderer* _renderer, StatsHandler* _stats)
{
	renderer = _renderer;	// getting renderer
	stats = _stats;	// getting stats handler

	laserIcon = new Sprite(_renderer, "laser_icon.bmp", 15, 300, 90, 90);	// creates sprite for laser
	fireballIcon = new Sprite(_renderer, "fireball_icon.bmp", 15, 400, 90, 90);	// creates sprite for fireball
	redLaserIcon = new Sprite(_renderer, "laser_red_icon.bmp", 15, 500, 90, 90);	// creates sprite for red laser
}

Enemies::~Enemies()
{
	delete laserIcon;	// freeing memory
	delete fireballIcon;
	delete redLaserIcon;
}

void Enemies::Draw()
{
	int stage = stats->GetStage();	// gets difficult level

	if (stage >= 1)
	{
		laserIcon->Draw();	// draws laser icon
	}

	if (stage >= 2)
	{
		fireballIcon->SetX(15);	// setting position for fireball icon
		fireballIcon->Draw();	// drawing fireball icon
	}

	if (stage >= 3)
	{
		fireballIcon->SetX(40);	// setting position for fireball icon
		fireballIcon->Draw();	// drawing fireball icon

		redLaserIcon->Draw();	// drawing red laser icon
	}

	if (stage >= 4)
	{
		fireballIcon->SetX(65);	// setting position for fireball icon
		fireballIcon->Draw();	// drawing fireball icon
	}

	if (stage >= 5)
	{
		fireballIcon->SetX(90);	// setting position for fireball icon
		fireballIcon->Draw();	// drawing fireball icon
	}
}
