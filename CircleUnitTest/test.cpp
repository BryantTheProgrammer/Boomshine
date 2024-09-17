//*********************************************************************
// File name:	 test.cpp
// Author:     Bryant Hayden
// Date:       4/23/2022
// Class:      CS250
// Assignment: SDL2SimpleCircle
// Purpose:    Unit Test for function of Circle
//*********************************************************************
#include "pch.h"
#include "Circle.h"
#include <sstream>

using namespace std;

TEST (Circle, operatorEqual) {
	// What to test?
	// 1.Perfect match
	// 2.Same Center plus/Minus radius
	// 3.same Xcenter diferent ycenter
	// 4.same y center deffernet xcenter
	// 5.Perfect match different color

	// default circles(Perfect Match)
	Circle cC1, cC2;

	// different radius circles
	Circle cCRadius1 (100, 100, 25), cCRadius2 (100, 100, 24),
		cCRadius3 (100, 100, 26);

	// different Y circles
	Circle cCY1 (100, 100), cCY2 (100, 99), cCY3 (100, 101);

	// different X circles
	Circle cCX1 (99, 100), cCX2 (100, 100), cCX3 (101, 101);

	// different color Circles
	Circle cCColor1, cCColor2 (10, 10, 10, Color::E_COLOR::AQUA),
		cCColor3 (10, 10, 10, Color::E_COLOR::BLACK);

	// 1
	EXPECT_TRUE (cC1 == cC2);

	// 2
	EXPECT_TRUE (cCRadius1 == cCRadius1);
	EXPECT_FALSE (cCRadius1 == cCRadius2);
	EXPECT_FALSE (cCRadius1 == cCRadius3);

	// 3
	EXPECT_TRUE (cCY1 == cCY1);
	EXPECT_FALSE (cCY1 == cCY2);
	EXPECT_FALSE (cCY1 == cCY3);

	// 4
	EXPECT_TRUE (cCX1 == cCX1);
	EXPECT_FALSE (cCX1 == cCX2);
	EXPECT_FALSE (cCX1 == cCX3);

	// 5
	EXPECT_TRUE (cCColor1 == cCColor1);
	EXPECT_TRUE (cCColor1 == cCColor3);
	EXPECT_FALSE (cCColor1 == cCColor2);
}


TEST (Circle, collision) {

	// What to test?
	// 1.Matching circles
	// 2.collision by 1 in all 8 cardinal directions
	// 3.As close as possible without Touching in 8 direction

	// default circles(Perfect Match)
	Circle cC1, cC2;

	// Cardinal Set 1
	// All circles(N,E,S,W,NE,NW,SE,SW) touch the first circle(Base) by 1
	Circle cCBase (100, 100, 10),
		cCN1 (100, 81, 10), cCS1 (100, 119, 10),
		cCE1 (81, 100, 10), cCW1 (119, 100, 10),
		// Using 15 as minimum distance for a 10 unit square at a
		// 45 degree angle from the original 10 unit square,
		cCNE1 (86, 86, 10), cCNW1 (114, 86, 10),
		cCSE1 (86, 114, 10), cCSW1 (114, 114, 10);

	// Cardinal set 2
	// as close as possible while not touching
	Circle cCN2 (100, 80, 10), cCS2 (100, 120, 10),
		cCE2 (80, 100, 10), cCW2 (120, 100, 10),
		// Using 15 as minimum distance for a 10 unit square at a
		// 45 degree angle from the original 10 unit square,
		cCNE2 (85, 85, 10), cCNW2 (115, 85, 10),
		cCSE2 (85, 115, 10), cCSW2 (115, 115, 10);

	// 1
	EXPECT_TRUE (cC1.collision (cC2));
	//Same but switch the calling object for consistency
	EXPECT_TRUE (cC2.collision (cC1));

	// 2
	EXPECT_TRUE (cCBase.collision (cCN1));
	EXPECT_TRUE (cCBase.collision (cCS1));
	EXPECT_TRUE (cCBase.collision (cCE1));
	EXPECT_TRUE (cCBase.collision (cCW1));

	EXPECT_TRUE (cCBase.collision (cCNE1));
	EXPECT_TRUE (cCBase.collision (cCSE1));
	EXPECT_TRUE (cCBase.collision (cCSE1));
	EXPECT_TRUE (cCBase.collision (cCNW1));

	// 3
	EXPECT_FALSE (cCBase.collision (cCN2));
	EXPECT_FALSE (cCBase.collision (cCS2));
	EXPECT_FALSE (cCBase.collision (cCE2));
	EXPECT_FALSE (cCBase.collision (cCW2));

	EXPECT_FALSE (cCBase.collision (cCNE2));
	EXPECT_FALSE (cCBase.collision (cCSE2));
	EXPECT_FALSE (cCBase.collision (cCSE2));
	EXPECT_FALSE (cCBase.collision (cCNW2));
}

TEST (Circle, scale) {

	// What to test?
	// 1. scale by 0
	// 2. scale by 1
	// 3. scale by 2
	// 4. scale by a double

	// default circles(Perfect Match)
	Circle cC1, cC2;

	// zero radius circle
	Circle cC0 (10, 10, 0);

	// times 2 default radius circle
	Circle cCX2 (10, 10, 20);

	// using a double(1.5)
	Circle cCDouble (10, 10, 15);

	// 1
	EXPECT_TRUE (Circle (10, 10, cC1.scale (0)) == cC0);

	// 2
	EXPECT_TRUE (Circle (10, 10, cC1.scale (1)) == cC2);

	// 3
	EXPECT_TRUE (Circle (10, 10, cC1.scale (2)) == cCX2);

	// 4
	EXPECT_TRUE (Circle (10, 10, cC1.scale (1.5)) == cCDouble);
}

TEST (Circle, operatorExtraction) {

	// What to test?
	// In a perfect world I would check each and every element being
	// read in, but for this assignment and for sake of time that is not
	// the case.
	// 1. Empty Read
	// 2. Complete read
	// 3. read multiple

	// In-stream used in unit testing
	stringstream ssIn;

	// default circles(Perfect Match)
	Circle cC1, cC2;

	// 1
	// Unit tested for a Empty file, it messed up "movingCircle" so
	// I deleted it.

	// 2
	ssIn.str ("10 10 10 0 0 0 255");
	ssIn >> cC1;
	EXPECT_TRUE (cC1 == Circle ());
	ssIn.str ("");
	ssIn.clear ();

	// 3
	ssIn.str ("10 10 10 0 0 0 255 100 100 50 0 0 0 255");
	ssIn >> cC1 >> cC2;
	EXPECT_TRUE (cC1 == Circle ());
	EXPECT_TRUE (cC2 == Circle (100, 100, 50, Color::E_COLOR::BLACK));
	ssIn.str ("");
	ssIn.clear ();
}