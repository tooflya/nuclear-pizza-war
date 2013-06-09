#ifndef CONST_SPLASHSCREEN
#define CONST_SPLASHSCREEN

#include "SplashScreen.h"
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

SplashScreen::SplashScreen()
{
	this->mBackground = new Entity("cyborghippo.png");

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->addChild(this->mBackground);

	// this->setRegisterAsTouchable(true);

	this->mBackground->setOpacity(0);

	this->mShowtime = 1.0f;
	this->mShowtimeElapsed = 0;
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void SplashScreen::onTouch(CCTouch* touch, CCEvent* event)
{
}

void SplashScreen::update(float pDeltaTime)
{
	this->mShowtimeElapsed += pDeltaTime;

	if(this->mShowtimeElapsed >= this->mShowtime)
	{
		this->mShowtimeElapsed = 0;

		AppDelegate::screens->set(1.0f, 0, 4);
	}
}

void SplashScreen::onEnter()
{
	Screen::onEnter();

	this->mBackground->runAction(CCFadeIn::create(0.5f));
}

#endif