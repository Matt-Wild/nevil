#include "FireballHandler.h"

FireballHandler::FireballHandler(Player* _player, SDL_Renderer* _renderer, StatsHandler* _stats)
{
	player = _player;	// getting objects for the player, renderer and stats handler
	renderer = _renderer;
	stats = _stats;
}

FireballHandler::~FireballHandler()
{
	for (int i = 0; i < fireballs.size(); i++)	// cycling through fireballs
	{
		Fireball* currentFireball = fireballs[i];	// getting current fireball

		fireballs.erase(fireballs.begin() + i);	// removing fireball from vector
		i--;	// correcting index

		delete currentFireball;	// freeing memory
	}
}

void FireballHandler::DespawnFireballs()
{
	for (int i = 0; i < fireballs.size(); i++)	// cycling through fireballs
	{
		Fireball* currentFireball = fireballs[0];	// getting current fireball

		if (currentFireball->GetY() - player->GetY() > 1500)	// does fireball need to be despawned?
		{
			fireballs.erase(fireballs.begin() + i);	// removing fireball from vector
			i--;	// correcting index

			delete currentFireball;	// freeing memory
		}
	}
}

void FireballHandler::SpawnFireballs() 
{
	int spawnAmount = stats->GetStage() - 1;	// getting amount that needs to be spawned
	if (spawnAmount < 0)
	{
		spawnAmount = 0;
	}

	while (fireballs.size() < spawnAmount)	// repeat until all fireballs are present
	{
		fireballs.push_back(new Fireball(player, renderer, rand() % 580 + 300, player->GetY() - 1000 - rand() % 500));	// creating new fireball
	}
}

void FireballHandler::Update()
{
	DespawnFireballs();	// making sure to regenerate necessary fireballs
	SpawnFireballs();

	for (int i = 0; i < fireballs.size(); i++)	// cycling through fireballs
	{
		Fireball* currentFireball = fireballs[i];	// getting current fireball
		currentFireball->Update();	// updating fireball

		if (currentFireball->CollidingWith(player->GetRect()))	// colliding with player?
		{
			player->RemoveHealth(1);	// hurts player

			fireballs.erase(fireballs.begin() + i);	// removes fireball from vector
			i--;	// correcting index

			delete currentFireball;	// freeing memory
		}
	}
}

void FireballHandler::Draw()
{
	for (int i = 0; i < fireballs.size(); i++)	// cycling through fireballs
	{
		fireballs[i]->Draw();	// drawing fireball
	}
}

void FireballHandler::Reset()
{
	for (int i = 0; i < fireballs.size(); i++)	// cycling through fireballs
	{
		Fireball* currentFireball = fireballs[i];	// getting current fireball

		fireballs.erase(fireballs.begin() + i);	// removing fireball from vector
		i--;	// correcting index

		delete currentFireball;	// freeing memory
	}
}
