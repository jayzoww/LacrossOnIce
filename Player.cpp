#include "Player.h"

#define SPRITEFOLDER ""

enum PlayerSprite {
	BASER,
	BASEL,
	HPUCKR,
	HPUCKL,
	SHOOT1NPR,
	SHOOT1NPL,
	SHOOT1R,
	SHOOT1L,
	SHOOT2R,
	SHOOT2L,
	SHOOT3R,
	SHOOT3L,
	// Length is number of sprites
	LENGTH
	
};

vector<vector<string>> sprites {
	{
		"1baseR.png", "1baseL.png", "1withPuckR.png", "1withPuckL.png",
		"1shooting1NoPuckR.png", "1shooting1NoPuckL.png", "1shooting1R.png",
		"1shooting1L.png", "1shooting2R.png", "1shooting2L.png",
		"1shooting3R.png", "1shooting3L.png"
		
	},
	
	{
		"2baseR.png", "2baseL.png", "2withPuckR.png", "2withPuckL.png",
		"2shooting1NoPuckR.png", "2shooting1NoPuckL.png", "2shooting1R.png",
		"2shooting1L.png", "2shooting2R.png", "2shooting2L.png",
		"2shooting3R.png", "2shooting3L.png"
		
	}
};

Player::Player(SDL_Rect r, bool face_right, vector<Platform*> plats, Team team)  {
	pos = vec2(r.x, r.y);
	vel = vec2(0, 0);
	collider = r;
	platforms = plats;

	facing_right = face_right;
	//Set Key presses to false
	right_pressed = false;
	left_pressed = false;
	up_pressed = false;
	down_pressed = false;
	shoot_pressed = false;
	hasPuck = false;
	shotTime = 0;
	t = team;
	
	pics = vector<LTexture*>();
	for(int i=0; i<LENGTH; i++){
		LTexture* txt = new LTexture();
		stringstream ss (SPRITEFOLDER,ios_base::app | ios_base::out);
		ss << sprites[t][i];
		
		bool yay = txt->loadFromFile(ss.str());
			cout << "render Loaded " << yay << endl;
//		txt.setBlendMode(SDL_BLENDMODE_BLEND);
//		txt.setAlpha(255);
		pics.push_back(txt);
	}
	if(t==HOME){
		lastPic = pics[BASER];
	} else {
		lastPic = pics[BASEL];
	}
}

Player::~Player(){
	for(int i=0; i<pics.size();i++){
		delete pics[i];
	}
	lastPic = NULL;
}

void Player::update(float deltaTime) {

	grounded = false;


	if (up_pressed && vel.y < PLAYER_JUMPBOUNDARY ) {
		vel = vel + PLAYER_JUMP_GRAV * deltaTime;
	}
	else if (down_pressed){
		vel = vel + PLAYER_DOWN_GRAV * deltaTime;
	} else {
		vel = vel + GRAVITY * deltaTime;
	}
	if (vel.x >= PLAYER_MAXVEL){
	//	vel.x = PLAYER_MAXVEL;
	}
	if (vel.x <= -PLAYER_MAXVEL){
	//	vel.x = -PLAYER_MAXVEL;
	}
	if (right_pressed && !rightWall) {
		if (!shoot_pressed){
			if (vel.x > -5){
				vel.x += PLAYER_ACEL_X * deltaTime;
			}
			else
				vel.x += PLAYER_TURNACCEL_X * deltaTime;
		}
		facing_right = true;
	}
	else if (left_pressed && !leftWall) {
		if (!shoot_pressed){
			if (vel.x < 5){
				vel.x -= PLAYER_ACEL_X * deltaTime;
			}
			else
				vel.x -= PLAYER_TURNACCEL_X * deltaTime;
		}
		facing_right = false;
	}
	else if (vel.x > 5) {	//No keys held and moving right
		vel.x -= PLAYER_DECEL_X * deltaTime;
	}
	else if (vel.x < -0.01) { //No keys held and moving right
		vel.x += PLAYER_DECEL_X * deltaTime;
	}
	else { //Not pressing keys and velocity between -.1 & .1
		vel.x = 0;	//Stop. Reduces possible infinite flipping between "decelerating" left and right
	}

	if (shoot_pressed){
		shotTime += deltaTime;
	}

	//cout << vel.x << endl;
	pos = pos + vel * deltaTime;

	//TODO remove after adding collisions
	//if (pos.x >= SCREEN_WIDTH - collider.w){
	//	pos.x = SCREEN_WIDTH - collider.w;
	//	vel.x = 0;
	//}
	//if (pos.x <= 0){
	//	pos.x = 0;
	//	vel.x = 0;
	//}
	if (pos.y >= SCREEN_HEIGHT) {
		pos.y = SCREEN_HEIGHT -collider.h - SCREEN_HEIGHT / 10;
	}
	if (pos.y <= 0){
		pos.y = 0;
		vel.y = 0;
	}

	leftWall = false;
	rightWall = false;
}

