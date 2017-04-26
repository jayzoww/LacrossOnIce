//
//  SDLGInit.cpp
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#include "SDLInit.h"
#include "SoundManager.h"

SDL_Window* SDLGI::gWindow;
SDL_Renderer* SDLGI::gRenderer;

bool SDLGI::init()
{
	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// music
		MySoundManager::Instance()->load("icehockeymusic.ogg", "music", SOUND_MUSIC);
		MySoundManager::Instance()->load("ambientsound.ogg", "ambience", SOUND_MUSIC);
		// sfx
		MySoundManager::Instance()->load("goal.wav", "goalhorn", SOUND_SFX);
		MySoundManager::Instance()->load("goalcheer.wav", "goalcheer", SOUND_SFX);
		MySoundManager::Instance()->load("hit.wav", "bodycheck", SOUND_SFX);
		MySoundManager::Instance()->load("shot.wav", "shot", SOUND_SFX);
		MySoundManager::Instance()->load("longgoalhorn.wav", "endgamebuzzer", SOUND_SFX);
	}

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		SDLGI::gWindow = SDL_CreateWindow( "CISC320 Project PaintedLady", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TYPE );
		if( SDLGI::gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			SDLGI::gRenderer = SDL_CreateRenderer( SDLGI::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( SDLGI::gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( SDLGI::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

//bool loadMedia()
//{
//	//Loading success flag
//	bool success = true;
//	
//	//Load press texture
//	if( !gDotTexture.loadFromFile( "dot.png" ) )
//	{
//		printf( "Failed to load dot texture!\n" );
//		success = false;
//	}
//	
//	return success;
//}

void SDLGI::close()
{
	//	//Free loaded images
	//	gDotTexture.free();

	//Destroy window
	SDL_DestroyRenderer( SDLGI::gRenderer );
	SDL_DestroyWindow( SDLGI::gWindow );
	SDLGI::gWindow = NULL;
	SDLGI::gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool SDLGI::checkCollision( SDL_Rect a, SDL_Rect b )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}