#include "main.h"

int main(int argc, char* args[])
{
    if( !SDLGI::init() )
    {
        cout << ( "Failed to initialize!\n" ) << endl;
    }
    else
    {
            Main_Menu g = Main_Menu();
            g.start();

//        Settings_Menu g = Settings_Menu();
//        g.start();

        SDLGI::close();
    }
    return 0;
}
