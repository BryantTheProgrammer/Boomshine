//*********************************************************************
// File name:	 ExpandingCircle.h
// Author:		 Bryant Hayden
// Date:       4/29/2022
// Class:		   CS250
// Assignment: Boomshine
// Purpose:		 Build a class to represent an expandingCircle
//*********************************************************************
#pragma once
#include "Circle.h"
#include "SDLManager.h"
#include "Direction2D.h"
#include "MovingCircle.h"
#include "SDLSprite.h"

class ExpandingCircle : public Circle {
public:

	ExpandingCircle (int xCenter = 10, int yCenter = 10,
		int mExpansionAmount = 40, int radius = 10, int waitTime = 30,
		const Color &rcColor = Color::getColor (Color::E_COLOR::BLUE));
	ExpandingCircle (const MovingCircle &rcMovingCircle,
		int mExpansionAmount = 40, int waitTime = 30);

	void expand ();
	void wait ();
	void contract ();

	bool getIsExpanded ()const;
	bool getWaited () const;
	bool getIsContracted ()const;

private:
	int mExpansionRadius;
	int mWaitTime;
	int mWaitCounter;

	bool mbExpanded;
	bool mbWaited;
	bool mbContracted;
};