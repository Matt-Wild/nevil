#include "Floor.h"

Floor::Floor(Player* _player, SDL_Renderer* _renderer)
	: ScrollSprite(_player, _renderer, "floor.bmp", 300, 850, 600, 50)	// call to scroll sprite ctor
{

}
