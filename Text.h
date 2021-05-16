#pragma once

#include <SDL_ttf.h>
#include <string>

class Text
{
protected:
	SDL_Renderer* renderer; // SDL renderer used for drawing
	TTF_Font* font;	// stores the font that's being used
	SDL_Texture* text;	// stores the texture created from the font
	SDL_Rect rect;	// stores the position and dimensions of the text
	SDL_Colour colour;	// stores the colour of the text
	std::string txt;	// stores the actual text being displayed

public:
	Text(SDL_Renderer* _renderer, std::string _fontFile, std::string _text, int _fontSize, SDL_Colour _colour, int _x, int _y);	// constructor
	virtual ~Text();	// destructor

	virtual void Draw();	// draws button

	// setters
	void SetX(int _x) { rect.x = _x; }	// sets position
	void SetY(int _y) { rect.y = _y; }
	void SetText(std::string _text);	// updates text

	// getters
	int GetX() { return rect.x; }	// gets position
	int GetY() { return rect.y; }
	int GetW() { return rect.w; }	// gets dimensions
	int GetH() { return rect.h; }
	SDL_Rect& GetRect() { return rect; }	// gets the position and dimensions of the button
};
