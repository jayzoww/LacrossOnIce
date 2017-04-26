//
//  ScoreBoard.cpp
//  prototype
//
//  Created by Chris Morgan on 2015-03-29.
//  Copyright (c) 2015 Chris Morgan. All rights reserved.
//

#include "ScoreBoard.h"

vector<string> numbers{
	"0.png", "1.png", "2.png", "3.png", "4.png", "5.png", "6.png", "7.png", "8.png", "9.png", "10.png"
};

ScoreBoard::ScoreBoard (float gameTime, const vec2& position){
	pos = position;
	runTime = gameTime;
	homeScore = 0;
	awayScore = 0;
	if(board!=NULL){
		board->free();
		board = NULL;
	}
	board = new LTexture();
	board->loadFromFile("Overlay.png");

	nums = vector<LTexture*>();
	
	for (int i = 0; i <= 10; i++){
		LTexture *ltext = new LTexture();
		stringstream ss(ios_base::app | ios_base::out);
		ss << numbers[i];
		ltext->loadFromFile(ss.str());
		cout << ltext << endl;
		nums.push_back(ltext);
	}
	
	if(away!=NULL){
		away->free();
		away = NULL;
	}
	// away = new LTexture(...init me...);
	if(home!=NULL){
		home->free();
		home = NULL;
	}
	// home = new LTexture(...init me...);
}

ScoreBoard::~ScoreBoard (){
	// free texture resources
	if(board!=NULL){
		board->free();
		board = NULL;
	}
	if(away!=NULL){
		away->free();
		away = NULL;
	}
	if(home!=NULL){
		home->free();
		home = NULL;
	}
}

void ScoreBoard::update(float deltaTime){
	runTime = fmax((runTime - deltaTime), 0);
}

bool ScoreBoard::isTimeDone(){
	return runTime<=0;
}

void ScoreBoard::changeScore(Team t){
	if(t == AWAY){
		homeScore ++;
		if(home!=NULL){
			home->free();
		}
		// home = new LTexture(...init me....);
	} else {
		awayScore ++;
		if(away!=NULL){
			away->free();
		}
		// away = new LTexture(...init me....);
	}

	cout << homeScore << "\t" << awayScore << endl;
}

int ScoreBoard::getMaxScore(){
	return (homeScore>=awayScore) ? homeScore : awayScore;
}

int ScoreBoard::getWinner(){
	if (homeScore > awayScore){
		return -1;
	}
	else if (awayScore > homeScore){
		return 1;
	}
	else {
		return 0;
	}
}

void ScoreBoard::draw(){
	// draw here
	board->render(pos.x - board->getWidth()/2, pos.y - board->getHeight()/2);
	// Draw Scores
	LTexture* p1score = nums[homeScore];
	LTexture* p2score = nums[awayScore];
	p1score->render(pos.x - SCORE_X_OFFSET, pos.y - SCORE_Y_OFFSET);
	p2score->render(pos.x + SCORE_X_OFFSET - 22, pos.y - SCORE_Y_OFFSET);
	// Draw Time

	LTexture* sec10s = nums[int(runTime) / 10];
	LTexture* sec1s = nums[int(runTime) % 10];
	sec10s->render(pos.x - TIME_X_OFFSET, pos.y - TIME_Y_OFFSET);
	sec1s->render(pos.x + TIME_X_OFFSET - 22, pos.y - TIME_Y_OFFSET);

	

//	cout << "x " << pos.x << " y " << pos.y <<endl;
//	cout << "w " << board->getWidth() << " h " << board->getHeight() <<endl;
}

