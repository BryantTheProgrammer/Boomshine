//*********************************************************************
// File name:	 ExpandingCircle.cpp
// Author:		 Bryant Hayden
// Date:       4/29/2022
// Class:		   CS250
// Assignment: Boomshine
// Purpose:		 Implementation for expandingCircle
//*********************************************************************
#include "ExpandingCircle.h"
//*********************************************************************
// Constructor: ExpandingCircle
//
// Description: Constructs ExpandingCircle
//
// Parameters:  xCenter					 - Center(X) of Expanding Circle
//							yCenter					 - Center(Y) of Expanding Circle
//							radius           - starting radius of Expanding Circle
//							rcColor          - Color of Expanding Circle
//							mExpansionAmount - amount to increase radius of circle
//							waitTime         - amount of time circle stays expanded
// 
// Returned:    none
//*********************************************************************
ExpandingCircle::ExpandingCircle (int xCenter, int yCenter,
	int mExpansionAmount, int radius, int waitTime, const Color &rcColor)
	: Circle (xCenter, yCenter, radius, rcColor) {

	mExpansionRadius = mRadius + mExpansionAmount;

	mbExpanded = false;
	mbWaited = false;
	mbContracted = false;

	mWaitTime = waitTime;
	mWaitCounter = 0;
}
//*********************************************************************
// Constructor: ExpandingCircle
//
// Description: Constructs ExpandingCircle based on a moving circle
//
// Parameters:  waitTime         - amount of time circle stays expanded
//							mExpansionAmount - amount to increase radius of circle
//							rcMovingCircle   - movingCircle to generate expanding
//															   circle at the same position
// Returned:    none
//*********************************************************************
ExpandingCircle::ExpandingCircle (const MovingCircle &rcMovingCircle,
	int mExpansionAmount, int waitTime) :Circle (rcMovingCircle) {
	
	mExpansionRadius = mRadius + mExpansionAmount;

	mbExpanded = false;
	mbWaited = false;
	mbContracted = false;

	mWaitTime = waitTime;
	mWaitCounter = 0;
}
//*********************************************************************
// Function:    expand
//
// Description: keeps track of expansion
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void ExpandingCircle::expand () {
	if (mRadius != mExpansionRadius) {
		mRadius++;
	}
	else {
		mbExpanded = true;
	}
}
//*********************************************************************
// Function:    wait
//
// Description: keeps track of wait while the circle is fully expanded
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void ExpandingCircle::wait () {
	if (mWaitTime != mWaitCounter) {
		mWaitCounter++;
	}
	else {
		mbWaited = true;
	}
}
//*********************************************************************
// Function:    contract
//
// Description: keeps track of contraction
//
// Parameters:  none
//
// Returned:    none
//*********************************************************************
void ExpandingCircle::contract () {
	if (mRadius != 0) {
		mRadius--;
	}
	else {
		mbContracted = true;
	}
}
//*********************************************************************
// Function:    getIsExpanded
//
// Description: Function returns whether or not a circle has fully
//						  expanded
//
// Parameters:  none
//
// Returned:    true if the circle has expanded
//*********************************************************************
bool ExpandingCircle::getIsExpanded () const {
	return mbExpanded;
}
//*********************************************************************
// Function:    getWaited
//
// Description: Function returns whether or not a circle has waited
//
// Parameters:  none
//
// Returned:    true if the circle has waited
//*********************************************************************
bool ExpandingCircle::getWaited () const {
	return mbWaited;
}
//*********************************************************************
// Function:    getIsContracted
//
// Description: Function returns whether or not a circle has fully
//						  contracted
//
// Parameters:  none
//
// Returned:    true if the circle has contracted
//*********************************************************************
bool ExpandingCircle::getIsContracted () const {
	return mbContracted;
}