#include  "Menu_Button.h"
#include "Main_Menu.h"

bool Main_Menu::quit;

using namespace std;

////The window we'll be rendering to
//SDL_Window* gWindow = NULL;

//The window renderer
//SDL_Renderer* gRenderer = NULL;

//Buttons objects
vector<Menu_Button> gButtons;

//Mouse button sprites


//Sprite sheet array
const string spriteSheetList[] = {"2Player.png","Practice.png","Settings.png","Quit.png"};

Main_Menu::Main_Menu()
{

}

Main_Menu::~Main_Menu()
{

}

bool Main_Menu::loadMedia()
{

    //Loading success flag
    bool success = true;

    for(int i=0;i<TOTAL_BUTTONS;i++){
        Menu_Button tempButton;
            //tempButton.gButtonsspriteSheet.push_back(sprite);
        gButtons.push_back(tempButton);
        for(int j = 0; j < BUTTON_SPRITE_TOTAL; j++ ){
            gButtons[i].gSpriteClips.push_back(SDL_Rect());
        }
    }

    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
//        LTexture sprite;
//        //Load sprites
//        if( !sprite.loadFromFile( spriteSheetList[i] ) )
//        {
//            printf( "Failed to load button sprite texture!\n" );
//            success = false;
//        }
        if( !gButtons[i].gButtonSpriteSheet[i].loadFromFile( spriteSheetList[i] ) )
        {
            printf( "Failed to load button sprite texture!\n" );
            success = false;
        }
        else
        {
            //Set sprites
            for( int j = 0; j < BUTTON_SPRITE_TOTAL; j++ )
            {
                gButtons[i].gSpriteClips[ j ].x = 0;
                gButtons[i].gSpriteClips[ j ].y = j * 50;
                gButtons[i].gSpriteClips[ j ].w = BUTTON_WIDTH;
                gButtons[i].gSpriteClips[ j ].h = BUTTON_HEIGHT;
            }

            //Set buttons middle of screen
            gButtons[i].setPosition( SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.5) - BUTTON_HEIGHT/2 + (BUTTON_SPACING*i) );
            gButtons[i].setButtonType(i);

        }
    }

    return success;
}

void Main_Menu::start ()
{
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
    }
    else
    {
        //Main loop flag
        quit = false;

        //Event handler
        SDL_Event e;
		
		LTexture backgroundScreen;
		backgroundScreen.loadFromFile("main menu.png");
		
        //While application is running
        while( !quit )
        {
	

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                //Handle button events
                for( int i = 0; i < TOTAL_BUTTONS; ++i )
                {
                    gButtons[ i ].handleEvent( &e );
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor( SDLGI::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( SDLGI::gRenderer );
			
			backgroundScreen.render(0,0);
			
            //Render buttons
            for( int i = 0; i < TOTAL_BUTTONS; i++ )
            {
                gButtons[i].render(i);
            }



            //Update screen
//               LTexture button1;
//                button1.loadFromRenderedText( "Hockey Game Thing", { 0, 0, 0 } );
//                button1.render( ( SCREEN_WIDTH - button1.getWidth() ) / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT*0.9));
            SDL_RenderPresent( SDLGI::gRenderer );
        }
    }



}

