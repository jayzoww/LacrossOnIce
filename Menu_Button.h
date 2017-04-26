#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "LTexture.h"
#include "Game.h"
#include "Practice.h"
#include "Main_Menu.h"
#include "Settings_Menu.h"

enum MenuButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_TOTAL = 3,
    OPTION_ONE = 0,
    OPTION_TWO = 1,
    OPTION_THREE = 2,
};

//Button constants
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;
const int TOTAL_BUTTONS = 4;
const int BUTTON_SPACING = 75;



//The menu buttons
class Menu_Button
{
public:
    //Initializes internal variables
    Menu_Button();

    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    void handleEvent( SDL_Event* e );

    //Shows button sprite
    void render(int buttonType);

    void setButtonType(int type);

    //static LTexture gButtonSpriteSheet[ TOTAL_BUTTONS ];

    LTexture gButtonSpriteSheet[TOTAL_BUTTONS];

    vector<SDL_Rect> gSpriteClips;

    //static SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];

private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    MenuButtonSprite mCurrentSprite;

    int buttonType;

    int optionCount;


};
