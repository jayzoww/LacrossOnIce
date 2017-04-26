#pragma once

//Using SDL, SDL_image, standard IO, and strings a
#include "SDLInit.h"
#include <string>

#include "Menu_Button.h"

using namespace std;

class Settings_Menu{
public:
    Settings_Menu();
    ~Settings_Menu();
    void start();
    void close();
	static bool quit;

private:
    bool loadMedia();

};
