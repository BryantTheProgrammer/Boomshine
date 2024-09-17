//**********************************************************************
// File name:	 SDLManager.cpp
// Author:     Computer Science, Pacific University
// Date:
// Class:
// Assignment:
// Purpose:
//**********************************************************************
#include "SDLManager.h"
#include "SDLSprite.h"
#include <algorithm>
#include <map>
#include <string>

const char SDLManager::WINDOW_NAME[] = "Graphics";
const std::string SDLManager::DEFAULT_FONT = "C:/Windows/Fonts/cour.ttf";
const int SDLManager::DEFAULT_FONT_SIZE = 35;

// OR flags like MIX_INIT_FLAC | MIX_INIT_MOD| MIX_INIT_MP3 | MIX_INIT_OGG;
const int SDLManager::AUDIO_SETTINGS = 0;
const int SDLManager::AUDIO_RATE = 22050;

const Color SDLManager::DEFAULT_BACKGROUND = { 255, 255, 255, 255 };
const Color SDLManager::DEFAULT_FOREGROUND = { 0, 0, 0, 0 };
const uint8_t SDLManager::DEFAULT_FPS = 60;

/*******************************************************************************
* Method:      instance
*
* Description: Retrieve the SDLManager instance for this program
*
* Parameters:  None
*
* Returned:    A reference to the SDLManager instance
******************************************************************************/
SDLManager &SDLManager::instance () {
	/*
	*  See also:
	*  https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Construct_On_First_Use
	*/
	static SDLManager cInstance;
	return cInstance;
}


/*******************************************************************************
* Constructor: SDLManager
*
* Description: Construct the SDLManager, defaulting necessary values
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
SDLManager::SDLManager () {
	mbInitialized = false;
	mpcWindow = nullptr;
	mpcRenderer = nullptr;
	mcBackgroundColor = DEFAULT_BACKGROUND;
	mcForegroundColor = DEFAULT_FOREGROUND;
	mFPS = DEFAULT_FPS;
	mpsAudioBuffer = nullptr;
	mbIsAnimating = false;
	TTF_Init ();
	mBasicFont = loadFont (DEFAULT_FONT, DEFAULT_FONT_SIZE);
}

/*******************************************************************************
* Destructor:  ~SDLManager
*
* Description: Destruct the SDLManager, freeing all associated memory
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
SDLManager::~SDLManager () {
	for (font_index i = 0; i < mcFonts.size (); ++i) {
		TTF_CloseFont (mcFonts [i]);
		mcFonts.erase (mcFonts.begin () + i);
	}
	Mix_CloseAudio ();
	Mix_Quit ();
	SDL_DestroyRenderer (mpcRenderer);
	SDL_DestroyWindow (mpcWindow);

	for (auto iter = mTextures.begin (); iter != mTextures.end (); ++iter) {
		if (mTextures [iter->first] != NULL) {
			SDL_DestroyTexture (mTextures [iter->first]);
		}
	}
	//SDL_DestroyTexture (mpsTexture);
	SDL_Quit ();
}



/*******************************************************************************
* Method:      initializeWorld
*
* Description: Create an SDL window, renderer, etc. Your program should only
*              call ONE initializeWorld function.
*
* Parameters:  windowXPosition   - The X-coordinate for the window to be
*                                  spawned at
*              windowYPosition   - The Y-coordinate for the window to be
*                                  spawned at
*              windowXSize       - The X-width in pixels of the window to spawn
*              windowYSize       - The Y-height in pixels of the window to
*                                  spawn
*              rcFontLocation    - A reference to a string containing the path
*                                  to the font that the game should register as
*                                  font 0. Defaults to SDLManager::DEFAULT_FONT
*              fontSize          - The font 0 size (in 72dpi pt) that the game
*                                  world should use. Defaults to
*                                  SDLManager::DEFAULT_FONT_SIZE
*              rcBackgroundColor - A reference to the Color to use for the
*                                  background Defaults to
*                                  SDLManager::DEFAULT_BACKGROUND
*
* Returned:    None
******************************************************************************/
void SDLManager::initializeWorld (int windowXPosition, int windowYPosition,
	int windowXSize, int windowYSize,
	const char szWindowName[],
	const std::string &rcFontLocation,
	int fontSize, const Color &rcBackgroundColor,
	const Color &rcForegroundColor,
	const uint8_t fps) {
	std::cout << "initWorld called" << std::endl;
	if (mbInitialized) {
		throw "Sorry, you can only use an initializeWorld function once!";
	}
	mbInitialized = true;


	if (-1 == SDL_Init (SDL_INIT_EVERYTHING)) {
		throw "SDL Initialization failed";
	}
	//We'll use mono here. Changing the 1 to a 2 will use stereo
	if (-1 == Mix_OpenAudio (AUDIO_RATE, MIX_DEFAULT_FORMAT, 1, 1024)) {
		throw "SDL Audio setup failed with error " + std::string (Mix_GetError ());
	}
	if (Mix_Init (AUDIO_SETTINGS) != AUDIO_SETTINGS) {
		throw "SDL audio library missing";
	}
	Mix_Volume (-1, MIX_MAX_VOLUME);


	TTF_Init ();
	mpcWindow = SDL_CreateWindow (szWindowName, windowXPosition,
		windowYPosition, windowXSize, windowYSize, 0);
	if (nullptr == mpcWindow) {
		throw "Failed to create SDL Window";
	}

	mpcRenderer = SDL_CreateRenderer (mpcWindow, -1, 0);
	if (nullptr == mpcRenderer) {
		throw "Failed to create SDL Renderer";
	}

	//setFont (registerFont (rcFontLocation, fontSize));
	/*
	* The following code is essentially copy/pasted from the original
	* "HelloChadd" Main.cpp
	*/
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize (mpcRenderer, windowXSize, windowYSize);
	setBackgroundColor (rcBackgroundColor);
	setForegroundColor (rcForegroundColor);
	mFPS = fps;
}

