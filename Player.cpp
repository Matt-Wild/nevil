#include "Player.h"
#include <iostream>

Player::Player(StatsHandler* _statsHandler, SDL_Renderer* _renderer)
{
	stats = _statsHandler;	// getting stats handler

	still = new Sprite(_renderer, "still.bmp", x, y, 48, 48);	// creates sprite for still phase
	jump = new Sprite(_renderer, "jump.bmp", x, y, 48, 48);	// creates sprite for jump phase
	left = new Sprite(_renderer, "left.bmp", x, y, 48, 48);	// creates sprite for left phase
	right = new Sprite(_renderer, "right.bmp", x, y, 48, 48);	// creates sprite for right phase
	
	Mix_VolumeChunk(jumpSound, MIX_MAX_VOLUME / 16);	// setting jump sound volume
	Mix_VolumeChunk(pingSound, MIX_MAX_VOLUME / 8);	// setting ping sound volume
	Mix_VolumeChunk(hurtSound, MIX_MAX_VOLUME / 4);	// setting ping sound volume
}

Player::~Player()
{
	delete still;	// deletes sprites

	Mix_FreeChunk(jumpSound);	// deletes jump sound effect
}

void Player::UpdateCurrentSprite()
{
	if (onGround || onPlatform)	// checks if standing on a surface
	{
		if (vx > 0)
			currentSprite = right;
		else if (vx < 0)
			currentSprite = left;
		else
			currentSprite = still;
	}
	else
	{
		currentSprite = jump;	// mid air sprite (jumping)
	}
}

void Player::Jump()
{
	Mix_PlayChannel(-1, jumpSound, 0);	// plays jump sound effect
	vy = -jumpStrength;	// boosts the player up
}

void Player::OnGround()
{
	if (y == 802.0f)	// player is standing on the starting platform
	{
		onGround = true;
	}
	else
	{
		onGround = false;
	}
}

void Player::ImplementDrag()
{
	if (vx > drag)	// checks if full drag can be applied
	{
		vx -= drag;	// applied full drag
	}
	else if (vx < -drag)
	{
		vx += drag;
	}
	else
	{
		vx = 0;	// if full drag cannot be applied, just resets velocity
	}
}

void Player::ImplementGravity()
{
	vy += gravity;	// implementing gravity
}

void Player::LimitVelocity()
{
	if (vx > max_vx)	// checks if x velocity is illegal
	{
		vx = max_vx;	// corrects x velocity
	}
	else if (vx < -max_vx)
	{
		vx = -max_vx;
	}

	if (vy > max_vy)	// checks if y velocity is illegal
	{
		vy = max_vy;	// corrects y velocity
	}
	else if (vy < -max_vy)
	{
		vy = -max_vy;
	}

	if (vy > 0)	// collisions with platforms can only happen when falling
	{
		if (y + vy > 802)	// colliding with ground
		{
			vy = 802.0f - y;	// correcting downward velocity to land on ground
		}
	}
}

void Player::UpdatePosition()
{
	x += vx;	// updating position based on velocity
	y += vy;
}

void Player::LimitXPosition()
{
	if (x > 852)	// checks if out of bounds
	{
		x = 852.0f;	// corrects position and velocity
		vx = 0.0f;
	}
	else if (x < 300)
	{
		x = 300.0f;
		vx = 0.0f;
	}
}

void Player::UpdateSprite()
{
	currentSprite->SetX(x);	// updating sprite position
	currentSprite->SetY(y);
}

void Player::UpdateOffset()
{
	if (y < 600)	// testing if y offset is necessary
	{
		if (y > 0)	// different rounding is needed for position and negative positions
			yOffset = 600 - floor(y);	// calculating new y offset
		else
			yOffset = 600 - ceil(y);	// calculating new y offset
	}
	else
	{
		yOffset = 0;	// reset if y offset is not necessary
	}
}

void Player::Draw()
{
	currentSprite->SetY(currentSprite->GetY() + yOffset);	// correcting sprite position for drawing
	currentSprite->Draw();	// draws sprite
	currentSprite->SetY(currentSprite->GetY() - yOffset);	// correcting sprite position for collisions etc
}

void Player::PreUpdate()
{
	if (immunity > 0)	// does nevil have immunity?
		immunity--;	// decrease immunity

	OnGround();	// updates if nevil is on the ground
	UpdateCurrentSprite();	// updates current sprite
	ImplementDrag();	// implementing drag to velocity
	ImplementGravity();	// implementing gravity

	bool standing = onGround || onPlatform;	// is nevil standing on a surface?

	const Uint8* key = SDL_GetKeyboardState(NULL);	// getting keyboard

	// arrow key movement behaviour
	if (key[SDL_SCANCODE_LEFT])
		vx -= 0.6f;

	if (key[SDL_SCANCODE_RIGHT])
		vx += 0.6f;

	if (standing)	// up and down controls only possible when standing on a platform
	{
		if (key[SDL_SCANCODE_UP])
			Jump();	// jumping mechanic

		if (key[SDL_SCANCODE_DOWN] && y < 700)
			y += 1.0f;	// moves player down skipping a platform
	}
	else
	{
		jumpStrength = 20.0f;	// reseting jump strength
	}

	LimitVelocity();	// limiting velocity to max values

	onPlatform = false;	// will be overriden if nevil collides with a platform
}

void Player::PostUpdate()
{
	UpdatePosition();	// updating position based on velocity
	LimitXPosition();	// limiting movement on the x axis
	UpdateSprite();	// updating sprite
	UpdateOffset();	// updating y offset
}

void Player::GainScore(int _amount)
{
	stats->AddScore(_amount);	// add score
	Mix_PlayChannel(-1, pingSound, 0);	// plays ping sound effect
}

void Player::AddHealth(int _amount)
{
	health += _amount;	// adding health
	Mix_PlayChannel(-1, pingSound, 0);	// plays ping sound effect

	if (health > 6)	// if health too high?
	{
		health = 6;	// set health to maximum
	}
}

void Player::RemoveHealth(int _amount)
{
	if (health > 0 && immunity == 0)	// has health left?
	{
		health -= _amount;	// reduce health

		if (health < 0)	// removed too much health?
		{
			health = 0;	// reset health to 0
		}

		if (health != 0)
			Mix_PlayChannel(-1, hurtSound, 0);	// plays hurt sound effect

		immunity = 60;
	}
}

void Player::Reset()
{
	health = 6;	// reseting values
	yOffset = 0;
	immunity = 0;
	x = 576.0f;
	y = 802.0f;
	vx = 0.0f;
	vy = 0.0f;
}
