//
//  Practice.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-08.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#ifndef __prototype__Practice__
#define __prototype__Practice__

#include "SDLInit.h"
#include <iostream>
#include <vector>
#include "Net.h"
#include "Platform.h"
#include "Player.h"
#include "Puck.h"
#include "ScoreBoard.h"

using namespace std;

class Practice{
public :
	Practice(float gt=GAMELENGTH, int gs=WINNINGSCORE);
	~Practice();
	void reset();
	void start();
private :
	// Practice Objects For execution...
	Player* player1;
	//Player* player2;
	Net* net1;
	Net* net2;
	Puck* puck;
	ScoreBoard* score;
//	int score;// temporary member until score board is finished
	vector<Platform*> platforms;
	// end Practice Objects
	float practiceTime;
	int endScore;
	// member functions...
	bool isPracticeOver();
	bool isGoal();
	void handleInput();
	void init();
	void close();

};

#endif /* defined(__prototype__Practice__) */

