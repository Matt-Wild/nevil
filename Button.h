#pragma once

#include "Sprite.h"
#include <string>
#include <SDL_mixer.h>

class Button
{
protected:
	SDL_Renderer* renderer; // SDL renderer used for drawing
	Sprite* inactive;	// the two sprites for the different button states
	Sprite* active;
	SDL_Rect rect;	// the position and dimensions of the button

	bool is_active = false;	// if the button is active or not
	bool enabled = false;	// if the button has been enabled

	Mix_Chunk* sound = Mix_LoadWAV("button.wav");

public:
	Button(SDL_Renderer* _renderer, std::string _fileInactive, std::string _fileActive, int _x, int _y, int _w, int _h); // constructor
	virtual ~Button(); // destructor

	virtual void Draw();	// draws button

	void Update();	// update function

	// setters
	void SetX(int _x) { rect.x = _x; }	// sets position
	void SetY(int _y) { rect.y = _y; }
	void SetEnabled(bool _enabled) { enabled = _enabled; }	// set enabled

	// getters
	int GetX() { return rect.x; }	// gets position
	int GetY() { return rect.y; }
	int GetW() { return rect.w; }	// gets dimensions
	int GetH() { return rect.h; }
	SDL_Rect& GetRect() { return rect; }	// gets the position and dimensions of the button
	bool GetEnabled() { return enabled; }	// gets if the button is enabled
};
