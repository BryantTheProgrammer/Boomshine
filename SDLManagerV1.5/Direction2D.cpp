//********************************************************************** 
// File name:	 Direction2D.cpp
// Author:		 Computer Science, Pacific University
// Date:		   
// Class:		   CS 250
// Assignment: 
// Purpose:		 Implement a 2D direction
//**********************************************************************

#include "Direction2D.h"
#include <iostream>
#include <string>

// The following lookup table is used to help convert string 
// directions to  an enum direction.

const std::string Direction2D::CompassDirectionNames[] =
{
	// 0    1     2    3     4    5     6    7
	"N", "NE", "E", "SE", "S", "NW", "W", "SW"
};

// The following lookup table is used to increment the current X and Y
// positions based on the direction of travel.

const int Direction2D::MoveLookup[][Direction2D::NUMBER_OF_COORDINATES] =
{
	{ 0, -1 },	// NORTH
	{ 1, -1 },	// NORTHEAST
	{ 1, 0 },		// EAST
	{ 1, 1 },		// SOUTHEAST
	{ 0, 1 },		// SOUTH
	{ -1, -1 },	// NORTHWEST
	{ -1, 0 },	// WEST
	{ -1, 1 }		// SOUTHWEST
};

// The following lookup table is used to determine the new direction for
// a reflection. For instance, if an object is moving N and hits the top
//  edge, the new direction is S.

// Order is: Top, Right, Bottom, Left reflection of 1 of 8 directions 
// where N = 0, NE = 1, E = 2, SE = 3, S = 4, NW = 5, W = 6, SW = 7
const Direction2D::E_Compass_Direction
Direction2D::ReflectLookup[][Direction2D::NUMBER_OF_SIDES] =
{
	{ Direction2D::E_Compass_Direction::S,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X },		//N

	{ Direction2D::E_Compass_Direction::SE,
	Direction2D::E_Compass_Direction::NW,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X },	  //NE

	{ Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::W,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X },		//E

	{ Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::SW,
	Direction2D::E_Compass_Direction::NE,
	Direction2D::E_Compass_Direction::X },    //SE

	{ Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::N,
	Direction2D::E_Compass_Direction::X },		//S

	{ Direction2D::E_Compass_Direction::SW,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::NE },   //NW

	{ Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::E },		//W

	{ Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::X,
	Direction2D::E_Compass_Direction::NW,
	Direction2D::E_Compass_Direction::SE }	  //SW
};
//**********************************************************************
// Constructor:	Direction2D
//
// Description:	Initialize the Direction to the argument given
//
// Parameters:	eDirection - the direction to use
//
// Returned:		none
//**********************************************************************
Direction2D::Direction2D (E_Compass_Direction eDirection) {

	meCompassDirection = eDirection;

	setMoveByCompassDirection ();
}

//**********************************************************************
// Method:	    setMoveByCompassDirection
//
// Description:	Set the x and y movement based on the current 
//              compass direction
//
// Parameters:  none
//
// Returned:	  none
//**********************************************************************
void Direction2D::setMoveByCompassDirection () {
	const int X_CHANGE = 0;
	const int Y_CHANGE = 1;
	if (meCompassDirection < Direction2D::E_Compass_Direction::N ||
		meCompassDirection > Direction2D::E_Compass_Direction::SW) {
		mXMove = 0;
	}
	const unsigned int direction =
		static_cast<unsigned int> (meCompassDirection);
	mXMove = MoveLookup [direction % NUMBER_OF_DIRECTIONS][X_CHANGE];
	mYMove = MoveLookup [direction % NUMBER_OF_DIRECTIONS][Y_CHANGE];
}

//**********************************************************************
// Method:	    getCompassDirection
//
// Description:	get the current compass direction
//
// Parameters:  none
//
// Returned:	  the current compass direction
//**********************************************************************
Direction2D::E_Compass_Direction Direction2D::getCompassDirection ()
const {
	return meCompassDirection;
}

