#pragma once

#include "SDLManager.h"
#include "Color.h"
#include <iostream>

class Circle {
public:
	Circle (int xCenter = 10, int yCenter = 10, int radius = 10,
		const Color &rcColor = Color::getColor (Color::E_COLOR::BLACK));
	Circle (const Circle &rcCircle);
	void draw (SDLManager &rcManager) const;
	bool collision (const Circle &cOtherCircle) const;
	double scale (double scaleFactor);

	bool operator==(const Circle &rcOtherCircle) const;

	friend std::istream &operator>> (std::istream &rcInStream,
		Circle &rcCircle);

protected:
	int mXCenter, mYCenter, mRadius;
	Color mcColor;
};