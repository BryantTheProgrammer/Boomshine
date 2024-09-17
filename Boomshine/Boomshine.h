//*********************************************************************
// File name:	 Boomshine.h
// Author:		 Bryant Hayden
// Date:       5/9/2022
// Class:		   CS250
// Assignment: Boomshine
// Purpose:		 Template for boomshine class
//*********************************************************************
#pragma once
#include "Circle.h"
#include "SDLManager.h"
#include "Direction2D.h"
#include "MovingCircle.h"
#include "SDLSprite.h"
#include "ExpandingCircle.h"

class Boomshine {
public:
	const int WINDOW_SIZE_X = 640;
	const int WINDOW_SIZE_Y = 640;

	//From Color::E_Color
	const int TOTAL_COLORS = 14;
	//Gray
	const int BACKROUND_COLOR_INDEX = 1;

	Boomshine (int gameLevel = 3);


	void checkCollisions ();
	void manageExpandingCircles ();
	void moveCircles ();

	void drawCircles (SDLManager &rcSDLManager);

	void addExpandingCircle (int x, int y);

	bool circlesStillExpanding () const;

	bool getGamePlayed () const;
	bool getGameOver () const;

	int getNumMovingCircles ()const;
	int getscore ()const;
	int getLevel ()const;

	void setGamePlayed ();
	void setGameOver ();

	void playAgain (bool levelPassed = false);
private:
	int mGameLevel;
	int mScore;

	bool bGamePlayed;
	bool bGameOver;

	std::vector<MovingCircle> mcMovingCircles;
	std::vector<ExpandingCircle> mcExpandingCircles;

	void generateMovingCircles (unsigned numberCircles,
		const int baseSpeed = 1, const int circleRadius = 10);

	Mix_Chunk *mpsAudio;
	void calculateScore ();
};