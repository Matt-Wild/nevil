#pragma once

#include <vector>
#include "Player.h"
#include "Platform.h"

class PlatformHandler
{
protected:
	int maxPlatforms = 16, distance = 200, despawnDistance = 1500;	// sets the amount of platforms to have at any one time and the distance to put them between and how far away a platform needs to be before being deleted
	int genPos = 850 - distance;	// generation position for the platforms

	Player* player;	// stores player object
	SDL_Renderer* renderer;	// stores renderer

	ScrollSprite* scoreAddon;	// stores sprite for score addon
	ScrollSprite* jumpAddon;	// stores sprite for jump addon
	ScrollSprite* healthAddon;	// stores sprite for health addon

	std::vector<Platform*> platforms;	// stores platforms currently in the scene

public:
	PlatformHandler(Player* _player, SDL_Renderer* _renderer);	// constructor
	~PlatformHandler();	// destructor

	void TrimPlatforms();	// gets rid of platforms that are no longer needed
	void GeneratePlatforms();	// generates platforms
	void Update();	// update function
	void Draw();	// draws platforms

	void Reset();	// resets platforms
};
