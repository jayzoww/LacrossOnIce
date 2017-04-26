#pragma once
#include "GameObject.h"
class Platform :
	public GameObject
{
private:
public:
	Platform(void);
	Platform(SDL_Rect);
	~Platform(void) {}
	void draw(void);
};
