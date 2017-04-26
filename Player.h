#pragma once
//#define PLAYER_HEIGHT SCREEN_HEIGHT * 0.12
#define PLAYER_HEIGHT 60

//#define PLAYER_WIDTH SCREEN_WIDTH * 0.04
#define PLAYER_WIDTH 32
#define PLAYER_BOUNCE_FACTOR_Y .333
#define PLAYER_BOUNCE_FACTOR_X .333
#define PLAYER_DECEL_X SCREEN_WIDTH / 5
#define PLAYER_ACEL_X SCREEN_WIDTH
#define PLAYER_TURNACCEL_X SCREEN_WIDTH*2
#define PLAYER_JUMP_GRAV GRAVITY * 0.5
#define PLAYER_DOWN_GRAV GRAVITY * 2
#define PLAYER_MAXVEL SCREEN_WIDTH * 0.75 //TODO fix hard code
#define PLAYER_JUMPVEL -SCREEN_WIDTH * 0.75 //TODO fix hard code
#define PLAYER_JUMPBOUNDARY PLAYER_JUMPVEL * 0.4
#define PLAYER_DOWNTIME 1
#define PLAYER_KNOCKBOUNDARY 800
#define PLAYER_HIT_THRESH 700
#define PLAYER_HEAD_BOUNCE 0.8

#define MAX_SHOTX SCREEN_WIDTH * 1.2 
#define MAX_SHOTY SCREEN_HEIGHT *0.8


#include "Kinematic.h"
#include "LTexture.h"
#include "Platform.h"
#include "Puck.h"
#include "vec2.h"
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
class Player :
	public Kinematic
{
public:
	Player(vec2);
	Player(SDL_Rect);
	Player(SDL_Rect, bool facing_right, vector<Platform*> platforms, Team team);
	Player(vector<SDL_Rect>);
	Player(SDL_Point, vector<SDL_Rect>);
	Player(void);
	~Player(void);
	vec2 vel;
	Puck* puck;
	bool hasPuck;
	bool shoot_pressed;
	bool knocked_down;
	float knockTime;
	float shotTime;
	bool grounded;
	bool leftWall;
	bool rightWall;
	vector<Platform*> platforms;
	

	void update(float deltaTime);
	void draw();
	void Up();
	void Down();
	void Left();
	void Right();
	void losePuck();
	
	void OnCollisionEnter(Platform* p, CollisionFace cf, float deltaTime);
	static void OnCollisionEnter(Player* a, Player* b, CollisionFace cf, float deltaTime);
	void OnCollisionEnter(Puck* p, CollisionFace cf, float deltaTime);


	void Shoot();
	void KnockedDown();

	void UpUnpressed();
	void DownUnpressed();
	void LeftUnpressed();
	void RightUnpressed();
	void ShootUnpressed();
private:
	Team t;
	vector<LTexture*> pics;
	LTexture* lastPic;
	
};