//*********************************************************************
// File name:	 MovingCircle.h
// Author:     Bryant Hayden
// Date:       4/21/2022
// Class:      CS250
// Assignment: MovingCircle
// Purpose:
//*********************************************************************
#include "MovingCircle.h"

//*********************************************************************
// Constructor: MovingCircle
//
// Description: constructs MovingCircle, calling Circle while adding
//							speed and direction
//
// Parameters:  xCenter     - Coordinate for center on X-Axis
//              yCenter     - Coordinate for center on Y-axis
//              radius      - radius of circle
//              rcColor     - Color of circle
//							rcDirection - Direction of circle
//							mSpeed      - speed of circle
//
// Returned:    none
//*********************************************************************
MovingCircle::MovingCircle (int xCenter, int yCenter, int radius,
	const Color &rcColor, const Direction2D &rcDirection, int speed) :
	Circle (xCenter, yCenter, radius, rcColor) {
	mcDirection = rcDirection;
	mSpeed = speed;
	mXMin = MIN_X;
	mYMin = MIN_Y;
	mXMax = MAX_X;
	mYMax = MAX_Y;
}
//*********************************************************************
// Function:    move
//
// Description: handles the reflection and movement of circle 
//
// Parameters:  none
//
// Returned:    true if the circle collided with a wall
//*********************************************************************
bool MovingCircle::move () {
	bool bCollide = false;
	if (mXCenter + mRadius >= mXMax) {
		mcDirection = mcDirection.reflectOnRightSide ();
		bCollide = true;
	}
	if (mXCenter - mRadius <= mXMin) {
		mcDirection = mcDirection.reflectOnLeftSide ();
		bCollide = true;
	}
	if (mYCenter + mRadius >= mYMax) {
		mcDirection = mcDirection.reflectOnBottom ();
		bCollide = true;
	}
	if (mYCenter - mRadius <= mYMin) {
		mcDirection = mcDirection.reflectOnTop ();
		bCollide = true;
	}
	mXCenter += (getSpeed () * mcDirection.getXMove ());
	mYCenter += (getSpeed () * mcDirection.getYMove ());
	return bCollide;
}
//*********************************************************************
// Function:    setDirection
//
// Description: set direction of calling movingCircle
//
// Parameters:  rcDirection - direction to be set on the MovingCircle
//
// Returned:    none
//*********************************************************************
void MovingCircle::setDirection (const Direction2D &rcDirection) {
	mcDirection = rcDirection;
}
//*********************************************************************
// Function:    getDirection
//
// Description: return Direction of calling object
//
// Parameters:  none
//
// Returned:    Direction of the calling movingCircle
//*********************************************************************
Direction2D MovingCircle::getDirection () const {
	return mcDirection;
}
//*********************************************************************
// Function:    setSpeed
//
// Description: set speed of calling moving circle
//
// Parameters:  speed - speed to be set
//
// Returned:    none
//*********************************************************************
void MovingCircle::setSpeed (int speed) {
	mSpeed = speed;
}
//*********************************************************************
// Function:    getSpeed
//
// Description: returns speed of calling moving circle
//
// Parameters:  none
//
// Returned:    speed of the calling movingCircle
//*********************************************************************
int MovingCircle::getSpeed () const {
	return mSpeed;
}
//*********************************************************************
// Function:    setMovementBoundingBox
//
// Description: Function sets restrictions that circle cannot leave
//
// Parameters:  xMin - min value for x
//							yMin - min value for y
//							xMax - max value for x
//							yMax - max value for Y
//
// Returned:    none
//*********************************************************************
void MovingCircle::setMovementBoundingBox (int xMin, int yMin,
	int xMax, int yMax) {
	mXMin = xMin;
	mYMin = yMin;
	mXMax = xMax;
	mYMax = yMax;
}
//*********************************************************************
// Function:    operator>>
//
// Description: reads MovingCircle from an Istream
//
// Parameters:  rcInStream - stream to be read from
//							cCircle    - cCircle to be filled from instream
//
// Returned:    the modified instream
//*********************************************************************
std::istream &operator>>(std::istream &rcInStream,
	MovingCircle &cCircle) {
	rcInStream >> static_cast<Circle &>(cCircle) >>
		cCircle.mcDirection >> cCircle.mSpeed;
	return rcInStream;
}
