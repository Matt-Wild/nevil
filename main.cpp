#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "StatsHandler.h"
#include "Floor.h"
#include "Background.h"
#include "Player.h"
#include "PlatformHandler.h"
#include "ScoreLine.h"
#include "HealthBar.h"
#include "ChaseLaser.h"
#include "Enemies.h"
#include "FireballHandler.h"
#include "RedLaser.h"

// function prototypes
void GameLoop(SDL_Window* window, SDL_Renderer* renderer);
bool MenuLoop(SDL_Window* window, SDL_Renderer* renderer);
bool DeathLoop(SDL_Window* window, SDL_Renderer* renderer, std::string score);
bool VictoryLoop(SDL_Window* window, SDL_Renderer* renderer);
bool PauseLoop(SDL_Window* window, SDL_Renderer* renderer);
void DrawMenuBackground(SDL_Renderer* renderer);

int main(int, char**)
{
	srand(time(NULL));	// seeding random number generation

	SDL_Window* window;
	SDL_Renderer* renderer;

	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try initialising TTF, log error and pause if fail
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try opening the mixer, log error and pause if fail
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
		system("pause");
		return 0;
	}

	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);	// sets music volume
	Mix_Music* bgm = Mix_LoadMUS("nevil.mp3");	// loading background music

	// try to create the window, log error and pause if fail
	window = SDL_CreateWindow("Nevil", 100, 100, 900, 900, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	// try to create the renderer, log error and pause if fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);	// allowing for transparency

	SDL_Surface* icon = SDL_LoadBMP("still.bmp");	// getting icon surface from image
	SDL_SetWindowIcon(window, icon);	// setting window icon
	SDL_FreeSurface(icon);	// icon surface no longer needed

	// this function acts as the start menu
	if (!MenuLoop(window, renderer))	// returns true if the user decides to exit the program
	{
		Mix_PlayMusic(bgm, -1);	// play background music

		// this function call goes into the actual game loop
		GameLoop(window, renderer);
	}

	Mix_FreeMusic(bgm);	// freeing memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	SDL_Quit();

	return 0;
}

void GameLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	StatsHandler* stats = new StatsHandler();
	
	SDL_Colour textColour = {255, 255, 255, 255};

	Text* scoreText = new Text(renderer, "arial.ttf", "SCORE:", 40, textColour, 10, 10);	// creating score text elements
	Text* scoreText2 = new Text(renderer, "arial.ttf", "0000000", 50, textColour, 10, 50);

	Text* heightText = new Text(renderer, "arial.ttf", "HEIGHT:", 40, textColour, 10, 110);	// creating height text elements
	Text* heightText2 = new Text(renderer, "arial.ttf", "0000000", 50, textColour, 10, 150);

	Text* enemiesText = new Text(renderer, "arial.ttf", "ENEMIES:", 40, textColour, 10, 250);	// creating height text elements

	Player* playerObj = new Player(stats, renderer);	// creates the player object
	Background* backgroundObj = new Background(playerObj, renderer);	// creates the background object
	Floor* floorObj = new Floor(playerObj, renderer);	// creating floor object
	PlatformHandler* platformHandler = new PlatformHandler(playerObj, renderer);	// creating platform handler
	ScoreLine* scoreLine = new ScoreLine(playerObj, renderer);	// creating score line
	HealthBar* healthBar = new HealthBar(playerObj, renderer);	// creating health bar
	ChaseLaser* chaseLaser = new ChaseLaser(playerObj, renderer);	// creating chase laser
	Enemies* enemies = new Enemies(renderer, stats);	// creating enemies object
	FireballHandler* fireballHandler = new FireballHandler(playerObj, renderer, stats);	// creating fireball handler
	RedLaser* redLaser = new RedLaser(playerObj, renderer, stats);	// creating red laser

	SDL_Rect hurtRect{ 300, 0, 600, 900 };	// rect for the hurt box

	bool endless = false;	// endless mode


	bool quit = false;
	SDL_Event e;

	while (!quit)
	{ // this is the main game loop

		Uint64 start = SDL_GetPerformanceCounter();	// used for regulating fps
		const Uint8* key = SDL_GetKeyboardState(NULL);	// getting keyboard

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		if (key[SDL_SCANCODE_ESCAPE])	// user pressed the escape key
			quit = PauseLoop(window, renderer);	// pause menu

		// start updating

		playerObj->PreUpdate();	// player update before platform collisions
		platformHandler->Update();	// updating platforms
		playerObj->PostUpdate();	// player update after platform collisions

		fireballHandler->Update();	// updating fireball handler
		redLaser->Update();	// updating red laser
	
		scoreLine->Update();	// updating score line
		chaseLaser->Update();	// updating chase laser

		stats->UpdateHeight(playerObj->GetYOffset());	// updating height
		scoreText2->SetText(stats->GetScore());	// updating score text
		heightText2->SetText(stats->GetHeight());	// updating height text

		if (stats->GetScoreInt() >= 100000 && !endless)	// has the player won?
		{
			quit = VictoryLoop(window, renderer);

			if (!quit)	// continue?
				endless = true;	// enable endless mode
		}

		if (playerObj->GetHealth() <= 0)	// has nevil died?
		{
			quit = DeathLoop(window, renderer, stats->GetScore());

			if (!quit)	// reset game
			{
				playerObj->Reset();	// resetting player
				stats->Reset();	// resetting stats
				chaseLaser->Reset();	// resetting chase laser
				platformHandler->Reset();	// resetting platform handler
				scoreLine->Reset();	// resetting score line
				fireballHandler->Reset();	// resetting fireballs
			}
		}

		// stop updating

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// sets background colour
		SDL_RenderClear(renderer);	// first clear the renderer

		// start drawing

		DrawMenuBackground(renderer);	// draws menu background

		healthBar->Draw();	// draw health bar
		enemies->Draw();	// draw enemy icons

		scoreText->Draw();	// drawing score text
		scoreText2->Draw();

		heightText->Draw();	// drawing height text
		heightText2->Draw();

		enemiesText->Draw();	// drawing enemies text

		backgroundObj->Draw();	// drawing the background
		floorObj->Draw();	// drawing the floor
		platformHandler->Draw();	// drawing platforms
		playerObj->Draw();	// drawing player
		fireballHandler->Draw();	// drawing fireballs
		redLaser->Draw();	// drawing red laser
		scoreLine->Draw();	// drawing score line
		chaseLaser->Draw();	// drawing chase laser

		if (playerObj->GetImmunity() > 0)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);	// sets colour for drawing the hurt box
			SDL_RenderFillRect(renderer, &hurtRect);	// draws hurt box
		}

		// stop drawing

		SDL_RenderPresent(renderer);	// update the screen

		Uint64 end = SDL_GetPerformanceCounter();	// used for regulating fps
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f; // how long the frame took
		if (floor(16.666f - elapsedMS) > 0)	// tests if delay needed
		{
			SDL_Delay(floor(16.666f - elapsedMS));	// cap fps to 60
		}
	}

	delete scoreText;	// freeing memory
	delete scoreText2;
	delete heightText;
	delete heightText2;
	delete playerObj;
	delete backgroundObj;
	delete floorObj;
	delete platformHandler;
	delete scoreLine;
	delete healthBar;
	delete chaseLaser;
	delete enemies;
	delete fireballHandler;
	delete redLaser;
}

bool MenuLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	Sprite* title = new Sprite(renderer, "title.bmp", 0, 0, 900, 250);	// creating title
	Sprite* tutorial = new Sprite(renderer, "tutorial.bmp", 0, 250, 900, 400);	// creating tutorial
	Button* startButton = new Button(renderer, "start_button.bmp", "start_button_active.bmp", 250, 785, 400, 100);	// creating start button

	bool start = false;
	bool quit = false;
	SDL_Event e;

	while (!start && !quit)
	{

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// start updating

		startButton->Update();
		if (startButton->GetEnabled())
		{
			start = true;	// ready to start game
		}

		// stop updating

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// sets background colour
		SDL_RenderClear(renderer);	// first clear the renderer

		// start drawing

		title->Draw();
		tutorial->Draw();
		startButton->Draw();

		// stop drawing

		SDL_RenderPresent(renderer);	// update the screen
	}

	delete title;	// freeing memory
	delete tutorial;
	delete startButton;

	return quit;	// returns if the user decides to exit the program
}

