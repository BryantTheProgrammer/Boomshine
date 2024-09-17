//**********************************************************************
// File name:	 SDLSprite.cpp
// Author:     Computer Science, Pacific University
// Date:       
// Class:      
// Assignment: 
// Purpose:    
//**********************************************************************

#include "SDLSprite.h"
#include "SDLManager.h"

int SDLSprite::spriteNum = 0;

SDLSprite::SDLSprite (std::string spriteName, int xCoord, int yCoord) {
	SDLManager &rcSDLManager = SDLManager::instance ();
	SpriteDimensions sSpriteDimensions;

	//strcpy_s (mFileName, MAX_NAME_LEN, pszFileName);
	mSpriteName = spriteName;
	mXCoord = xCoord;
	mYCoord = yCoord;
	sSpriteDimensions = rcSDLManager.loadSprite (mSpriteName.c_str ());
	mHeight = sSpriteDimensions.height;
	mWidth = sSpriteDimensions.width;
	mSpriteID = spriteNum++;
}

SDLSprite::~SDLSprite () {

}

std::string SDLSprite::getName () const {
	return mSpriteName;
}

void SDLSprite::draw () const {
	SDLManager &rcSDLManager = SDLManager::instance ();
	rcSDLManager.drawSprite (*this);
}

int SDLSprite::getX () const {
	return mXCoord;
}

int SDLSprite::getY () const {
	return mYCoord;
}

void SDLSprite::setX (int xCoord) {
	mXCoord = xCoord;
}

void SDLSprite::setY (int yCoord) {
	mYCoord = yCoord;
}

//**********************************************************************
// Function:    setScale
//
// Description: Set the scaling factor for the Sprite.  
//
// Parameters:  scale - the scaling factor. 
//              1.0 is no change. <1.0 is shrink, >1.0 is expand
//
// Returned:    None
//**********************************************************************
void SDLSprite::setScale (double scale) {
	mScale = scale;
}

//**********************************************************************
// Function:    setRotation
//
// Description: Set the angle of rotation of the sprite.
//
// Parameters:  rotation - the degrees of rotation, 0.0 to 359.0
//
// Returned:    None
//**********************************************************************
void SDLSprite::setRotation (double rotation) {
	mRotationInDegrees = rotation;
}

//**********************************************************************
// Function:    getRotation
//
// Description: Get the angle of rotation of the sprite.
//
// Parameters:  None
//
// Returned:    the rotation of the sprite
//**********************************************************************
double SDLSprite::getRotation () const {
	return mRotationInDegrees;
}

//**********************************************************************
// Function:    clicked
//
// Description: determine if the sprite has been clicked
//
// Parameters:  x - x coordinate of mouse click on screen
//              y - y coordinate of mouse click on screen
//
// Returned:    true if the x,y falls inside the sprite
//**********************************************************************
bool SDLSprite::clicked (int x, int y) {
	bool bRetVal = false;
	if (x >= mXCoord && x <= mXCoord + mWidth &&
		y >= mYCoord && y <= mYCoord + mHeight) {
		bRetVal = true;
		//clickEventHandler ();
	}

	return bRetVal;
}

//**********************************************************************
// Function:    getWidth
//
// Description: Get the width
//
// Parameters:  None
//
// Returned:    the width
//**********************************************************************
int SDLSprite::getWidth () const {
	return static_cast<int>(mWidth * mScale);
}

//**********************************************************************
// Function:    getHeight
//
// Description: Get the height
//
// Parameters:  None
//
// Returned:    the height
//**********************************************************************
int SDLSprite::getHeight () const {
	return static_cast<int>(mHeight * mScale);
}