/*******************************************************************************
* Method:      windowWidth
*
* Description: Get the size in pixels of the SDLManager's window's width
*
* Parameters:  None
*
* Returned:    The size as described
******************************************************************************/
int SDLManager::windowWidth () const {
	int width, height;
	SDL_GetWindowSize (mpcWindow, &width, &height);
	return width;
}

/*******************************************************************************
* Method:      windowHeight
*
* Description: Get the size in pixels of the SDLManager's window's height
*
* Parameters:  None
*
* Returned:    The size as described
******************************************************************************/
int SDLManager::windowHeight () const {
	int width, height;
	SDL_GetWindowSize (mpcWindow, &width, &height);
	return height;
}

/*******************************************************************************
* Method:      drawBlankBackground
*
* Description: Clear the background and fill it with the background Color
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLManager::clearBackground () const {
	SDL_SetRenderDrawColor (mpcRenderer, mcBackgroundColor.getR (),
		mcBackgroundColor.getG (), mcBackgroundColor.getB (),
		mcBackgroundColor.getA ()); SDL_RenderClear (mpcRenderer);
}

/*******************************************************************************
* Method:      setBackgroundColor
*
* Description: Set the background Color of the game world
*
* Parameters:  rcColor - a reference to the Color to set the background to
*
* Returned:    None
******************************************************************************/
void SDLManager::setBackgroundColor (const Color &rcColor) {
	mcBackgroundColor = rcColor;
}

/*******************************************************************************
* Method:      setForegroundColor
*
* Description: Set the foreground Color the SDLManager should render with
*
* Parameters:  rcColor - a reference to the Color to set the foreground to
*
* Returned:    None
******************************************************************************/
void SDLManager::setForegroundColor (const Color &rcColor) {
	mcForegroundColor = rcColor;
	SDL_SetRenderDrawColor (mpcRenderer, mcForegroundColor.getR (),
		mcForegroundColor.getG (), mcForegroundColor.getB (),
		mcForegroundColor.getA ());
}