void Player::draw() {
//	SDL_Rect fillRect = { static_cast<int>(pos.x), static_cast<int>(pos.y), collider.w, collider.h};
//	if(left_pressed || right_pressed) {
//		SDL_SetRenderDrawColor( SDLGI::gRenderer, 0x00, 0xFF, 0x00, 0xFF );		
//	}
//	else if (hasPuck) {
//		SDL_SetRenderDrawColor(SDLGI::gRenderer, 0x00, 0x00, 0x00, 0xFF);
//	}
//	else {
//		SDL_SetRenderDrawColor( SDLGI::gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
//	}
//	SDL_RenderFillRect( SDLGI::gRenderer, &fillRect );
//	SDL_SetRenderDrawColor(SDLGI::gRenderer, 0x00, 0x00, 0x00, 0xFF);
//	SDL_RenderDrawRect(SDLGI::gRenderer, &fillRect);
	LTexture* pic = lastPic;
	if(!hasPuck){
		if( !facing_right ){
			if(shoot_pressed){
				pic = pics[SHOOT1NPL];
			} else {
				pic = pics[BASEL];
			}
		} else if( facing_right) {
			if(shoot_pressed){
				pic = pics[SHOOT1NPR];
			} else {
				pic = pics[BASER];
			}
		}
	} else {
		if( !facing_right ){
			if(shoot_pressed){
				pic = pics[SHOOT1L];
			} else {
				pic = pics[HPUCKL];
			}
			
		} else if( facing_right) {
			if(shoot_pressed){
				pic = pics[SHOOT1R];
			} else {
				pic = pics[HPUCKR];
			}
		}
	}
	lastPic = pic;
	//cout << "mtexture " << pic << endl;
//	cout << "len " << pics.size() <<endl;
//	SDL_Point c{static_cast<int>(pos.x),static_cast<int>(pos.y)};
	pic->render(pos.x - collider.w, pos.y);//,NULL,0.0,&c);

}

void Player::OnCollisionEnter(Platform* p, CollisionFace cf, float deltaTime) {

	switch (cf) {
	case TOP:
	//	cout << "TOP" << endl;
		pos.y = p->getPosition().y + p->getCollider().h;
		vel.y = PLAYER_BOUNCE_FACTOR_Y * abs(vel.y);
		break;
	case LEFT:
	//	cout << "LEFT" << endl;
		pos.x = p->getPosition().x + p->getCollider().w;
		vel.x = vel.x <= 0 ? PLAYER_BOUNCE_FACTOR_X * abs(vel.x) : vel.x;
		leftWall = true;
		break;
	case RIGHT:
	//	cout << "RIGHT" << endl;
		pos.x = p->getPosition().x - collider.w;
		vel.x = vel.x >= 0 ? PLAYER_BOUNCE_FACTOR_X * -abs(vel.x): vel.x;
		rightWall = true;
		break;
	case BOTTOM:
	//	cout << "BOTTOM" << endl;
		pos.y = p->getPosition().y - collider.h;
		vel.y = vel.y>=0 ? 0 : vel.y;
		grounded = true;
		break;
	default:
	//	cout << "NONE" << endl;
		break;
	} 

}

void Player::OnCollisionEnter(Puck* p, CollisionFace cf, float deltaTime) {

	if (cf != NONE){
		if (p->possession == false){
			hasPuck = true;
			p->possession = true;
			puck = p;
		}
	}
}

