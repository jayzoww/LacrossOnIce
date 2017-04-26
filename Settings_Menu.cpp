
#include "Menu_Button.h"
#include "Settings_Menu.h"
#include "SDLInit.h"

bool Settings_Menu::quit;

using namespace std;

////The window we'll be rendering to
//SDL_Window* gWindow = NULL;

//The window renderer
//SDL_Renderer* gRenderer = NULL;

//Buttons objects
vector<Menu_Button> sButtons;

//Mouse button sprites


//Sprite sheet array
const string spriteSheetList[] = {"Resolution.png","Controls.png","Return.png"};

Settings_Menu::Settings_Menu()
{

}

Settings_Menu::~Settings_Menu()
{

}

bool Settings_Menu::loadMedia()
{

    //Loading success flag
    bool success = true;

    for(int i=0;i<3;i++){
        Menu_Button tempButton;
            //tempButton.sButtonspriteSheet.push_back(sprite);
        sButtons.push_back(tempButton);
        for(int j = 0; j < BUTTON_SPRITE_TOTAL; j++ ){
            sButtons[i].gSpriteClips.push_back(SDL_Rect());
        }
    }

    for (int i = 0; i < 3; i++)
    {
//        LTexture sprite;
//        //Load sprites
//        if( !sprite.loadFromFile( spriteSheetList[i] ) )
//        {
//            printf( "Failed to load button sprite texture!\n" );
//            success = false;
//        }
        if( !sButtons[i].gButtonSpriteSheet[i].loadFromFile( spriteSheetList[i] ) )
        {
            printf( "Failed to load button sprite texture!\n" );
            success = false;
        }
        else
        {
            //Set sprites
            for( int j = 0; j < BUTTON_SPRITE_TOTAL; j++ )
            {
                sButtons[i].gSpriteClips[ j ].x = 0;
                sButtons[i].gSpriteClips[ j ].y = j * 50;
                sButtons[i].gSpriteClips[ j ].w = BUTTON_WIDTH;
                sButtons[i].gSpriteClips[ j ].h = BUTTON_HEIGHT;
            }

            //Set buttons middle of screen
            sButtons[i].setPosition( SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.5) - BUTTON_HEIGHT/2 + (BUTTON_SPACING*i) );
            sButtons[i].setButtonType(i+4);

        }
    }

    return success;
}

void Settings_Menu::start ()
{
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
    }
    else
    {
                    printf("here");
        //Main loop flag
        quit = false;

        //Event handler
        SDL_Event e;
		
		
		LTexture backgroundScreen;
		backgroundScreen.loadFromFile("settings menu.png");

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }

                //Handle button events
                for( int i = 0; i < 3; ++i )
                {
                    sButtons[ i ].handleEvent( &e );
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor( SDLGI::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( SDLGI::gRenderer );
			
			backgroundScreen.render(0,0);

            //Render buttons
            for( int i = 0; i < 3; i++ )
            {
                sButtons[i].render(i);
            }



            //Update screen
//               LTexture button1;
//                button1.loadFromRenderedText( "Hockey Game Thing", { 0, 0, 0 } );
//                button1.render( ( SCREEN_WIDTH - button1.getWidth() ) / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT*0.9));
            SDL_RenderPresent( SDLGI::gRenderer );
        }
    }



}

