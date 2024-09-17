//*********************************************************************
// File name:	 Circle.cpp
// Author:     Computer Science, Pacific University
// Date:       4/19/2022
// Class:      CS250
// Assignment: SDL2SimpleCircle
// Purpose:
//*********************************************************************
#include "Circle.h"
#include "Color.h"
#include "SDLManager.h"
#include <cmath>
//*********************************************************************
// Constructor: Circle
//
// Description: Constructs a circle given a position of coordinates,
//							a size, and a color
//
// Parameters:  xCenter - Coordinate for center with respect to X-axis
//              yCenter - Coordinate for center with respect to Y-axis
//              radius  - radius of circle
//              rcColor - Color of circle
//
// Returned:    none
//*********************************************************************
Circle::Circle (int xCenter, int yCenter, int radius,
	const Color &rcColor) {
	mXCenter = xCenter;
	mYCenter = yCenter;
	mRadius = radius;
	mcColor = rcColor;
}
//*********************************************************************
// Constructor: Circle
//
// Description: Copy constructor for circle
//
// Parameters:  rcCircle - Circle for which the calling circle will be
//												 set
//
// Returned:    none
//*********************************************************************
Circle::Circle (const Circle &rcCircle) {
	*this = rcCircle;
}
//*********************************************************************
// Function:    draw
//
// Description: draws a Circle to an SDLManager
//
// Parameters:  rcManager - SDLManager for which the Circle is to be
//							drawn
//
// Returned:    none
//*********************************************************************
void Circle::draw (SDLManager &rcManager) const {
	rcManager.drawFilledCircle (mXCenter, mYCenter, mRadius, mcColor);
}
//*********************************************************************
// Function:    collision
//
// Description: if two circles intersect in anyway
//
// Parameters:  cOtherCircle - circle to be checked against the
//														 calling object
//
// Returned:    true if the circles intersect
//*********************************************************************
bool Circle::collision (const Circle &cOtherCircle) const {
	bool bIntersect = false;
	int xDistance = abs (mXCenter - cOtherCircle.mXCenter);
	int yDistance = abs (mYCenter - cOtherCircle.mYCenter);
	int minimumDistance = mRadius + cOtherCircle.mRadius;

	return (((xDistance * xDistance) + (yDistance * yDistance)) <
		(minimumDistance * minimumDistance));
}
//*********************************************************************
// Function:    scale
//
// Description: scales a Circle
//
// Parameters:  scaleFactor - factor by which to scale the
//														calling circle
//
// Returned:    the scaled radius
//*********************************************************************
double Circle::scale (double scaleFactor) {
	return mRadius * scaleFactor;
}

//*********************************************************************
// Function:    operator>>
//
// Description: reads in a circle from an inStream
//
// Parameters:  rcInStream - InStream for which we are reading
//						  rcCircle   - circle to be read into
//
// Returned:    the modified In stream
//*********************************************************************
std::istream &operator>>(std::istream &rcInStream, Circle &rcCircle) {
	rcInStream >> rcCircle.mXCenter >> rcCircle.mYCenter
		>> rcCircle.mRadius >> rcCircle.mcColor;
	return rcInStream;
}
//*********************************************************************
// Function:    operator==
//
// Description: check if two circles are equal
//
// Parameters:  rcOtherCircle - circle to be checked against calling
//															circle for equivalence
//
// Returned:    if 2 circles are equal
//*********************************************************************
bool Circle::operator==(const Circle &rcOtherCircle) const {
	return (mXCenter == rcOtherCircle.mXCenter &&
		mYCenter == rcOtherCircle.mYCenter &&
		mcColor.getA () == rcOtherCircle.mcColor.getA () &&
		mcColor.getG () == rcOtherCircle.mcColor.getG () &&
		mcColor.getR () == rcOtherCircle.mcColor.getR () &&
		mcColor.getB () == rcOtherCircle.mcColor.getB () &&
		mRadius == rcOtherCircle.mRadius);
}