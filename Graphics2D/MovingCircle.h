//*********************************************************************
// File name:	 MovingCircle.h
// Author:		 Computer Science, Pacific University
// Date:       4/23/2022
// Class:		   CS 250
// Assignment: SDL2 Moving Circles
// Purpose:		 Build a class to represent a moving circle
//*********************************************************************
#pragma once

#include "SDLManager.h"
#include "Circle.h"
#include "Direction2D.h"

class MovingCircle : public Circle {

public:
	static const int MIN_X = 0;
	static const int MIN_Y = 0;
	static const int MAX_X = 639;
	static const int MAX_Y = 639;

	MovingCircle (int xCenter = 100, int yCenter = 100, int radius = 10,
		const Color &rcColor = Color::E_COLOR::BLACK,
		const Direction2D &rcDirection =
		Direction2D::E_Compass_Direction::N, int speed = 1);

	bool move ();

	void setDirection (const Direction2D &rcDirection);
	Direction2D getDirection () const;

	void setSpeed (int speed);
	int getSpeed () const;

	void setMovementBoundingBox (int xMin = MIN_X, int yMin = MIN_Y,
		int xMax = MAX_X, int yMax = MAX_Y);

	friend std::istream &operator>> (std::istream &rcInStream,
		MovingCircle &cCircle);

private:

	// bounding box of movement
	int mXMin;
	int mYMin;
	int mXMax;
	int mYMax;

	Direction2D mcDirection;
	int mSpeed;
};