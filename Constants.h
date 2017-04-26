//
//  Constants.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-20.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#ifndef prototype_Constants_h
#define prototype_Constants_h

#define MACOSX 1
#define WINDOWSOS 0
#define OS WINDOWSOS

// resosultion macros

#define RES1080P 1080
#define RES900P 900
#define RES720P 720
#define RES480P 480
#define RES240P 240
#define RESORIGINAL 540

// aspect ratio macros
#define CONVERTASPCTRATIO169 16/9
#define CONVERTASPCTRATIO1610 16/10
#define CONVERTASPCTRATIO43 4/3
#define ASPECRATIO CONVERTASPCTRATIO169

// screen pixel height and width macros
#define _SCREENHEIGHT_ RESORIGINAL
#define _SCREENWIDTH_ (_SCREENHEIGHT_ * ASPECRATIO)

// window type macro
//#define _WINDOWTYPE_ SDL_WINDOW_FULLSCREEN

// Game constants
#define GAMELENGTH 60
#define WINNINGSCORE 10

#endif