/*******************************************************************************
* Method:      raiseWindow
*
* Description: Raise the SDLManager's window to the top
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLManager::raiseWindow () {
	SDL_RaiseWindow (mpcWindow);
}

/*******************************************************************************
* Method:      render
*
* Description: Replace the current image in the frame with the drawn image
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLManager::render () const {
	SDL_RenderPresent (mpcRenderer);
}

/*******************************************************************************
* Method:      plotPixel
*
* Description: Plot a colored pixel
*
* Parameters:  xCoord  - x coordinate of pixel
*							 yCoord  - y coordinate of pixel
*							 rcColor - pixel color
*
* Returned:    0 on success; otherwise, -1
******************************************************************************/
int SDLManager::plotPixel (int xCoord, int yCoord) const {
	return pixelRGBA (mpcRenderer, xCoord, yCoord,
		mcForegroundColor.getR (), mcForegroundColor.getG (),
		mcForegroundColor.getB (), mcForegroundColor.getA ());
}

int SDLManager::plotPixel (int xCoord, int yCoord,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return pixelRGBA (mpcRenderer, xCoord, yCoord, r, g, b, a);
}

int SDLManager::plotPixel (int xCoord, int yCoord, const Color &rcColor) const {
	return pixelRGBA (mpcRenderer, xCoord, yCoord, rcColor.getR (),
		rcColor.getG (), rcColor.getB (), rcColor.getA ());
}

/*******************************************************************************
* Method:      drawLine
*
* Description: Draw a colored pixel
*
* Parameters:  x1  - x coordinate of first point
*							 y1  - y coordinate of first point
*							 x2  - x coordinate of second point
*							 y2  - y coordinate of second point
*
* Returned:    0 on success; otherwise, -1
******************************************************************************/
int SDLManager::drawLine (int x1, int y1, int x2, int y2) {
	return lineRGBA (mpcRenderer, x1, y1, x2, y2,
		mcForegroundColor.getR (), mcForegroundColor.getG (),
		mcForegroundColor.getB (), mcForegroundColor.getA ());
}

int SDLManager::drawLine (int x1, int y1, int x2, int y2,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return lineRGBA (mpcRenderer, x1, y1, x2, y2, r, g, b, a);
}

int SDLManager::drawLine (int x1, int y1, int x2, int y2, const Color &rcColor) {
	return lineRGBA (mpcRenderer, x1, y1, x2, y2, rcColor.getR (),
		rcColor.getG (), rcColor.getB (), rcColor.getA ());
}
/*******************************************************************************
* Method:      drawCircle
*
* Description: Draw a circle with center and radius
*
* Parameters:  xCenter  - x center of circle
*							 yCenter  - y center of circle
*							 radius   - radius of circle
*
* Returned:    0 on success; otherwise, -1
******************************************************************************/
int SDLManager::drawCircle (int xCenter, int yCenter, int radius) const {
	return circleRGBA (mpcRenderer, xCenter, yCenter, radius,
		mcForegroundColor.getR (), mcForegroundColor.getG (),
		mcForegroundColor.getB (), mcForegroundColor.getA ());
}

int SDLManager::drawCircle (int xCenter, int yCenter, int radius,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return circleRGBA (mpcRenderer, xCenter, yCenter, radius, r, g, b, a);
}

int SDLManager::drawCircle (int xCenter, int yCenter, int radius,
	const Color &rcColor) const {
	return circleRGBA (mpcRenderer, xCenter, yCenter, radius,
		rcColor.getR (), rcColor.getG (), rcColor.getB (),
		rcColor.getA ());
}

/*******************************************************************************
* Method:      drawFilledCircle
*
* Description: Draw a filled circle with center and radius
*
* Parameters:  xCenter  - x center of circle
*							 yCenter  - y center of circle
*							 radius   - radius of circle
*
* Returned:    0 on success; otherwise, -1
******************************************************************************/
int SDLManager::drawFilledCircle (int xCenter, int yCenter, int radius) const {
	return filledCircleRGBA (mpcRenderer, xCenter, yCenter, radius,
		mcForegroundColor.getR (), mcForegroundColor.getG (),
		mcForegroundColor.getB (), mcForegroundColor.getA ());
}

