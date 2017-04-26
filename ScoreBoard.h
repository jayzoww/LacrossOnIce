//
//  ScoreBoard.h
//  prototype
//
//  Created by Chris Morgan on 2015-03-29.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#ifndef prototype_ScoreBoard_h
#define prototype_ScoreBoard_h

#define SCORE_X_OFFSET 118
#define SCORE_Y_OFFSET 30
#define TIME_X_OFFSET 27
#define TIME_Y_OFFSET 30

#include "LTexture.h"
#include "GameObject.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "vec2.h"
#include <cmath>
class ScoreBoard : public GameObject{
public:
	ScoreBoard():homeScore(0),awayScore(0),runTime(GAMELENGTH){};
	ScoreBoard(float gameTime, const vec2& position);
	~ScoreBoard();
	bool isTimeDone();
	void changeScore(Team t);
	int getMaxScore();
	void update(float deltaTime);
	void draw();
	int getWinner();
private:
	LTexture* board = NULL;
	LTexture* away = NULL;
	LTexture* home = NULL;
	vector<LTexture*> nums;
	
	int homeScore;
	int awayScore;
	float runTime;
};

#endif
