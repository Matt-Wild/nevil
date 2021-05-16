#include "AnimScrollSprite.h"

AnimScrollSprite::AnimScrollSprite(Player* _player, SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h, int _cellsInRow, int _cellsInCol, int _speed)
	: ScrollSprite(_player, _renderer, _file, _x, _y, _w, _h) // call to ScrollSprite ctor
{
	cellsInRow = _cellsInRow;	// getting cell details
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 0;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	timer = 0;	// getting animation details
	speed = _speed;
}

void AnimScrollSprite::Update()
{
	timer++;	// increasing timer

	if (timer >= speed) // next cell?
	{
		timer = 0; // reset timer

		currentCol++; // go to column
		if (currentCol > cellsInRow - 1) // go back first column?
		{
			currentCol = 0;

			currentRow++; // go to next row
			if (currentRow > cellsInCol - 1) // back to first row?
			{
				currentRow = 0;
			}
		}
	}
}

void AnimScrollSprite::Draw()
{
	cellRect.x = currentCol * cellRect.w;	// calculating which cell to draw
	cellRect.y = currentRow * cellRect.h;

	if (image)
	{
		rect.y += player->GetYOffset();	// corrects y position for drawing

		SDL_RenderCopy(renderer, image, &cellRect, &rect);	// drawing the image

		rect.y -= player->GetYOffset();	// corrects y position for collisions etc
	}
}
