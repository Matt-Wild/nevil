#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h)
{
	SDL_Surface* bmpFile = SDL_LoadBMP(_file.c_str());
	image = SDL_CreateTextureFromSurface(_renderer, bmpFile);
	SDL_FreeSurface(bmpFile);

	// initial position & w/h of sprite, based in incoming parameters
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;

	renderer = _renderer;
}

Sprite::~Sprite()
{
	if (image)
	{
		SDL_DestroyTexture(image);	// destroying the image
	}
}

void Sprite::Draw()
{
	if (image)
	{
		SDL_RenderCopy(renderer, image, NULL, &rect);	// drawing the image
	}
}

bool Sprite::IsCollidingWith(Sprite* other)
{
	return SDL_HasIntersection(&rect, &other->GetRect());	// tests if two sprites intersect
}

bool Sprite::Hovered()
{
	SDL_Rect mouseRect{};	// creates rect object for mouse
	mouseRect.w = 1;
	mouseRect.h = 1;

	SDL_GetMouseState(&mouseRect.x, &mouseRect.y);	// gets mouse position

	return SDL_HasIntersection(&rect, &mouseRect);	// checks if mouse rect is colliding with sprite rect
}
