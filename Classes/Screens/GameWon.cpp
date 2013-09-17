#ifndef CONST_GAMEWON
#define CONST_GAMEWON

#include "GameWon.h"

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

GameWon::GameWon()
{
	this->setRegisterAsTouchable(true);

<<<<<<< HEAD
	this->mBackground = new Entity("gui/victory.png");
=======
	this->mBackground = new Entity("victory.png");
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->addChild(this->mBackground);
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void GameWon::onTouch(CCTouch* touch, CCEvent* event)
{
	AppDelegate::screens->set(1.0f, 2, 0);
}

#endif