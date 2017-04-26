//
//  SDLInit.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#ifndef __prototype__SDLInit__
#define __prototype__SDLInit__

#include <iostream>
#include "Constants.h"
#include "SoundManager.h"
#if OS==MACOSX

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#else // assume windows

#include <SDL.h>
#include <SDL_image.h>

#endif

//Screen dimension constants
#ifndef _SCREENWIDTH_
const int SCREEN_WIDTH = 1280;
//const int SCREEN_WIDTH = 1900;
#else
const int SCREEN_WIDTH = _SCREENWIDTH_;
#endif

#ifndef _SCREENHEIGHT_
const int SCREEN_HEIGHT = 720;
//const int SCREEN_HEIGHT = 1000;
#else
const int SCREEN_HEIGHT = _SCREENHEIGHT_;
#endif

#ifndef _WINDOWTYPE_
const Uint32 WINDOW_TYPE = SDL_WINDOW_SHOWN;
#else
const Uint32 WINDOW_TYPE = _WINDOWTYPE_;
#endif

using namespace std;

// SDL wrapping for initializing graphics rendering and window generation
class SDLGI{

public:
	//Starts up SDL and creates window
	static bool init();

	////Loads media
	//bool loadMedia(); ?? may move to individual Textures

	//Frees media and shuts down SDL
	static void close();

	//Box collision detector
	static bool checkCollision( SDL_Rect a, SDL_Rect b );

//The window we'll be rendering to
	static SDL_Window* gWindow;//= NULL;

//The window renderer
	static SDL_Renderer* gRenderer;//= NULL;

};
#endif /* defined(__prototype__SDLInit__) */
