#pragma once
#include "GameObject.h"

class Kinematic :
	public GameObject
{
public:
	Kinematic(vec2);
	Kinematic(SDL_Rect);
	Kinematic(vector<SDL_Rect>);
	Kinematic(SDL_Point, vector<SDL_Rect>);
	Kinematic(void);
	~Kinematic(void);
	vec2 vel;

	virtual void update(float deltaTime) = 0;
	virtual void Up() = 0;
	virtual void Down() = 0;
	virtual void Left() = 0;
	virtual void Right() = 0;

	virtual void UpUnpressed() = 0;
	virtual void DownUnpressed() = 0;
	virtual void LeftUnpressed() = 0;
	virtual void RightUnpressed() = 0;
protected:
	bool facing_right;
	bool left_pressed;
	bool right_pressed;
	bool up_pressed;
	bool down_pressed;
};