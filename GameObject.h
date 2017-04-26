//
//  GameObject.h
//  prototype
//
//  Created by Matthew Lapinsky on 2015-03-11.
//  Copyright (c) 2015 Matthew Lapinsky. All rights reserved.
//

#ifndef __prototype__GameObject__
#define __prototype__GameObject__
#define GRAVITY vec2(0, 9.8 * SCREEN_WIDTH / 4)
#include "SDLInit.h"
#include <iostream>
#include <vector>
#include "vec2.h"

using namespace std;

enum Team{
	HOME,
	AWAY
};

enum CollisionFace {
	NONE,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

class GameObject{
public:
	GameObject();
	GameObject(vec2);
	GameObject(SDL_Rect);
	GameObject(vec2, SDL_Rect);
	virtual ~GameObject() {}

	virtual void draw() = 0;
	void setPosition(vec2);
	vec2 getPosition();
	SDL_Rect getCollider();
	static CollisionFace checkCollision(GameObject* g1, GameObject* g2);
protected:
	SDL_Rect collider;
	vec2 pos;
};

#endif /* defined(__prototype__GameObject__) */