#include "Background.h"

Background::Background(Player* _player, SDL_Renderer* _renderer)
{
	player = _player;	// getting player object
	bg1 = new Sprite(_renderer, "bg1.bmp", 300, 0, 600, 900);	// creating background 1 sprite
	bg2 = new Sprite(_renderer, "bg2.bmp", 300, 0, 600, 900);	// creating background 2 sprite
}

Background::~Background()
{
	delete bg1;	// deletes sprites
}

void Background::Draw()
{
	int yOffset = player->GetYOffset() / 2;	// getting y offset

	bg1->SetY(bg1->GetY() + yOffset);	// correcting y position for drawing
	bg1->Draw();	// draws sprite
	bg1->SetY(bg1->GetY() - yOffset);	// correcting y position for collisions etc

	if (yOffset > 0)	// does background 2 need drawing?
	{
		int baseOffset = ((yOffset / 900) * -900) - 900;

		bg2->SetY(baseOffset + yOffset);	// correcting y position for drawing
		bg2->Draw();	// draws sprite

		if (yOffset >= 900)	// fill in gap in background when at this height
		{
			baseOffset += 900;
			bg2->SetY(baseOffset + yOffset);	// correcting y position for drawing
			bg2->Draw();	// draws sprite
		}
	}
}
