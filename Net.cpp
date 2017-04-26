#include "Net.h"


Net::Net(SDL_Rect r, bool face_right, float top, float bot, Team tm)  {
	pos = vec2(r.x, r.y);
	vel = vec2(0,NET_VEL);
	collider = r;
	vel = vec2(0, NET_VEL);
	facing_right = face_right;
	dir = 0;
	top_limit = top;
	bottom_limit = bot;
	t = tm;
	// add net picture select here
	if(gnet!=NULL){
		gnet->free();
		gnet = NULL;
	}
	gnet = new LTexture();
	if(t==HOME){
		gnet->loadFromFile("net1.png");
	} else {
		gnet->loadFromFile("net2.png");
	}
}

Net::~Net(){
	if(gnet != NULL){
		gnet->free();
		gnet = NULL;
	}
}

Team Net::getTeam(){
	return t;
}

void Net::draw() {
	//SDL_Rect fillRect = { pos.x, pos.y, collider.w, collider.h };
//	SDL_Rect fillRect = { static_cast<int>(pos.x), static_cast<int>(pos.y), collider.w, collider.h };
//	SDL_SetRenderDrawColor(SDLGI::gRenderer, 0x00, 0x00, 0xFF, 0xFF);
//	SDL_RenderFillRect(SDLGI::gRenderer, &fillRect);
	gnet->render(pos.x, pos.y);
}


void Net::update(float deltaTime) {
	pos = pos + vel * deltaTime;

	if (dir && pos.y <= top_limit){
		dir = 0;
		vel = vec2(0, -vel.y);
	}
	else if (!dir && pos.y >= bottom_limit){
		dir = 1;
		vel = vec2(0, -vel.y);
	}
}
