//**********************************************************************
// File name:	 Color.h
// Author:     Computer Science, Pacific University
// Date:       
// Class:      CS250
// Assignment: 
// Purpose:    
//**********************************************************************
#pragma once

#include <iostream>
#include <cstdint>

class Color {
public:
	static const uint8_t RGBA = 4;
	static const uint8_t R = 0;
	static const uint8_t G = 1;
	static const uint8_t B = 2;
	static const uint8_t A = 3;

	enum class E_COLOR : uint8_t {
		BLACK, GRAY, SILVER, WHITE, MAROON, RED, OLIVE, YELLOW,
		GREEN, LIME, TEAL, AQUA, NAVY, BLUE, PURPLE, FUCHSIA
	};
	static Color getColor (E_COLOR eColor);

	Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0);
	Color (E_COLOR eColor = E_COLOR::BLACK);

	uint8_t getR () const;
	uint8_t getG () const;
	uint8_t getB () const;
	uint8_t getA () const;

	void setOpacity (float opacity);

	friend std::istream &operator >> (std::istream &rcInStream,
		Color &rcColor);

private:
	uint8_t mR, mG, mB, mA;
	static const uint8_t maRGBA[][RGBA];
};
