#ifndef CONST_GAMEOVER
#define CONST_GAMEOVER

#include "GameOver.h"

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

GameOver::GameOver()
{
	this->setRegisterAsTouchable(true);

<<<<<<< HEAD
	this->mBackground = new Entity("gui/game_over.png");
=======
	this->mBackground = new Entity("game_over.png");
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

void GameOver::onTouch(CCTouch* touch, CCEvent* event)
{
	AppDelegate::screens->set(1.0f, 2, 0);
}

#endif