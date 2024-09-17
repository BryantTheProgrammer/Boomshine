//*********************************************************************
// File name:	 Graphics2DDriver.cpp
// Author:     Computer Science, Pacific University
// Date:       4/19/2022
// Class:      CS250
// Assignment: SDL2SimpleCircle
// Purpose:
//*********************************************************************
#include"SDLManager.h"
#include"Color.h"
#include"Circle.h"
#include<fstream>

using namespace std;

int main (int argc, char *argv[]) {
	const string IN_FILE_NAME = "circles.txt";
	const string ERROR_MESSAGE = "Error Opening File";

	fstream inFile;

	vector<Circle>cCircles = {};

	Circle readCircle;

	SDLManager &rcSDLManager = SDLManager::instance ();

	bool bFailedRead = false;

	int windowXPosition = 300,
		windowYPosition = 300,
		windowSizeX = 640,
		windowSizeY = 640;

	rcSDLManager.initializeWorld (windowXPosition, windowYPosition,
		windowSizeX, windowSizeY, "Simple Graphics");
	rcSDLManager.setBackgroundColor (Color::E_COLOR::TEAL);
	rcSDLManager.setForegroundColor (Color::E_COLOR::BLUE);

	inFile.open (IN_FILE_NAME);
	if (inFile.fail()) {
		bFailedRead = true;
	}

	while (inFile >> readCircle){
		cCircles.push_back (Circle(readCircle));
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
			rcSDLManager.displayText (200, 100, IN_FILE_NAME,
				Color::E_COLOR::BLUE);
		}
		//if (cCircles.at(0) == cCircles.at(0)) {
		//	exit (EXIT_SUCCESS);
		//}
		for (auto it: cCircles) {
			it.draw (rcSDLManager);
		}
		//rcManager.drawLine (0, 0, 639, 639);
		//rcManager.drawLine (639, 0, 0, 639);

		//rcSDLManager.drawFilledCircle (320, 320, 50, Color::E_COLOR::RED);
		
		if (rcSDLManager.getSDLEvent (uEvent)) {
			if (SDL_QUIT == uEvent.type) {
				rcSDLManager.animationStop ();
			}
		}

		rcSDLManager.render ();
	}

	return EXIT_SUCCESS;
}