int SDLManager::drawFilledCircle (int xCenter, int yCenter, int radius,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return filledCircleRGBA (mpcRenderer, xCenter, yCenter, radius, r, g, b, a);
}

int SDLManager::drawFilledCircle (int xCenter, int yCenter, int radius,
	const Color &rcColor) const {
	return filledCircleRGBA (mpcRenderer, xCenter, yCenter, radius,
		rcColor.getR (), rcColor.getG (), rcColor.getB (),
		rcColor.getA ());
}

/*******************************************************************************
* Method:      startFrame
*
* Description: Mark the start of a frame, so that sleepUntilFrameEnd may be
*              used to regulate framerate
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLManager::startFrame () {
	mFrameStartTick = SDL_GetTicks ();
}


/*******************************************************************************
* Method:      sleepUntilFrameEnd
*
* Description: Pause thread until the next frame, performing any per-frame
*              maintenance on SDLManager itself
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLManager::sleepUntilFrameEnd () {
	uint32_t nextFrameTick = mFrameStartTick
		+ static_cast<uint32_t> (1000.0 / static_cast<double> (mFPS));
	// = 1000 * seconds/frame = ms/frame
	if (mFrameStartTick < nextFrameTick) {
		SDL_Delay (nextFrameTick - mFrameStartTick);
	}
}

void SDLManager::animationStart () {
	mbIsAnimating = true;
	startFrame ();
}

void SDLManager::animationStop () {
	mbIsAnimating = false;
}

bool SDLManager::animationIsRunning () {
	sleepUntilFrameEnd ();
	startFrame ();
	return mbIsAnimating;
}



/*******************************************************************************
* Method:      getSDLEventPtr
*
* Description: Get a pointer to a copy of the top SDL_Event off of the events
*              queue
*
* Parameters:  None
*
* Returned:    A pointer to the copy of the SDL_Event pulled, or nullptr if the
*              queue was empty. See https://wiki.libsdl.org/SDL_Event.
*              Note: Any non-null SDL_Event * returned from this function MUST
*              BE FREED by calling delete on it to prevent memory leaks.
******************************************************************************/

bool SDLManager::getSDLEvent (SDL_Event &ruEvent) const {
	return (0 != SDL_PollEvent (&ruEvent));
}

//***************************************************************************
// Function:    loadFont
//
// Description: Load the given font using the given size.
//
// Parameters:  fontname - full path to the font file
//              size - size of the font
//
// Returned:    the id of the font or -1 on error
//***************************************************************************
int SDLManager::loadFont (std::string fontname, int size) {
	TTF_Font *pFont = TTF_OpenFont (fontname.c_str (), size);
	int retVal = -1;

	if (nullptr != pFont) {
		mcFonts.push_back (pFont);
		retVal = mcFonts.size ();
	}

	return retVal;
}

