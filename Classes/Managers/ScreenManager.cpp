#ifndef CONST_SCREENMANAGER
#define CONST_SCREENMANAGER

#include "ScreenManager.h"

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

ScreenManager::ScreenManager()
{
	this->generate();
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void ScreenManager::generate()
{
	this->mScreens[0] = new Level();
	this->mScreens[1] = new GameOver();
	this->mScreens[2] = new GameWon();
	this->mScreens[3] = new MainMenu();
	this->mScreens[4] = new MojangSplashScreen();
}

void ScreenManager::set(float pAnimationTime, int pAction, int pIndex)
{
	this->mCurrentScreenIndex = pIndex;
	
	CCTransitionScene* transition = CCTransitionFade::create(pAnimationTime, this->mScreens[pIndex]);

	switch(pAction)
	{
		case 0:
			CCDirector::sharedDirector()->replaceScene(transition);
		break;
		case 1:
			CCDirector::sharedDirector()->pushScene(transition);
		break;
		case 2:
			CCDirector::sharedDirector()->replaceScene(transition);
		break;
	}
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif