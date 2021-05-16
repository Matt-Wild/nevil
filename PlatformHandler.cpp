#include "PlatformHandler.h"

PlatformHandler::PlatformHandler(Player* _player, SDL_Renderer* _renderer)
{
	player = _player;	// getting player and renderer
	renderer = _renderer;

	scoreAddon = new ScrollSprite(_player, _renderer, "platform_score.bmp", 0, 0, 150, 5);	// creates sprite for score addon
	jumpAddon = new ScrollSprite(_player, _renderer, "platform_jump.bmp", 0, 0, 150, 5);	// creates sprite for jump addon
	healthAddon = new ScrollSprite(_player, _renderer, "platform_health.bmp", 0, 0, 150, 5);	// creates sprite for jump addon
}

PlatformHandler::~PlatformHandler()
{
	delete scoreAddon;	// freeing memory
	delete jumpAddon;
	delete healthAddon;

	for (int i = 0; i < platforms.size(); i++)	// cycling through platforms
	{
		Platform* currentPlatform = platforms[i];	// getting current platform

		platforms.erase(platforms.begin() + i);	// removing platform from vector
		i--;	// correcting index

		delete currentPlatform;	// freeing memory
	}
}

void PlatformHandler::TrimPlatforms()
{
	for (int i = 0; i < platforms.size(); i++)	// cycling through platforms
	{
		Platform* currentPlatform = platforms[i];	// getting current platform

		if (currentPlatform->GetY() - player->GetY() > despawnDistance)	// checking if platform needs to be destroyed
		{
			platforms.erase(platforms.begin() + i);	// removing platform from vector
			i--;	// decreasing index

			delete currentPlatform;	// freeing memory
		}
	}
}

void PlatformHandler::GeneratePlatforms()
{
	while (platforms.size() < maxPlatforms)	// cycles until all the platforms needed have been created
	{
		platforms.push_back(new Platform(player, renderer, genPos));	// appends platform to vector

		genPos -= distance;	// gets y position for next platform
	}
}

void PlatformHandler::Update()
{
	TrimPlatforms();	// deletes platforms that are no longer needed
	GeneratePlatforms();	// makes sure enough platforms exist

	for (int i = 0; i < platforms.size(); i++)	// cycling through platforms
	{
		platforms[i]->Update();	// updating platform
	}
}

void PlatformHandler::Draw()
{
	for (int i = 0; i < platforms.size(); i++)	// cycling through platforms
	{
		if (platforms[i]->GetAddon() == "SCORE")	// need to draw score addon?
		{
			scoreAddon->SetX(platforms[i]->GetX());	// setting position for score addon
			scoreAddon->SetY(platforms[i]->GetY() - 5);

			scoreAddon->Draw();	// drawing score addon
		}
		else if (platforms[i]->GetAddon() == "JUMP")	// need to draw jump addon?
		{
			jumpAddon->SetX(platforms[i]->GetX());	// setting position for jump addon
			jumpAddon->SetY(platforms[i]->GetY() - 5);

			jumpAddon->Draw();	// drawing jump addon
		}
		else if (platforms[i]->GetAddon() == "HEALTH")	// need to draw health addon?
		{
			healthAddon->SetX(platforms[i]->GetX());	// setting position for jump addon
			healthAddon->SetY(platforms[i]->GetY() - 5);

			healthAddon->Draw();	// drawing jump addon
		}

		platforms[i]->Draw();	// drawing platform
	}
}

void PlatformHandler::Reset()
{
	for (int i = 0; i < platforms.size(); i++)	// cycling through platforms
	{
		Platform* currentPlatform = platforms[i];	// getting current platform

		platforms.erase(platforms.begin() + i);	// removing platform from vector
		i--;	// correcting index

		delete currentPlatform;	// freeing memory
	}

	genPos = 850 - distance;	// resetting gen position
}
