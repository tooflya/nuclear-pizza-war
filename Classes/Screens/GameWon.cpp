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

	this->mBackground = new Entity("victory.png");

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