//
//  puck.cpp
//  gamefinal
//
//  Created by Peter Ju on 3/25/15.
//  Copyright (c) 2015 Peter Ju. All rights reserved.
//

#include "Puck.h"

Puck::Puck(SDL_Rect r, ScoreBoard* s)  {
    pos = vec2(r.x, r.y);
    vel = vec2(0, 0);
    collider = r;
	possession = false;
	sb = s;
 
}

void Puck::update(float deltaTime) {
	if (!possession){
		vel = vel + GRAVITY * deltaTime;

		if (vel.x >= PUCK_MAXVEL){
			//	vel.x = PUCK_MAXVEL;
		}
		if (vel.x <= -PUCK_MAXVEL){
			//	vel.x = -PUCK_MAXVEL;
		}

		if (vel.x > 0.1) {	// moving right
			vel.x -= PUCK_DECEL_X * deltaTime;
		}
		else if (vel.x < -0.1) { // moving right
			vel.x += PUCK_DECEL_X * deltaTime;
		}
		else {
			vel.x = 0;	//Stop. Reduces possible infinite flipping between "decelerating" left and right
		}


		//cout << vel.x << endl;
		pos = pos + vel * deltaTime;

		//TODO remove after adding collisions
		if (pos.x >= SCREEN_WIDTH - collider.w){
			pos.x = SCREEN_WIDTH - collider.w;
			vel.x = 0;
		}
		if (pos.x <= 0){
			pos.x = 0;
			vel.x = 0;
		}
		if (pos.y >= SCREEN_HEIGHT - collider.h - SCREEN_HEIGHT / 10) {
			pos.y = SCREEN_HEIGHT - collider.h - SCREEN_HEIGHT / 10;
		}
		if (pos.y <= 0){
			pos.y = 0;
			vel.y = 0;
		}
	}
	else {
		pos = vec2(OFF_SCREEN, OFF_SCREEN);
	}
}

void Puck::draw() {
    SDL_Rect fillRect = { static_cast<int>(pos.x), static_cast<int>(pos.y), collider.w, collider.h};
    SDL_SetRenderDrawColor( SDLGI::gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( SDLGI::gRenderer, &fillRect );
}

bool Puck::isPossessed(){
	return possession;
}

void Puck::OnCollisionEnter(Platform* p, CollisionFace cf, float deltaTime) {
    
    switch (cf) {
        case TOP:
 //           cout << "TOP" << endl;
            pos.y = p->getPosition().y + p->getCollider().h;
            vel.y = PUCK_BOUNCE_FACTOR_Y * abs(vel.y);
            break;
        case LEFT:
//            cout << "LEFT" << endl;
            pos.x = p->getPosition().x + p->getCollider().w;
            vel.x = PUCK_BOUNCE_FACTOR_X * abs(vel.x);
            break;
        case RIGHT:
 //           cout << "RIGHT" << endl;
            pos.x = p->getPosition().x - collider.w;
            vel.x = PUCK_BOUNCE_FACTOR_X * -abs(vel.x);
            break;
        case BOTTOM:
//            cout << "BOTTOM" << endl;
            pos.y = p->getPosition().y - collider.h;
			vel.y = PUCK_BOUNCE_FACTOR_Y * -abs(vel.y);
            //vel.y = 0;
            break;
        default:
//            cout << "NONE" << endl;
            break;
    }
    
}

void Puck::OnCollisionEnter(Net* n, CollisionFace cf, float deltaTime) {

	switch (cf) {
	case TOP:
//		cout << "TOP" << endl;
		pos.y = n->getPosition().y + n->getCollider().h;
		vel.y = PUCK_BOUNCE_FACTOR_Y * abs(vel.y) + NET_PUSH_VEL;
		break;
	case LEFT:
	case RIGHT:
//		cout << "RIGHT" << endl;
		sb->changeScore(n->getTeam());
		drop();
		break;
	case BOTTOM:
//		cout << "BOTTOM" << endl;
		pos.y = n->getPosition().y - collider.h;
		vel.y = PUCK_BOUNCE_FACTOR_Y * -abs(vel.y);
		break;
	default:
//		cout << "NONE" << endl;
		break;
	}

}

void Puck::drop(){
	pos.x = SCREEN_WIDTH / 2 - PUCK_WIDTH / 2;
	pos.y = SCREEN_HEIGHT * 3 / 5.0 + SCREEN_HEIGHT / 20;
	vel = vec2(0, 0);
	MySoundManager::Instance()->playSound("goalhorn", 0);
	MySoundManager::Instance()->playSound("goalcheer", 0);
}				  

void Puck::setVelocity(vec2 velocity){
	vel = velocity;
}
