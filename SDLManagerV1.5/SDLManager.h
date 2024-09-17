//**********************************************************************
// File name:	 SDLManager.h
// Author:     Computer Science, Pacific University
// Date:       
// Class:      
// Assignment: 
// Purpose:    
//**********************************************************************

#pragma once
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "Color.h"
#include "SDLSprite.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::vector<TTF_Font *>::size_type font_index;
typedef struct {
	int height, width;
} SpriteDimensions;

class SDLManager {
public:
	static SDLManager &instance (); // Follows meyers singleton pattern

	//********************************************************************
	// Window Routines
	//********************************************************************
	void initializeWorld (int windowXPosition, int windowYPosition,
		int windowXSize, int windowYSize,
		const char szWindowName[] = WINDOW_NAME,
		const std::string &rcFontLocation = DEFAULT_FONT,
		int fontSize = DEFAULT_FONT_SIZE,
		const Color &rcBackgroundColor = DEFAULT_BACKGROUND,
		const Color &rcForegroundColor = DEFAULT_FOREGROUND,
		const uint8_t fps = DEFAULT_FPS);

	int windowWidth () const;
	int windowHeight () const;
	void clearBackground () const;
	void setBackgroundColor (const Color &rcColor);
	void setForegroundColor (const Color &rcColor);
	void raiseWindow ();
	void render () const;

	//********************************************************************
	// Graphics Primitives Routines
	//********************************************************************
	int plotPixel (int xCoord, int yCoord) const;
	int plotPixel (int xCoord, int yCoord, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	int plotPixel (int xCoord, int yCoord, const Color &rcColor) const;

	int drawLine (int x1, int y1, int x2, int y2);
	int drawLine (int x1, int y1, int x2, int y2,
		uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	int drawLine (int x1, int y1, int x2, int y2, const Color &rcColor);

	int drawCircle (int xCenter, int yCenter, int radius) const;
	int drawCircle (int xCenter, int yCenter, int radius,
		uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	int drawCircle (int xCenter, int yCenter, int radius,
		const Color &rcColor) const;

	int drawFilledCircle (int xCenter, int yCenter, int radius) const;
	int drawFilledCircle (int xCenter, int yCenter, int radius,
		uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	int drawFilledCircle (int xCenter, int yCenter, int radius,
		const Color &rcColor) const;

	//********************************************************************
	// Timing Routines
	//********************************************************************

	void animationStart ();
	void animationStop ();
	bool animationIsRunning ();

	//********************************************************************
	// Text Routines
	//********************************************************************

	void displayText (int x, int y, std::string msg, Color cRgba);
	void displayText (int x, int y, std::string msg);
	int loadFont (std::string fontname, int size);
	bool displayText (int x, int y, std::string msg, Color cRgba, int font);

	//********************************************************************
	// Sprite Routines
	//********************************************************************

	SpriteDimensions loadSprite (const char *pszName);
	void drawSprite (const SDLSprite &rcSDLSprite);
	void rotateSprite (SDLSprite &rcSDLSprite, double degrees);

	//********************************************************************
	// Event-handling Routines
	//********************************************************************

	bool getSDLEvent (SDL_Event &ruEvent) const;

	static const uint8_t DEFAULT_FPS;

private:
	static const Color DEFAULT_FOREGROUND, DEFAULT_BACKGROUND;
	static const char WINDOW_NAME[];
	static const std::string DEFAULT_FONT;
	static const int DEFAULT_FONT_SIZE;
	static const int AUDIO_SETTINGS;
	static const int AUDIO_RATE;

	SDLManager ();
	~SDLManager (); // DestroyRenderer, DestroyWindow, Quit

	void startFrame ();
	void sleepUntilFrameEnd ();

	/*
	* Included per recommendation for Meyers singletons
	* (http://www.cs.fsu.edu/~lacher/lectures/Output/loki6/script.html)
	*/

	//Prevents implicit copy
	SDLManager (SDLManager const &_) = delete;

	//Prevents explicit copy
	void operator= (SDLManager const &_) = delete;

	SDL_Window *mpcWindow;
	SDL_Renderer *mpcRenderer;

	uint32_t mFrameStartTick;
	uint8_t mFPS;

	std::vector<TTF_Font *> mcFonts;
	std::map<std::string, SDL_Texture *> mTextures;
	unsigned int mActiveFontIndex;
	Color mcBackgroundColor, mcForegroundColor;

	Mix_Chunk *mpsAudioBuffer;

	bool mbInitialized;
	bool mbIsAnimating;
	int mBasicFont;
};
