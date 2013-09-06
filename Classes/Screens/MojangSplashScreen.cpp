#ifndef CONST_MOJANGSPLASHSCREEN
#define CONST_MOJANGSPLASHSCREEN

#include "MojangSplashScreen.h"
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

MojangSplashScreen::MojangSplashScreen()
{
	this->mBackground = new Entity("mojang.png");

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->addChild(this->mBackground);

	// this->setRegisterAsTouchable(true);

	this->mShowtime = 1.0f;
	this->mShowtimeElapsed = 0;
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void MojangSplashScreen::onTouch(CCTouch* touch, CCEvent* event)
{
}

void MojangSplashScreen::update(float pDeltaTime)
{
	this->mShowtimeElapsed += pDeltaTime;

	if(this->mShowtimeElapsed >= this->mShowtime)
	{
		this->mShowtimeElapsed = 0;

		AppDelegate::screens->set(1.0f, 0, 3);
	}
}

#endif