//**********************************************************************
// Method:	    reflectOnTop
//
// Description:	change the compass direction to reflect a bounce off 
//              the top of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//**********************************************************************
Direction2D::E_Compass_Direction Direction2D::reflectOnTop () const {
	uint8_t xDirection = static_cast<uint8_t> (meCompassDirection),
		yDirection = static_cast<uint8_t>
		(Direction2D::E_BOUNDING_BOX_SIDE::TOP_SIDE);

	return Direction2D::E_Compass_Direction
	(static_cast<Direction2D::E_Compass_Direction>
		(ReflectLookup [xDirection][yDirection]));
}

//**********************************************************************
// Method:	    reflectOnRightSide
//
// Description:	change the compass direction to reflect a bounce off 
//              the right side of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//**********************************************************************
Direction2D::E_Compass_Direction Direction2D::reflectOnRightSide () const {
	uint8_t xDirection = static_cast<uint8_t> (meCompassDirection),
		yDirection = static_cast<uint8_t>
		(Direction2D::E_BOUNDING_BOX_SIDE::RIGHT_SIDE);
	return Direction2D::E_Compass_Direction
	(static_cast<Direction2D::E_Compass_Direction>
		(ReflectLookup [xDirection][yDirection]));
}

//**********************************************************************
// Method:	    reflectOnBottom
//
// Description:	change the compass direction to reflect a bounce off the 
//              bottom of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//**********************************************************************
Direction2D::E_Compass_Direction Direction2D::reflectOnBottom () const {
	uint8_t xDirection = static_cast<uint8_t> (meCompassDirection),
		yDirection = static_cast<uint8_t>
		(Direction2D::E_BOUNDING_BOX_SIDE::BOTTOM_SIDE);
	return Direction2D::E_Compass_Direction
	(static_cast<Direction2D::E_Compass_Direction>
		(ReflectLookup [xDirection][yDirection]));
}

//**********************************************************************
// Method:	    reflectOnLeftSide
//
// Description:	change the compass direction to reflect a bounce off the
//               side of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//**********************************************************************
Direction2D::E_Compass_Direction Direction2D::reflectOnLeftSide () const {
	uint8_t xDirection = static_cast<uint8_t> (meCompassDirection),
		yDirection = static_cast<uint8_t>
		(Direction2D::E_BOUNDING_BOX_SIDE::LEFT_SIDE);
	return Direction2D::E_Compass_Direction
	(static_cast<Direction2D::E_Compass_Direction>
		(ReflectLookup [xDirection][yDirection]));
}

//**********************************************************************
// Method:	    getXMove
//
// Description:	get the current X move
//
// Parameters:  none
//
// Returned:	  the current X move
//**********************************************************************
int Direction2D::getXMove () const {
	return mXMove;
}

//**********************************************************************
// Method:	    getYMove
//
// Description:	get the current Y move
//
// Parameters:  none
//
// Returned:	  the current Y move
//**********************************************************************
int Direction2D::getYMove () const {
	return mYMove;
}

//**********************************************************************
// Function:	  operator>> (friend of the class)
//
// Description:	Read in a direction from the stream. The direction in 
//              the file must be written as a string that matches a 
//              value in Direction2D::CompassDirectionNames
//
// Parameters:  rcInStream  - the stream to read from
//              rcDirection - the direction to fill
//
// Returned:	  the modified stream read from
//**********************************************************************

std::istream &operator>>(std::istream &rcInStream,
	Direction2D &rcDirection) {
	std::string compassDirection;

	rcInStream >> compassDirection;

	rcDirection.setCompassDirection (compassDirection);

	return rcInStream;
}

//**********************************************************************
// Method:	    setCompassDirection
//
// Description:	Set the compass direction based on a string that matches
//              a value in Direction2D::CompassDirectionNames and also
//              set the x and y move.
//
// Parameters:  compassDirection - the name of the direction
//
// Returned:	  none
//**********************************************************************
void Direction2D::setCompassDirection (std::string compassDirection) {
	for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++) {
		if (CompassDirectionNames [i] == compassDirection) {
			meCompassDirection = static_cast<E_Compass_Direction> (i);
		}
	}
	setMoveByCompassDirection ();
}
