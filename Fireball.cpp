#include "Fireball.h"

Fireball::Fireball(Player* _player, SDL_Renderer* _renderer, int _x, int _y)
{
	y = _y;	// setting fireball position

	fireball = new AnimScrollSprite(_player, _renderer, "fireball.bmp", _x, _y, 20, 30, 5, 1, 5);	// creating fireball sprite
}

Fireball::~Fireball()
{
	delete fireball;	// freeing memory
}

void Fireball::Update()
{
	y += vy;	// updating position
	fireball->SetY(y);	// updating sprite position
	fireball->Update();	// updating sprite animation
}

void Fireball::Draw()
{
	fireball->Draw();	// drawing sprite
}

bool Fireball::CollidingWith(SDL_Rect _rect)
{
	return SDL_HasIntersection(&fireball->GetRect(), &_rect);	// returns if there's an intersection
}
