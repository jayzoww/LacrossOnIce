//
//  LTexture.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
 and may not be redistributed without written permission.*/

#ifndef __prototype__LTexture__
#define __prototype__LTexture__

#include <stdio.h>


#include "SDLInit.h"


#include <string>
#include <vector>

using namespace std;


//Texture wrapper class
class LTexture
{
public:

	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile( std::string path );

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	#ifdef _SDL_TTF_H
	//Creates image from font string
	static TTF_Font *gFont;
    #endif
	static vector<LTexture> textures;

	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;


};


#endif /* defined(__prototype__LTexture__) */
