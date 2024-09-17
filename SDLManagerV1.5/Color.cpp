//**********************************************************************
// File name:	 Color.h
// Author:     Computer Science, Pacific University
// Date:       
// Class:      CS250
// Assignment: 
// Purpose:    
//**********************************************************************
#include "Color.h"

const uint8_t Color::maRGBA[][Color::RGBA] =
{
	{ 0, 0, 0, 255 },						// black
{ 128, 128, 128, 255 },				// gray
{ 192, 192, 192, 255 },				// silver
{ 255, 255, 255, 255 },				// white	
{ 128, 0, 0, 255 },						// maroon
{ 255, 0, 0, 255 },						// red
{ 128, 128, 0, 255 },					// olive
{ 255, 255, 0, 255 },					// yellow	
{ 0, 128, 0, 255 },						// green
{ 0, 255, 0, 255 },						// lime
{ 0, 128, 128, 255 },					// teal
{ 0, 255, 255, 255 },					// aqua	
{ 0, 0, 128, 255 },						// navy
{ 0, 0, 255, 255 },						// blue
{ 128, 0, 128, 255 },					// purple
{ 255, 0, 255, 255 }					// fuchsia
};

Color Color::getColor (E_COLOR eColor) {
	uint8_t color = static_cast<uint8_t> (eColor);
	return Color (maRGBA [color][R], maRGBA [color][G], maRGBA [color][B],
		maRGBA [color][A]);
}

Color::Color (E_COLOR eColor) {
	uint8_t color = static_cast<uint8_t> (eColor);
	mR = maRGBA [color][R];
	mG = maRGBA [color][G];
	mB = maRGBA [color][B];
	mA = maRGBA [color][A];
}
//**********************************************************************
// Constructor: Color
//
// Description: Initialize rgba
//
// Parameters:  r - red
//              g - green
//              b - blue 
//              a - alpha, all parameter are in the range 0-255
//
// Returned:    None
//**********************************************************************
Color::Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	mR = r;
	mG = g;
	mB = b;
	mA = a;
}

//**********************************************************************
// Function:    getR
//
// Description: Get the red component
//
// Parameters:  none
//
// Returned:    the red component
//**********************************************************************
uint8_t Color::getR () const {
	return mR;
}

//**********************************************************************
// Function:    getG
//
// Description: Get the green component
//
// Parameters:  none
//
// Returned:    the green component
//**********************************************************************
uint8_t Color::getG () const {
	return mG;
}

//**********************************************************************
// Function:    getB
//
// Description: Get the blue component
//
// Parameters:  none
//
// Returned:    the blue component
//**********************************************************************
uint8_t Color::getB () const {
	return mB;
}

//**********************************************************************
// Function:    getA
//
// Description: Get the alpha component
//
// Parameters:  none
//
// Returned:    the alpha component
//**********************************************************************
uint8_t Color::getA () const {
	return mA;
}

//**********************************************************************
// Function:    setOpacity
//
// Description: set the alpha component (Opacity). 0=transparent, 1= opaque
//
// Parameters:  opacity - value from 0.0 to 1.0 to determine Opacity
//
// Returned:    none
//**********************************************************************
void Color::setOpacity (float opacity) {
	if (opacity >= 0.0 && opacity <= 1.0) {
		mA = static_cast<uint8_t>(opacity * 255);
	}
}

//**********************************************************************
// Function:    operator>>
//
// Description: Read in the Color from a stream
//
// Parameters:  rcInStream - the stream to read from
//              rcColor    - the Color to read into
//
// Returned:    the modified stream
//**********************************************************************
std::istream &operator>> (std::istream &rcInStream, Color &rcColor) {
	int r, g, b, a;

	rcInStream >> r >> g >> b >> a;

	rcColor.mR = static_cast<uint8_t> (r);
	rcColor.mG = static_cast<uint8_t> (g);
	rcColor.mB = static_cast<uint8_t> (b);
	rcColor.mA = static_cast<uint8_t> (a);

	return rcInStream;
}
