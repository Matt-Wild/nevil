#include "HealthBar.h"

HealthBar::HealthBar(Player* _player, SDL_Renderer* _renderer)
{
	player = _player;	// getting player and renderer objects
	renderer = _renderer;
	
	full = new Sprite(_renderer, "heart.bmp", 0, 0, 90, 90);	// creates sprite for full heart
	half = new Sprite(_renderer, "half_heart.bmp", 0, 0, 90, 90);	// creates sprite for half heart
}

HealthBar::~HealthBar()
{
	delete full;	// freeing memory
	delete half;
}

void HealthBar::Draw()
{
	int health = player->GetHealth();	// get player health

	if (health >= 2)
	{
		full->SetX(5);	// setting heart position
		full->SetY(800);

		full->Draw();	// drawing full heart
	}
	else if (health >= 1)
	{
		half->SetX(5);	// setting heart position
		half->SetY(800);

		half->Draw();	// drawing full heart
	}

	if (health >= 4)
	{
		full->SetX(100);	// setting heart position
		full->SetY(800);

		full->Draw();	// drawing full heart
	}
	else if (health >= 3)
	{
		half->SetX(100);	// setting heart position
		half->SetY(800);

		half->Draw();	// drawing full heart
	}

	if (health >= 6)
	{
		full->SetX(195);	// setting heart position
		full->SetY(800);

		full->Draw();	// drawing full heart
	}
	else if (health >= 5)
	{
		half->SetX(195);	// setting heart position
		half->SetY(800);

		half->Draw();	// drawing full heart
	}
}
