//
//  Game.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#ifndef __prototype__Game__
#define __prototype__Game__

#include "SDLInit.h"
#include <iostream>
#include <vector>
#include "Net.h"
#include "Platform.h"
#include "Player.h"
#include "Puck.h"
#include "ScoreBoard.h"

using namespace std;

class Game{
public :

	Game(float gt=GAMELENGTH, int gs=WINNINGSCORE);
	~Game();
	void reset();
	void start();
	bool paused;
private :
	// Game Objects For execution...
	Player* player1;
	Player* player2;
	Net* net1;
	Net* net2;
	Puck* puck;
	ScoreBoard* score;
//	int score;// temporary member until score board is finished
	vector<Platform*> platforms;
	// end Game Objects
	float gameTime;
	int endScore;
	// member functions...
	bool isGameOver();
	bool isGoal();
	void handleInput();
	void init();
	void close();

};

#endif /* defined(__prototype__Game__) */
