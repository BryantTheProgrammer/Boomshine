//*********************************************************************
// File name:	 BoomshineDriver.cpp
// Author:		 Bryant Hayden
// Date:       4/29/2022
// Class:		   CS250
// Assignment: Boomshine
// Purpose:		 Driver for Boomshine game
//*********************************************************************

#include "SDLManager.h"
#include "MovingCircle.h"
#include "Color.h"
#include "Circle.h"
#include "ExpandingCircle.h"
#include "Boomshine.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;



int main (int argc, char *argv[]) {
//**********************
const int GAME_LEVEL = 3;
//**********************

const Color BACKROUND_COLOR = Color::E_COLOR::GRAY;
const int WINDOW_SIZE_X = 640;
const int WINDOW_SIZE_Y = 640;

const string FONT_VERDANA = "C:/Windows/Fonts/Verdana.ttf";

// Play again button
enum  PLAY_AGAIN : int {
	xLeft = 275, yTop = 35, xRight = 385, yBottom = 80
};


	//srand (3);
	srand (static_cast<unsigned> (time (static_cast<time_t *>(NULL))));

	SDLManager &rcSDLManager = SDLManager::instance ();

	int windowXPosition = 300,
		windowYPosition = 300,
		windowSizeX = WINDOW_SIZE_X,
		windowSizeY = WINDOW_SIZE_Y;

	rcSDLManager.initializeWorld (windowXPosition, windowYPosition,
		windowSizeX, windowSizeY, "Boomshine");

	rcSDLManager.setBackgroundColor (BACKROUND_COLOR);
	rcSDLManager.setForegroundColor (Color::E_COLOR::BLUE);

	SDL_Event uEvent;

	rcSDLManager.animationStart ();
	rcSDLManager.clearBackground ();

	Boomshine cBoomshineGame (GAME_LEVEL);

	while (rcSDLManager.animationIsRunning ()) {
		rcSDLManager.clearBackground ();


		//If the game has been played
		if (cBoomshineGame.getGamePlayed ()) {
			//If there are no more expanding circles
			if (!cBoomshineGame.circlesStillExpanding()) {
				cBoomshineGame.setGameOver ();
			}
		}

		//End of game Statement
		if (cBoomshineGame.getGameOver()) {
			// Creates Statment 
			string level = "Level: ", hits = " Hits: ",
				levelNum = to_string (cBoomshineGame.getLevel ()),
				hitNum = to_string (cBoomshineGame.getscore ());
			// writes statement to screen
			rcSDLManager.displayText (225,0,
				level + levelNum + hits + hitNum,Color(Color::E_COLOR::BLUE),
				rcSDLManager.loadFont(FONT_VERDANA, 25));

			// Block makes the button outline
				for (int y = PLAY_AGAIN::yTop; y < PLAY_AGAIN::yBottom; y++) {
					rcSDLManager.drawLine (xLeft, y, xRight, y);
				}
				// "Playagain"
				rcSDLManager.displayText (xLeft+10,yTop+10, "Play Again", 
					Color::E_COLOR::WHITE, rcSDLManager.loadFont (FONT_VERDANA, 18));
			}//Must be verdana
			// Handles collision and transforming of circles
			cBoomshineGame.checkCollisions ();

			// Handles moving circles
			cBoomshineGame.moveCircles ();

			// Handles Expanding Circles
			cBoomshineGame.manageExpandingCircles ();

			cBoomshineGame.drawCircles (rcSDLManager);

		// Handles Events: Mouse click and exit button
		if (rcSDLManager.getSDLEvent (uEvent)) {
			if (SDL_MOUSEBUTTONDOWN == uEvent.type &&
				!cBoomshineGame.getGameOver() &&
				!cBoomshineGame.circlesStillExpanding()) {
				int xClicked = uEvent.button.x;
				int yClicked = uEvent.button.y;
				cBoomshineGame.addExpandingCircle (xClicked, yClicked);
				cBoomshineGame.setGamePlayed ();
				//Mix_PlayChannel (1, mpsChunk, 0);
			}
			if (SDL_QUIT == uEvent.type) {
				rcSDLManager.animationStop ();
			}
		}
		//click for play again
		if (SDL_MOUSEBUTTONDOWN == uEvent.type &&
			cBoomshineGame.getGameOver ()) {
			if (uEvent.button.x > xLeft && uEvent.button.x <xRight &&
				uEvent.button.y > yTop && uEvent.button.y < yBottom) {
				cBoomshineGame.playAgain (cBoomshineGame.getscore () >=
					cBoomshineGame.getLevel ());
			}
		}
		rcSDLManager.render ();
	}
	Mix_Quit ();
	return EXIT_SUCCESS;
}