//***************************************************************************
// Function:    displayText
//
// Description: Display text on the screen at the given location.
//
// Parameters:  x - x position
//              y - y position
//              msg - the text to display
//              rgba - the color of the text
//              font - the font id returned by loadFont
//
// Returned:    true or false to indicate success
//***************************************************************************
bool SDLManager::displayText (int x, int y, std::string msg, Color cRgba, int font) {
	//SDL_Color color = { mcForegroundColor.getR (), mcForegroundColor.getG (),
	//	mcForegroundColor.getB (), mcForegroundColor.getA () };

	SDL_Color color = { cRgba.getR (), cRgba.getG (),
		cRgba.getB (), cRgba.getA () };

	SDL_Surface *pSurface = TTF_RenderText_Blended (mcFonts.at (font - 1),
		msg.c_str (), color);
	if (nullptr == pSurface) {
		//std::cout << "Failed to create surface : " << SDL_GetError();
		return false;
	}

	// Map the Surface onto a Texture
	SDL_Texture *pTexture = SDL_CreateTextureFromSurface (mpcRenderer, pSurface);
	if (nullptr == pTexture) {
		//std::cout << "Failed to create texture : " << SDL_GetError();
		return false;
	}

	// Render the Texture with our message.
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture (pTexture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy (mpcRenderer, pTexture, NULL, &dst);

	SDL_FreeSurface (pSurface);
	SDL_DestroyTexture (pTexture);
	return true;
}

//***************************************************************************
// Function:    displayText
//
// Description: Display text on the screen at the given location using a
//              default font.
//
// Parameters:  x - x position
//              y - y position
//              msg - the text to display
//              rgba - the color of the text
//
// Returned:    none
//***************************************************************************
void SDLManager::displayText (int x, int y, std::string msg, Color cRgba) {
	displayText (x, y, msg, cRgba, mBasicFont);
}

void SDLManager::displayText (int x, int y, std::string msg) {
	displayText (x, y, msg, mcForegroundColor, mBasicFont);
}

//void SDLManager::drawSprite (SDLSprite &rcSDLSprite)
//{
//	SDL_Rect mRect;
//	SDL_Texture *psTexture = mTextures[rcSDLSprite.getName ()];
//	if (NULL == psTexture)
//	{
//		displayText (0, 0, "No Sprite Texture");
//		render ();
//		SDL_Delay (5000);
//		exit (EXIT_FAILURE);
//	}
//	SDL_QueryTexture (psTexture, NULL, NULL, &mRect.w, &mRect.h);
//	mRect.x = rcSDLSprite.getX ();
//	mRect.y = rcSDLSprite.getY ();
//	SDL_RenderCopy (mpcRenderer, psTexture, NULL, &mRect);
//
//}

//***************************************************************************
// Function:    drawSprite
//
// Description: Renders a sprite
//							NOTE: If x, y, h, and w are incorrect, most likely, you won't
//										see the sprite on the screen at all
//
// Parameters:  rcSprite - a sprite object
//
// Returned:    none
//***************************************************************************
void SDLManager::drawSprite (const SDLSprite &rcSprite) {
	SDL_Texture *pTexture;

	SDL_Rect rect;
	rect.x = rcSprite.getX ();
	rect.y = rcSprite.getY ();
	rect.h = rcSprite.getHeight ();
	rect.w = rcSprite.getWidth ();

	pTexture = mTextures [rcSprite.getName ()];

	if (nullptr != pTexture) {
		// rotation is in degrees
		SDL_RenderCopyEx (mpcRenderer, pTexture, NULL, &rect,
			rcSprite.getRotation (), NULL, SDL_FLIP_NONE);
		//SDL_RenderCopy (mpRenderer, pTexture, NULL, &rect);
	}
}

//***************************************************************************
// Function:    loadSprite
//
// Description: Loads a sprite for rendering into a  SDL_Texture map
//
// Parameters:  pszName - sprite name preceded by the path
//													e.g. "Images\\usa640x480.png"
//
// Returned:    a struct containing (height, width) of the sprite
//***************************************************************************
SpriteDimensions SDLManager::loadSprite (const char *pszName) {
	SpriteDimensions sSpriteDimensions;

	SDL_Texture *psTexture;
	psTexture = IMG_LoadTexture (mpcRenderer, pszName);
	SDL_QueryTexture (psTexture, NULL, NULL,
		&sSpriteDimensions.width, &sSpriteDimensions.height);
	if (NULL == psTexture) {
		displayText (0, 0, "Error Opening File");
		render ();
		SDL_Delay (5000);
		exit (EXIT_FAILURE);
	}
	std::string name (pszName);
	mTextures [name] = psTexture;

	return sSpriteDimensions;
}

void rotateSprite (SDLSprite &rcSDLSprite, double degrees) {
	rcSDLSprite.setRotation (degrees);
}