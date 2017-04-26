//
//  GameObject.cpp
//  prototype
//
//  Created by Matthew Lapinsky on 2015-03-11.
//  Copyright (c) 2015 Matthew Lapinsky. All rights reserved.
//

#include "GameObject.h"
#include "SDLInit.h"

GameObject::GameObject(){

}

GameObject::GameObject(vec2 p): pos(p){
}

GameObject::GameObject(SDL_Rect c): collider(c) {
}

GameObject::GameObject(vec2 p, SDL_Rect c) : pos(p), collider(c){
}

void GameObject::setPosition(vec2 p) {
	pos = p;
}

vec2 GameObject::getPosition() {
	return pos;
}

SDL_Rect GameObject::getCollider(){
	return collider;
}

CollisionFace GameObject::checkCollision(GameObject* g1, GameObject* g2) {
	
	SDL_Rect r1 = g1->collider;
	r1.x = g1->pos.x;
	r1.y = g1->pos.y;

	SDL_Rect r2 = g2->collider;
	r2.x = g2->pos.x;
	r2.y = g2->pos.y;

	SDL_Rect fillRect = { r1.x, r1.y, r1.w, r1.h };
	SDL_SetRenderDrawColor(SDLGI::gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(SDLGI::gRenderer, &fillRect);

	SDL_Rect fillRect2 = { r2.x, r2.y, r2.w, r2.h };
	SDL_SetRenderDrawColor(SDLGI::gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(SDLGI::gRenderer, &fillRect2);

	/*
	vec2 top_left_1 = vec2(r1.x, r1.y);
	vec2 top_right_1 = vec2(r1.x + r1.w, r1.y);
	vec2 bot_left_1 = vec2(r1.x, r1.y + r1.h);
	vec2 bot_right_1 = vec2(r1.x + r1.w, r1.y + r1.h);

	vec2 top_left_2 = vec2(r2.x, r2.y);
	vec2 top_right_2 = vec2(r2.x + r1.w, r1.y);
	vec2 bot_left_2 = vec2(r2.x, r2.y + r2.h);
	vec2 bot_right_2 = vec2(r2.x + r2.w, r2.y + r2.h);
	*/
	bool xOverlap = false;
	bool yOverlap = false;
	int xOverlapDistance = 0;
	int yOverlapDistance = 0;
	int xDistance = r1.x - r2.x;
	int yDistance = r1.y - r2.y;
	if (xDistance <= 0) {		//r1 on left
		if (-xDistance <= r1.w) {	//At this point, xDistance < 0, -xDistance makes term positive. Distance between 2 is less than total width
			xOverlap = true;
			xOverlapDistance = -r1.w - xDistance;
		}
	}
	else {	//r2 on left
		if (xDistance <= r2.w) {	//If distance between the 2 is less than total width.
			xOverlap = true;
			xOverlapDistance = r2.w - xDistance;
		}
	}
	if (yDistance <= 0) {	//r1 is above	
		if (-yDistance <= r1.h) {	//At this point, yDistance < 0, -yDistance makes term positive.  If distance between is less than total height
			yOverlap = true;
			yOverlapDistance = -r1.h - yDistance;
		}
	}
	else {	
		if (yDistance <= r2.h) {	//If distance between the 2 is less than total height.
			yOverlap = true;
			yOverlapDistance = r2.h - yDistance;
		}
	}

	//cout << xOverlapDistance << "\t" << yOverlapDistance << "\t";
	//cout << xOverlap << "\t" << yOverlap << "\t";
	if (!(xOverlap && yOverlap)) {
		return NONE;	//no collision
	}
	else {
		//collision
		if (abs(xOverlapDistance) <= abs(yOverlapDistance)) {	// left-right collision
			if (r1.x > r2.x) {
				return LEFT;	//r1 is colliding on its left face (r1 is to the right of r2)
			}
			else {
				return RIGHT;	//r1 is colliding on its right face (r1 is to the left of r2)
			}
		}
		else {	//top-bottom collision
			if (r1.y > r2.y) {
				return TOP;		//r1 is colliding on its top face (r1 is below r2)
			}
			else {
				return BOTTOM;	//r1 is colliding on its bottom face (r1 is above r2)
			}
		}
	}

	return NONE;	//Should never get here
}