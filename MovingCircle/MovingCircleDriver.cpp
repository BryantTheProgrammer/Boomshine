//*********************************************************************
// File name:	 MovingCircleDriver.cpp
// Author:     Computer Science, Pacific University
// Date:       4/19/2022
// Class:      CS250
// Assignment: movingCircle
// Purpose:
//*********************************************************************
#include "SDLManager.h"
#include "MovingCircle.h"
#include "Color.h"
#include "Circle.h"
#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
	const string IN_FILE_NAME = "movingcircles.txt";
	const string ERROR_MESSAGE = "Error Opening File";

	fstream inFile;

	vector<MovingCircle>cMovingCircles = {};

	MovingCircle readMovingCircle;

	SDLManager &rcSDLManager = SDLManager::instance ();

	bool bFailedRead = false;

	int windowXPosition = 300,
		windowYPosition = 300,
		windowSizeX = 640,
		windowSizeY = 640;

	rcSDLManager.initializeWorld (windowXPosition, windowYPosition,
		windowSizeX, windowSizeY, "Moving Circles");
	rcSDLManager.setBackgroundColor (Color::E_COLOR::TEAL);
	rcSDLManager.setForegroundColor (Color::E_COLOR::BLUE);

	inFile.open (IN_FILE_NAME);
	if (inFile.fail ()) {
		bFailedRead = true;
	}

	while (inFile >> readMovingCircle) {
		cMovingCircles.push_back (readMovingCircle);
	}

	inFile.close ();

	SDL_Event uEvent;
	rcSDLManager.animationStart ();
	rcSDLManager.clearBackground ();

	while (rcSDLManager.animationIsRunning ()) {
		rcSDLManager.clearBackground ();

		if (bFailedRead == true) {
			rcSDLManager.displayText (100, 50, ERROR_MESSAGE,
				Color::E_COLOR::BLUE);
			rcSDLManager.displayText (100, 100, IN_FILE_NAME,
				Color::E_COLOR::BLUE);
		}
		//	if (cCircles.at (0) == cCircles.at (0)) {
				//exit (EXIT_SUCCESS);
			//}
		for (int circle = 0; circle < cMovingCircles.size (); circle++) {
			cMovingCircles.at (circle).move ();
		}
		for (auto it : cMovingCircles) {
			it.draw (rcSDLManager);
		}

		if (rcSDLManager.getSDLEvent (uEvent)) {
			if (SDL_QUIT == uEvent.type) {
				rcSDLManager.animationStop ();
			}
		}

		rcSDLManager.render ();
	}

	return EXIT_SUCCESS;
}