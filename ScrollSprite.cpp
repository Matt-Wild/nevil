#include "ScrollSprite.h"

ScrollSprite::ScrollSprite(Player* _player, SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h)
	: Sprite(_renderer, _file, _x, _y, _w, _h)	// call to sprite ctor
{
	player = _player;	// getting player object
}

void ScrollSprite::Draw()
{
	if (image)
	{
		rect.y += player->GetYOffset();	// corrects y position for drawing

		SDL_RenderCopy(renderer, image, NULL, &rect);	// drawing the image

		rect.y -= player->GetYOffset();	// corrects y position for collisions etc
	}
}
