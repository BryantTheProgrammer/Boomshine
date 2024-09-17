//**********************************************************************
// File name:	 SDLSprite.h
// Author:     Computer Science, Pacific University
// Date:       
// Class:      
// Assignment: 
// Purpose:    
//**********************************************************************

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

//class SDLManager;

class SDLSprite {
public:
	static int spriteNum;
	SDLSprite (std::string spriteName, int xCoord, int yCoord);
	~SDLSprite ();
	std::string getName () const;
	virtual void draw () const;
	int getX () const;
	void setX (int xCoord);
	int getY () const;
	void setY (int yCoord);
	int getID () const { return mSpriteID; }
	int getWidth () const;
	int getHeight () const;
	void setScale (double scale);
	void setRotation (double rotation);
	double getRotation () const;
	bool clicked (int x, int y);

private:
	std::string mSpriteName;
	int mSpriteID;
	int mXCoord, mYCoord;
	int mHeight, mWidth;
	double mScale = 1.0;
	double mRotationInDegrees = 0.0;
};