#pragma once
#define NET_WIDTH SCREEN_WIDTH * 0.02
#define NET_HEIGHT  SCREEN_HEIGHT * 0.3
#define NET_VEL SCREEN_HEIGHT/3
#define NET_PUSH_VEL 100 // prevents puck from getting stuck to bottom of net
#include "Kinematic.h"
#include "LTexture.h"

class Net :
	public Kinematic
{
public:
	Net(SDL_Rect, bool facingRight, float top, float bot, Team tm);
	~Net(void);
	vec2 vel;
	bool dir; // 0 down, 1 up
	float top_limit;
	float bottom_limit;
	Team t;

	Team getTeam();
	
	void update(float deltaTime);
	void draw();

	void Up() {};
	void Down() {}
	void Left() {};
	void Right() {};

	void UpUnpressed() {};
	void DownUnpressed() {};
	void LeftUnpressed() {};
	void RightUnpressed() {};

private:
	LTexture* gnet=NULL;
	
};