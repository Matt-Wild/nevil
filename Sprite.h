#pragma once

#include <SDL.h>
#include <string>

class Sprite
{
protected:
	SDL_Renderer* renderer; // SDL renderer used for drawing
	SDL_Texture* image; // image used by this sprite
	SDL_Rect rect;	// the position and dimensions of the sprite

public:
	Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h); // constructor
	virtual ~Sprite(); // destructor

	virtual void Draw();	// draws sprite

	bool IsCollidingWith(Sprite* other);	// returns if the sprite is colliding with the other

	bool Hovered();	// returns if the sprite is hovered over by the mouse

	// setters
	void SetX(int _x) { rect.x = _x; }	// sets position
	void SetY(int _y) { rect.y = _y; }

	// getters
	int GetX() { return rect.x; }	// gets position
	int GetY() { return rect.y; }
	int GetW() { return rect.w; }	// gets dimensions
	int GetH() { return rect.h; }
	SDL_Rect& GetRect() { return rect; }	// gets the position and dimensions of the sprite
};
