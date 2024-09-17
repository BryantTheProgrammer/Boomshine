//*********************************************************************
// File name:	 Boomshine.cpp
// Author:		 Bryant Hayden
// Date:       5/9/2022
// Class:		   CS250
// Assignment: Boomshine
// Purpose:		 Implementation for boomshine class
//*********************************************************************
#include "Boomshine.h"
//*********************************************************************
// Constructor: Boomshine
//
// Description: creates a boomshine object
//
// Parameters:  gameLevel - levelOfBoomshine to be played
//
// Returned:    none
//*********************************************************************
Boomshine::Boomshine (int gameLevel) {
	mGameLevel = gameLevel;
	mScore = 0;

	bGameOver = false;
	bGamePlayed = false;

	mcMovingCircles = {};
	mcExpandingCircles = {};

	mpsAudio = Mix_LoadWAV ("boom1.wav");

	generateMovingCircles (gameLevel * 2);
}
//*********************************************************************
// Function:    generateMovingCircles
//
// Description: generates movingCircles for boomshine
//
// Parameters:  numberCircles - number of circles to generate
//							baseSpeed     - lowestSpeed of the circles
//							circleRadius  - radius of moving circles
//
// Returned:    none
//*********************************************************************
void Boomshine::generateMovingCircles (unsigned numberCircles,
	const int baseSpeed, const int circleRadius) {
	// This loop will randomly generate each value of a circle
	// during every iteration
	for (unsigned circle = 0; circle < numberCircles; circle++) {
		int generatedX =
			(rand () % (WINDOW_SIZE_X - (2 * circleRadius) - 2))
			+ (circleRadius + 1);
		int generatedY =
			(rand () % (WINDOW_SIZE_Y - (2 * circleRadius) - 2))
			+ (circleRadius + 1);
		int generatedColorIndex = (rand () % TOTAL_COLORS + 2);

		Direction2D generatedDirection (Direction2D::E_Compass_Direction
		(rand () % Direction2D::NUMBER_OF_COORDINATES));

		Color generatedColor = Color (Color::E_COLOR (generatedColorIndex));

		MovingCircle randomCircle (generatedX, generatedY, circleRadius,
			generatedColor, generatedDirection, rand () % 3 + baseSpeed);

		randomCircle.setMovementBoundingBox
		(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

		mcMovingCircles.push_back (randomCircle);
	}
}
//*********************************************************************
// Function:    handleExpansions
//
// Description: keeps track each expandingCircle and their expansion
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::manageExpandingCircles () {
	for (auto &it : mcExpandingCircles) {
		if (!it.getIsExpanded ()) {
			it.expand ();
		}
		else if (!it.getWaited ()) {
			it.wait ();
		}
		else if (!it.getIsContracted ()) {
			it.contract ();
		}
		else {
			mcExpandingCircles.erase (mcExpandingCircles.begin ());
		}
	}
}
//*********************************************************************
// Function:    handleMovements
//
// Description: handlesMovements of MovingCircles
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::moveCircles () {
	for (auto &it : mcMovingCircles) {
		it.move ();
	}
}
//*********************************************************************
// Function:    getScore
//
// Description: gets score after Circles are done expanding
//
// Parameters:  none
//
// Returned:    score of the game
//*********************************************************************
int Boomshine::getscore () const {
	return (mGameLevel * 2) - mcMovingCircles.size ();
}

//*********************************************************************
// Function:    handleCollisions
//
// Description: checks for collision of movingCircles and
//							expandingCircles, if there is a collision, the
//							movingCircle gets turned into a expanding circle
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::checkCollisions () {
	for (unsigned expanding = 0; expanding < mcExpandingCircles.size ();
		expanding++) {

		for (unsigned moving = 0; moving < mcMovingCircles.size ();
			moving++) {

			if (mcMovingCircles.at (moving).collision
			(mcExpandingCircles.at (expanding))) {

				Mix_PlayChannel (1, mpsAudio, 0);

				mcExpandingCircles.push_back
				(ExpandingCircle (mcMovingCircles.at (moving)));

				mcMovingCircles.erase (mcMovingCircles.begin () + moving);
			}
		}
	}
}
//*********************************************************************
// Function:    drawCircles
//
// Description: draw member circles with a SDLMangager
//
// Parameters:  rcSDLManager - passed in to be used in draw()
//
// Returned:    none
//*********************************************************************
void Boomshine::drawCircles (SDLManager &rcSDLManager) {
	for (auto &it : mcMovingCircles) {
		it.draw (rcSDLManager);
	}
	//Handles Drawing for expanding Circle
	for (auto &it : mcExpandingCircles) {
		it.draw (rcSDLManager);
	}
}
//*********************************************************************
// Function:    addExpandingCircle
//
// Description: adds an ExpandingCircle to mcExpandingCircles
//
// Parameters:  x - x-coordinate of new circle
//							y - y-Coordinate of new circle
//
// Returned:    none
//*********************************************************************
void Boomshine::addExpandingCircle (int x, int y) {
	mcExpandingCircles.push_back (ExpandingCircle (x, y));
}
//*********************************************************************
// Function:    isStillExpanding
//
// Description: returns if there any expanding circles in existence
//
// Parameters:  none
//
// Returned:    true if there are expanding circles
//*********************************************************************
bool Boomshine::circlesStillExpanding () const {
	return mcExpandingCircles.size () > 0;
}

//*********************************************************************
// Function:    getNumMovingCircles
//
// Description: returns the number of movingCircles in mcMovingCircles
//
// Parameters:  none
//
// Returned:    size of mcMovingCircles
//*********************************************************************
int Boomshine::getNumMovingCircles () const {
	return mcMovingCircles.size ();
}
//*********************************************************************
// Function:    getLevel
//
// Description: returns mGameLevel
//
// Parameters:  none
//
// Returned:    current level of boomshine
//*********************************************************************
int Boomshine::getLevel () const {
	return mGameLevel;
}
//*********************************************************************
// Function:    setGamePlayed
//
// Description: sets game state to played
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::setGamePlayed () {
	bGamePlayed = true;
}
//*********************************************************************
// Function:    getGamePlayed
//
// Description: returns whether or not the game has been started
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
bool Boomshine::getGamePlayed ()const {
	return bGamePlayed;
}
//*********************************************************************
// Function:    setGameOver
//
// Description: sets bGameOver to true if game has ended and then
//							calls calculateScore()
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::setGameOver () {
	bGameOver = true;
	calculateScore ();
}
//*********************************************************************
// Function:    getGameOver
//
// Description: returns whether or not the game has ended
//
// Parameters:  none
//
// Returned:    true if the game is over
//*********************************************************************
bool Boomshine::getGameOver () const {
	return bGameOver;
}//*********************************************************************
// Function:    calculateScore
//
// Description: compares remaining circles to start of level to get
//							score, sets mScore
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void Boomshine::calculateScore () {
	mScore = mGameLevel * 2 - getNumMovingCircles ();
}
//*********************************************************************
// Function:    playAgain
//
// Description: resets game to pre-game state, generates new
//							movingCircles, uses same level or increments level
//							depending on if the level was passed or not
//
// Parameters:  levelPassed - levelPassed if player scored circles
//													  >= the level
//
// Returned:    none
//*********************************************************************
void Boomshine::playAgain (bool levelPassed) {
	if (levelPassed) {
		mGameLevel += 1;
	}

	bGameOver = false;
	bGamePlayed = false;

	mcMovingCircles = {};
	mcExpandingCircles = {};

	generateMovingCircles (mGameLevel * 2);
}