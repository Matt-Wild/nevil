#include "RedLaser.h"

RedLaser::RedLaser(Player* _player, SDL_Renderer* _renderer, StatsHandler* _stats)
{
	player = _player;	// getting player, renderer, stats handler objects
	renderer = _renderer;
	stats = _stats;

	laser = new Sprite(renderer, "laser_red.bmp", 0, 0, 50, 900);	// getting laser image

	Mix_VolumeChunk(laserSound, MIX_MAX_VOLUME / 8);	// setting laser sound volume
}

RedLaser::~RedLaser()
{
	delete laser;	// freeing memory

	Mix_FreeChunk(laserSound);	// deletes laser sound effect
}

void RedLaser::Update()
{
	if (present)	// currently active?
	{
		if (player->GetX() <= x + 50 && player->GetX() + 50 >= x)	// colliding with player?
		{
			player->RemoveHealth(1);	// damage player
		}

		timer--;	// reduce timer

		if (timer <= 0)	// run out of time?
		{
			timer = 600 + rand() % 600;	// timer for inactive phase

			present = false;	// disappear
		}
	}
	else
	{
		if (stats->GetStage() >= 3)	// high enough difficult to spawn laser?
		{
			timer--;	// reduce timer

			if (timer <= 0)	// is timer ready?
			{
				Mix_PlayChannel(-1, laserSound, 0);	// plays laser sound effect

				timer = 180;	// timer for active phase
				present = true;	// present laser

				x = rand() % 550 + 300;	// getting for x position for laser
				laser->SetX(x);	// updating laser sprite position
			}
		}
	}
}

void RedLaser::Draw()
{
	if (present)	// is laser present?
		laser->Draw();	// draw laser
}
