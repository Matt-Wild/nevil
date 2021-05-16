#include "Button.h"
#include "Sprite.h"

Button::Button(SDL_Renderer* _renderer, std::string _fileInactive, std::string _fileActive, int _x, int _y, int _w, int _h)
{
	// initial position & w/h of sprite, based in incoming parameters
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;

	renderer = _renderer;

	inactive = new Sprite(renderer, _fileInactive, rect.x, rect.y, rect.w, rect.h);
	active = new Sprite(renderer, _fileActive, rect.x, rect.y, rect.w, rect.h);
}

Button::~Button()
{
	delete inactive;	// destroying the sprites
	delete active;
	
	Mix_FreeChunk(sound);	// destroying the sound object
}

void Button::Draw()
{
	if (is_active)
	{
		active->Draw();	// draws active image
	}
	else
	{
		inactive->Draw();	// draws inactive image
	}
}

void Button::Update()
{
	if (inactive->Hovered())	// checks if hovered
	{
		if (!is_active)	// checks if newly hovered over
		{
			Mix_PlayChannel(-1, sound, 0);	// plays sound effect
			is_active = true;	// updates is_active value
		}

		SDL_PumpEvents();
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) // checks if left mouse button is pressed
		{
			enabled = true;	// enabled button
		}
	}
	else
	{
		is_active = false;
	}
}
