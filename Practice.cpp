//
//  Practice.cpp
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#include "Practice.h"
bool forcePQuit = false;

Practice::Practice(float gt, int gs) : practiceTime(gt), endScore(gs){
	//	init(); // maybe should be done in start
    score = new ScoreBoard(practiceTime, vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/10));
	SDL_Rect r;
	
	r.x = 0;
	r.y = (SCREEN_HEIGHT * 9)/10;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT/10;
	platforms.push_back(new Platform(r));
	
	r.x = SCREEN_WIDTH / 3;
	r.y = SCREEN_HEIGHT * 3 / 5;
	r.w = SCREEN_WIDTH / 3;
	r.h = SCREEN_HEIGHT / 20;
	platforms.push_back(new Platform(r));
	
	r.x = -SCREEN_WIDTH / 10;
	r.y = 0;
	r.w = SCREEN_WIDTH / 10;
	r.h = SCREEN_HEIGHT;
	platforms.push_back(new Platform(r));
	r.x = SCREEN_WIDTH;
	r.y = 0;
	r.w = SCREEN_WIDTH / 10;
	r.h = SCREEN_HEIGHT;
	platforms.push_back(new Platform(r));

	r.x = 0;
	r.y = 0;
	r.w = PLAYER_WIDTH;
	r.h = PLAYER_HEIGHT;
	player1 = new Player(r, true, platforms, HOME);

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH * 0.02;
	r.h = SCREEN_HEIGHT * 0.3;
	net1 = new Net(r, true, SCREEN_HEIGHT * 0.05, SCREEN_HEIGHT * 0.9 - r.h - SCREEN_HEIGHT * 0.05, HOME);

	r.x = SCREEN_WIDTH-NET_WIDTH;
	r.y = 0;
	r.w = NET_WIDTH;
	r.h = NET_HEIGHT;
	net2 = new Net(r, true, SCREEN_HEIGHT * 0.05, SCREEN_HEIGHT * 0.9 - r.h - SCREEN_HEIGHT * 0.05, AWAY);

	r.x = SCREEN_WIDTH/2 - PUCK_WIDTH/2;
	r.y = 0;
	r.w = PUCK_WIDTH;
	r.h = PUCK_HEIGHT;
	puck = new Puck(r, score);
}

Practice::~Practice(){
	close();
}

void Practice::init(){

}

void Practice::close(){

}

void Practice::reset(){

}

void Practice::start(){
	reset();
	float time = 0.0; // time for frame loop in seconds since it starts
	int timeStart = SDL_GetTicks();
	float deltaTime = 0.0; // time taken between frame;
	LTexture bg;
	bg.loadFromFile("backgroundWithPlatform.png");


	while (!isPracticeOver()) {
		// update Time information...
		int currentMillis = SDL_GetTicks();
		float nextTime = ((float)(currentMillis - timeStart))/1000.0f;
		deltaTime = nextTime-time;
		time = nextTime;//((float)(currentMillis - timeStart))/1000.0f;

		//cout << 1 / deltaTime << endl;

		//cout << "Time: " << time << " DeltaTime: " << deltaTime << endl;

		// get Input and update object positions from input
		handleInput();
		player1->update(deltaTime);
		net1->update(deltaTime);
		net2->update(deltaTime);
		puck->update(deltaTime);
		// check collisions...

		//CollisionFace collFace = GameObject::checkCollision(player1, player2);
		//Player::OnCollisionEnter(player1, player2, collFace, deltaTime);

		CollisionFace collFace;

		for (int i = 0; i < platforms.size(); i++){
			collFace = GameObject::checkCollision(player1, platforms[i]);
			player1->OnCollisionEnter(platforms[i], collFace, deltaTime);

			//collFace = GameObject::checkCollision(player2, platforms[i]);
			//player2->OnCollisionEnter(platforms[i], collFace, deltaTime);

			if (!puck->isPossessed()){

				collFace = GameObject::checkCollision(puck, platforms[i]);
				puck->OnCollisionEnter(platforms[i], collFace, deltaTime);

			}

		}

		if (!puck->isPossessed()){

			collFace = GameObject::checkCollision(puck, net1);
			puck->OnCollisionEnter(net1, collFace, deltaTime);

			collFace = GameObject::checkCollision(puck, net2);
			puck->OnCollisionEnter(net2, collFace, deltaTime);

			collFace = GameObject::checkCollision(puck, player1);
			player1->OnCollisionEnter(puck, collFace, deltaTime);
//
//			collFace = GameObject::checkCollision(puck, player2);
//			player2->OnCollisionEnter(puck, collFace, deltaTime);

		}

		// end collision checking


		// Practice logic implementation...

		// end Practice logic

		// render frame
		SDL_SetRenderDrawColor(SDLGI::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( SDLGI::gRenderer );

		bg.render(0,0);
		
		score->draw();
		
		//Draw Platforms
		SDL_SetRenderDrawColor( SDLGI::gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
		for(int i = 0; i < platforms.size(); i++)
		{
			platforms[i]->draw();
		}


		player1->draw();
		net1->draw();
		net2->draw();
		if (!puck->isPossessed()){
			puck->draw();
		}

		//Update screen
		SDL_RenderPresent( SDLGI::gRenderer );
		// end render

	}
	forcePQuit = false;
	close();

}

void Practice::handleInput(){
	SDL_Event e;

	SDL_PumpEvents();
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{

		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		//User requests quit
		if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			forcePQuit=true;
		}
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
		{
			//Adjust the velocity
			switch( e.key.keysym.sym )
			{
			case SDLK_w: player1->Up(); puck->Up(); break;
			case SDLK_s: player1->Down(); break;
			case SDLK_a: player1->Left(); break;
			case SDLK_d: player1->Right(); break;
			case SDLK_LSHIFT: player1->Shoot(); break;
			}
		}
		//If a key was released
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
		{
			//Adjust the velocity
			switch( e.key.keysym.sym )
			{
			case SDLK_w: player1->UpUnpressed(); break;
			case SDLK_s: player1->DownUnpressed(); break;
			case SDLK_a: player1->LeftUnpressed(); break;
			case SDLK_d: player1->RightUnpressed(); break;
			case SDLK_LSHIFT: player1->ShootUnpressed(); break;
			}
		}

		//Handle input for the player objects...
		//coming soon;
	}
}

bool Practice:: isPracticeOver(){
	return score->getMaxScore()==endScore || score->isTimeDone() || forcePQuit;
}

bool Practice:: isGoal(){
	return false;
}