void Player::OnCollisionEnter(Player* a, Player* b, CollisionFace cf, float deltaTime){
	vec2 temp;
	vec2 avg;

	switch(cf) {
	case LEFT: // Player A collides with Player b from right
		temp = a->pos;
		a->pos.x = b->pos.x + b->collider.w;
		b->pos.x = temp.x - b->collider.w;
		temp = a->vel;
		a->vel.x = b->vel.x;
		b->vel.x = temp.x;
		if (abs(a->vel.x - b->vel.x) > PLAYER_HIT_THRESH){
			MySoundManager::Instance()->playSound("bodycheck", 0);
			if (a->hasPuck){
				a->losePuck();
			}
			else if (b->hasPuck){
				b->losePuck();
			}
		}
		break;

	case RIGHT: // Player A collides with Player b from left
		temp = b->pos;
		b->pos.x = a->pos.x + a->collider.w;
		a->pos.x = temp.x - a->collider.w;
		temp = a->vel;
		a->vel.x = b->vel.x;
		b->vel.x = temp.x;
		if (abs(a->vel.x - b->vel.x) > PLAYER_HIT_THRESH){
			MySoundManager::Instance()->playSound("bodycheck", 0);
			if (a->hasPuck){
				a->losePuck();
			}
			else if (b->hasPuck){
				b->losePuck();
			}
		}		
		break;

	case TOP:	//a is on bottom
		b->pos.y = a->getPosition().y - b->collider.h;
		b->vel.y = -abs(b->vel.y)*PLAYER_HEAD_BOUNCE +  a->vel.y;
		b->grounded = true;
		a->vel.y = abs(a->vel.y);
		if (a->hasPuck){
			a->losePuck();
		}
		break;

	case BOTTOM:
		a->pos.y = b->getPosition().y - a->collider.h;
		a->vel.y = -abs(a->vel.y)*PLAYER_HEAD_BOUNCE + b->vel.y;
		a->grounded = true;
		b->vel.y = abs(b->vel.y);
		if (b->hasPuck){
			b->losePuck();
		}
		break;


	}
}



void Player::Up() {
	up_pressed = true;
	if (grounded) {
		vel = vec2(vel.x, PLAYER_JUMPVEL);
		grounded = false;
	}
}

void Player::Down() {
	down_pressed = true;
	//TODO
}

void Player::Right() {
	right_pressed = true;
	left_pressed = false;
}

void Player::Left() {
	left_pressed = true;
	right_pressed = false;
}
void Player::UpUnpressed() {
	up_pressed = false;
}
void Player::DownUnpressed() {
	down_pressed = false;
}
void Player::LeftUnpressed() {
	left_pressed = false;
}
void Player::RightUnpressed() {
	right_pressed = false;
}

void Player::Shoot() {
	shotTime = 0;
	shoot_pressed = true;
}

void Player::KnockedDown() {
	knockTime = 0;
	knocked_down = true;
	// change position
	

	// change collider rectangle
	// knock off puck
	//

}

void Player::losePuck(){
	vec2 puckpos = pos + vec2(0,-PUCK_HEIGHT-1);
	puck->possession = false;
	hasPuck = false;
	puck->setPosition(puckpos);
	puck->setVelocity(vec2(0, -700));

}

void Player::ShootUnpressed(){
	float aimfactor = up_pressed ? 0.25 : 1;
	vec2* puckVel;
	if (hasPuck){
		MySoundManager::Instance()->playSound("shot", 0);
		shotTime = shotTime > 1/3.0 ? 1 : shotTime * 3;
		if (facing_right){
			if (up_pressed){
				puckVel = new vec2(0.5, 3);
				puckVel->x *= MAX_SHOTX * (shotTime / 2 + 0.5);
				puckVel->y *= -MAX_SHOTY * (shotTime / 2 + 0.5);
			}
			else {
				puckVel = new vec2(1, 2 * shotTime);
				puckVel->x *= MAX_SHOTX * (shotTime / 2 + 0.5);
				puckVel->y *= -MAX_SHOTY * shotTime;
			}


			puckVel->x += vel.x;
			puckVel->y += vel.y;
		}
		else{
			if (up_pressed){
				puckVel = new vec2(-0.5, 3);
				puckVel->x *= MAX_SHOTX * (shotTime / 2 + 0.5);
				puckVel->y *= -MAX_SHOTY * (shotTime / 2 + 0.5);
			}
			else {
				puckVel = new vec2(-1, 2 * shotTime);
				puckVel->x *= MAX_SHOTX * (shotTime / 2 + 0.5);
				puckVel->y *= -MAX_SHOTY * shotTime;
			}

			puckVel->x += vel.x;
			puckVel->y += vel.y;
		}
		//cout << puckVel->y << endl;
		if (facing_right){
			puck->setPosition(pos + vec2(PLAYER_WIDTH,PLAYER_HEIGHT-PUCK_HEIGHT));
		}
		else {
			puck->setPosition(pos + vec2(-PUCK_WIDTH, PLAYER_HEIGHT - PUCK_HEIGHT));
		}

		puck->setVelocity(*puckVel);
		puck->possession = false;
		hasPuck = false;
	}
	shoot_pressed = false;
}