bool DeathLoop(SDL_Window* window, SDL_Renderer* renderer, std::string score)
{
	SDL_Colour textColour = { 255, 255, 255, 255 };
	Text* scoreText = new Text(renderer, "arial.ttf", "SCORE:", 80, textColour, 15, 450);
	Text* scoreText2 = new Text(renderer, "arial.ttf", score, 100, textColour, 15, 520);

	Mix_Chunk* loseSound = Mix_LoadWAV("lose.wav");	// sound effect for losing

	Mix_PlayChannel(-1, loseSound, 0);	// plays losing sound effect

	Sprite* gameOver = new Sprite(renderer, "lose.bmp", 126, 15, 648, 384);	// creating title
	Button* againButton = new Button(renderer, "again_button.bmp", "again_button_active.bmp", 485, 785, 400, 100);	// creating restart button
	Button* quitButton = new Button(renderer, "quit_button.bmp", "quit_button_active.bmp", 15, 785, 400, 100);	// creating quit button

	bool again = false;
	bool quit = false;
	SDL_Event e;

	while (!again && !quit)
	{

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// start updating

		againButton->Update();
		if (againButton->GetEnabled())
		{
			again = true;	// ready to restart
		}

		quitButton->Update();
		if (quitButton->GetEnabled())
		{
			quit = true;	// ready to quit
		}

		// stop updating

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// sets background colour
		SDL_RenderClear(renderer);	// first clear the renderer

		// start drawing

		gameOver->Draw();
		againButton->Draw();
		quitButton->Draw();
		scoreText->Draw();
		scoreText2->Draw();

		// stop drawing

		SDL_RenderPresent(renderer);	// update the screen
	}

	delete againButton;	// freeing memory
	delete gameOver;
	delete quitButton;
	delete scoreText;
	delete scoreText2;

	Mix_FreeChunk(loseSound);	// deletes losing sound effect

	return quit;	// returns if the user decides to exit the program
}

bool VictoryLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	Mix_Chunk* victorySound = Mix_LoadWAV("victory.wav");	// sound effect for winning
	Mix_VolumeChunk(victorySound, MIX_MAX_VOLUME / 8);	// setting victory sound volume

	Mix_PlayChannel(-1, victorySound, 0);	// plays winning sound effect

	Sprite* gameOver = new Sprite(renderer, "victory.bmp", 222, 15, 456, 384);	// creating title
	Button* endlessButton = new Button(renderer, "endless_button.bmp", "endless_button_active.bmp", 485, 785, 400, 100);	// creating restart button
	Button* quitButton = new Button(renderer, "quit_button.bmp", "quit_button_active.bmp", 15, 785, 400, 100);	// creating quit button

	bool again = false;
	bool quit = false;
	SDL_Event e;

	while (!again && !quit)
	{

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// start updating

		endlessButton->Update();
		if (endlessButton->GetEnabled())
		{
			again = true;	// ready to continue
		}

		quitButton->Update();
		if (quitButton->GetEnabled())
		{
			quit = true;	// ready to quit
		}

		// stop updating

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// sets background colour
		SDL_RenderClear(renderer);	// first clear the renderer

		// start drawing

		gameOver->Draw();
		endlessButton->Draw();
		quitButton->Draw();

		// stop drawing

		SDL_RenderPresent(renderer);	// update the screen
	}

	delete endlessButton;	// freeing memory
	delete gameOver;
	delete quitButton;

	Mix_FreeChunk(victorySound);	// deletes victory sound effect

	return quit;	// returns if the user decides to exit the program
}

bool PauseLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	Sprite* paused = new Sprite(renderer, "paused.bmp", 50, 0, 800, 400);	// creating title
	Button* resumeButton = new Button(renderer, "resume_button.bmp", "resume_button_active.bmp", 250, 585, 400, 100);	// creating restart button
	Button* quitButton = new Button(renderer, "quit_button.bmp", "quit_button_active.bmp", 250, 700, 400, 100);	// creating quit button

	bool resume = false;
	bool quit = false;
	SDL_Event e;

	while (!resume && !quit)
	{

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// start updating

		resumeButton->Update();
		if (resumeButton->GetEnabled())
		{
			resume = true;	// ready to continue
		}

		quitButton->Update();
		if (quitButton->GetEnabled())
		{
			quit = true;	// ready to quit
		}

		// stop updating

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// sets background colour
		SDL_RenderClear(renderer);	// first clear the renderer

		// start drawing

		paused->Draw();
		resumeButton->Draw();
		quitButton->Draw();

		// stop drawing

		SDL_RenderPresent(renderer);	// update the screen
	}

	delete resumeButton;	// freeing memory
	delete paused;
	delete quitButton;

	return quit;	// returns if the user decides to exit the program
}


void DrawMenuBackground(SDL_Renderer* renderer)
{
	SDL_Rect background{};	// creating rects for menu background
	SDL_Rect lineOuter{};
	SDL_Rect lineInner{};

	background.x = 0;	// setting position and dimensions for menu background components
	background.y = 0;
	background.w = 300;
	background.h = 900;

	lineOuter.x = 291;
	lineOuter.y = 0;
	lineOuter.w = 9;
	lineOuter.h = 900;

	lineInner.x = 294;
	lineInner.y = 0;
	lineInner.w = 3;
	lineInner.h = 900;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// drawing menu background components
	SDL_RenderFillRect(renderer, &background);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(renderer, &lineOuter);

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(renderer, &lineInner);
}
