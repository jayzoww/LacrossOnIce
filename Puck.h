//
//  puck.h
//  gamefinal
//
//  Created by Peter Ju on 3/25/15.
//  Copyright (c) 2015 Peter Ju. All rights reserved.
//

#pragma once
#define PUCK_HEIGHT SCREEN_HEIGHT * 0.04
#define PUCK_WIDTH SCREEN_WIDTH * 0.035
#define PUCK_BOUNCE_FACTOR_Y .333
#define PUCK_BOUNCE_FACTOR_X .8
#define PUCK_DECEL_X SCREEN_WIDTH / 5
#define PUCK_ACEL_X SCREEN_WIDTH
#define PUCK_MAXVEL 800
#define OFF_SCREEN -20

#include "Kinematic.h"
#include "Platform.h"
#include "ScoreBoard.h"
#include "Net.h"
#include "vec2.h"
//#include "Player.h"
class Puck :
public Kinematic
{
public:
    Puck(vec2);
    Puck(SDL_Rect, ScoreBoard*);
    Puck(SDL_Rect, bool facing_right);
    Puck(vector<SDL_Rect>);
    Puck(SDL_Point, vector<SDL_Rect>);
    Puck(void);
	~Puck(void) {};
    vec2 vel;
//	int *player;
	bool possession;
	ScoreBoard *sb;
    
	void drop();
	void setVelocity(vec2 velocity);
    void update(float deltaTime);
    void draw();
	bool isPossessed();
    
    void OnCollisionEnter(Platform* p, CollisionFace cf, float deltaTime);
	void OnCollisionEnter(Net* n, CollisionFace cf, float deltaTime);


	void Up() {	}
	void Down() {}
	void Left() {}
	void Right() {}

	void UpUnpressed() {}
	void DownUnpressed() {}
	void LeftUnpressed() {}
	void RightUnpressed() {}

};
