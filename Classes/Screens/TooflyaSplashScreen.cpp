#ifndef CONST_TOOFLYASPLASHSCREEN
#define CONST_TOOFLYASPLASHSCREEN

#include "TooflyaSplashScreen.h"
#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

TooflyaSplashScreen::TooflyaSplashScreen()
{
    CCLayerColor* c = CCLayerColor::create(ccc4(255, 255, 255, 255), Options::CAMERA_WIDTH, Options::CAMERA_HEIGHT);
    
	this->mBackground = new Entity("splash_logo_tfl.png");

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

    c->addChild(this->mBackground);
	this->addChild(c);

	// this->setRegisterAsTouchable(true);

	this->mShowtime = 3.0f;
	this->mShowtimeElapsed = 0;
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void TooflyaSplashScreen::onTouch(CCTouch* touch, CCEvent* event)
{
}

void TooflyaSplashScreen::update(float pDeltaTime)
{
	this->mShowtimeElapsed += pDeltaTime;

	if(this->mShowtimeElapsed >= this->mShowtime)
	{
		this->mShowtimeElapsed = 0;

		AppDelegate::screens->set(1.0f, 0, 3);
	}
}

#endif