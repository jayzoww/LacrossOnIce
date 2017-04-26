#pragma once

//Using SDL, SDL_image, standard IO, and strings a
#include <stdio.h>
#include <string>
#include "SDLInit.h"

#include "Menu_Button.h"

using namespace std;

class Main_Menu{
public:
    Main_Menu();
    ~Main_Menu();
    void start();
    void close();
    static bool quit;
private:
    bool loadMedia();


};
