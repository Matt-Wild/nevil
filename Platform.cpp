#include "Platform.h"

Platform::Platform(Player* _player, SDL_Renderer* _renderer, int _y)
	: ScrollSprite(_player, _renderer, "platform.bmp", rand() % 450 + 300, _y, 150, 20)	// calls scroll sprite ctor
{
	int addonPicker = rand() % 100;	// random picker for platform addon

	if (addonPicker > 80)
	{
		addon = "SCORE";	// platform given the score addon
	}
	else if (addonPicker > 70)
	{
		addon = "JUMP";	// platform given the jump addon
	}
	else if (addonPicker > 68)
	{
		addon = "HEALTH";	// platform given the health addon
	}
}

bool Platform::InXRange()
{
	if (player->GetX() + 48 >= GetX() && player->GetX() <= GetX() + 150)	// tests if in x range
	{
		return true;
	}

	return false;
}

bool Platform::Collidable()
{
	if (InXRange() && GetY() >= player->GetY() + 48)	// checks if platform in aligned for collision with player and player is above platform
	{
		return true;
	}

	return false;
}

void Platform::Update()
{
	if (Collidable())	// can player collide with this platform on this frame?
	{
		if (player->GetY() + player->GetVY() + 48 > GetY())	// player colliding with platform
		{
			player->SetVY((float)GetY() - player->GetY() - 48.0f);	// correcting velocity so player lands on platform
			player->SetOnPlatform(true);	// makes sure player object knows it's standing on a platform

			if (addon == "SCORE")	// does platform have the score addon?
			{
				player->GainScore(rand() % 400 + 100);	// granting player score
				addon = "NONE";	// getting rid of score addon
			}
			else if (addon == "JUMP")	// does platform have the jump addon?
			{
				player->SetJumpStrength(40.0f);	// doubling player jump strength
			}
			else if (addon == "HEALTH")	// does platform have the health addon?
			{
				if (player->GetHealth() < 6)	// is player below max health?
				{
					player->AddHealth(1);	// increasing player health
					addon = "NONE";	// getting rid of score addon
				}
			}
		}
	}
}
