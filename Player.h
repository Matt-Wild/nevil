#pragma once

#include <vector>
#include <SDL_mixer.h>
#include "Sprite.h"
#include "StatsHandler.h"

class Player
{
protected:
	bool onGround, onPlatform;	// stores if nevil is current standing on the ground or a platform
	int yOffset = 0;	// y offset for drawing scrolling objects
	int health = 6;	// storing health value for nevil
	int immunity = 0;	// immunity counter
	float x = 576.0f, y = 802.0f;	// starting position
	float max_vx = 8.0f, max_vy = 40.0f, drag = 0.2f, gravity = 0.45f, jumpStrength = 20.0f, vx = 0.0f, vy = 0.0f;	// values for max velocity, drag, gravity, jump strength and velocity

	StatsHandler* stats;

	Sprite* currentSprite;	// stores the current sprite

	Sprite* still;	// stores the sprite for still nevil
	Sprite* jump;	// stores the sprite for jumping nevil
	Sprite* left;	// stores the sprite for left nevil
	Sprite* right;	// stores the sprite for right nevil

	Mix_Chunk* jumpSound = Mix_LoadWAV("jump.wav");	// sound effect for jumping
	Mix_Chunk* pingSound = Mix_LoadWAV("ping.wav");	// sound effect for getting score
	Mix_Chunk* hurtSound = Mix_LoadWAV("punch.wav");	// sound effect for getting hurt

	void UpdateCurrentSprite();	// updates current sprite
	void Jump();	// jumping mechanic
	void OnGround();	// returns if the player is standing on the ground
	void ImplementDrag();	// slows down horizontal velocity over time
	void ImplementGravity();	// causes the player to fall due to gravity
	void LimitVelocity();	// limits velocity of player
	void UpdatePosition();	// updates position based on velocity
	void LimitXPosition();	// limits player position on the x axis
	void UpdateSprite();	// updates sprite position
	void UpdateOffset();	// updates y offset
	
public:
	Player(StatsHandler* _statsHandler, SDL_Renderer* _renderer);	// constructor
	virtual ~Player();	// destructor

	virtual void Draw();	// draws player

	void PreUpdate();	// update function before platform collisions
	void PostUpdate();	// update function after platform collisions

	void GainScore(int _amount);	// player gaining score
	void AddHealth(int _amount);	// increase player health
	void RemoveHealth(int _amount);	// decreasse player health

	void Reset();	// reset nevil

	// getters
	float GetX() { return x; }	// returns x position
	float GetY() { return y; }	// returns y position
	float GetVX() { return vx; }	// returns x velocity
	float GetVY() { return vy; }	// returns y velocity
	int GetHealth() { return health; }	// get player health
	int GetYOffset() { return yOffset; };	// gets y offset for drawing objects
	int GetImmunity() { return immunity; }	// return immunity counter
	SDL_Rect GetRect() { return currentSprite->GetRect(); }	// returns rect of current sprite

	// setters
	void SetVX(float _vx) { vx = _vx; }	// sets x velocity
	void SetVY(float _vy) { vy = _vy; }	// sets y velocity
	void SetJumpStrength(float _strength) { jumpStrength = _strength; }	// sets jump strength
	void SetOnPlatform(bool _standing) { onPlatform = _standing; }	// sets if nevil is standing on a platform
};
