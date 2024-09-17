//**********************************************************************
// File name:	 Direction2D.h
// Author:		 Computer Science, Pacific University
// Date:		   
// Class:		   CS 250
// Assignment: 
// Purpose:		 Represent a two-dimensional direction
//**********************************************************************

#pragma once

#include <iostream>
#include <cstdint>
//#include "SDL.h"

class Direction2D {
public:
	static const unsigned short int NUMBER_OF_COORDINATES = 2;

	static const unsigned short int NUMBER_OF_DIRECTIONS = 8;
	enum class E_Compass_Direction : uint8_t {
		N, NE, E, SE, S, NW, W, SW, X // X is invalid
	};

	static const unsigned short int NUMBER_OF_SIDES = 4;
	enum class E_BOUNDING_BOX_SIDE : uint8_t {
		TOP_SIDE, RIGHT_SIDE, BOTTOM_SIDE, LEFT_SIDE
	};

	static const std::string CompassDirectionNames[];
	static const int MoveLookup[][NUMBER_OF_COORDINATES];
	static const Direction2D::E_Compass_Direction
		ReflectLookup[][NUMBER_OF_SIDES];


	Direction2D (E_Compass_Direction = E_Compass_Direction::N);

	Direction2D::E_Compass_Direction reflectOnLeftSide () const;
	Direction2D::E_Compass_Direction reflectOnRightSide () const;
	Direction2D::E_Compass_Direction reflectOnTop () const;
	Direction2D::E_Compass_Direction reflectOnBottom () const;

	int getXMove () const;
	int getYMove () const;

	E_Compass_Direction getCompassDirection () const;

	friend std::istream &operator>> (std::istream &rcInStream,
		Direction2D &rcDirection);

private:
	E_Compass_Direction meCompassDirection;
	int mXMove;
	int mYMove;

	void setCompassDirection (std::string compassDirection);
	void setMoveByCompassDirection ();

};
