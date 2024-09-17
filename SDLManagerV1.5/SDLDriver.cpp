//**********************************************************************
// File name:	 SDLDriver.cpp
// Author:     Computer Science, Pacific University
// Date:       
// Class:      
// Assignment: 
// Purpose:    
//**********************************************************************

#include "SDLManager.h"
#include "Color.h"

int main (int argc, char *argv[]) {
	int windowXPosition = 100,
		windowYPosition = 100,
		windowSizeX = 640,
		windowSizeY = 640;

	SDLManager &rcManager = SDLManager::instance ();

	rcManager.initializeWorld (windowXPosition, windowYPosition,
		windowSizeX, windowSizeY);
	rcManager.setBackgroundColor (Color::E_COLOR::GRAY);
	rcManager.setForegroundColor (Color::E_COLOR::BLACK);

	SDL_Event uEvent;
	rcManager.animationStart ();
	rcManager.clearBackground ();

	while (rcManager.animationIsRunning ()) {
		rcManager.clearBackground ();
		rcManager.displayText (150, 50, "CS250 2D Graphics",
			Color::E_COLOR::BLUE);
		rcManager.drawLine (0, 0, 639, 639);
		rcManager.drawLine (639, 0, 0, 639);
		rcManager.drawFilledCircle (320, 320, 50, Color::E_COLOR::AQUA);

		if (rcManager.getSDLEvent (uEvent)) {
			if (SDL_QUIT == uEvent.type) {
				rcManager.animationStop ();
			}
		}

		rcManager.render ();
	}

	return EXIT_SUCCESS;
}
