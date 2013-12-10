#ifndef CONST_BUBBLE
#define CONST_BUBBLE

#include "Bubble.h"

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

Bubble::Bubble()
{

}

Bubble::Bubble(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->setBarsManagement(true, false);

		this->setIgnoreSorting(true);

		this->mSplash = new Splash();
	}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* Bubble::create()
{
	if(!this->mSplash->getParent())
	{
		this->getParent()->addChild(this->mSplash);
		this->mSplash->destroy();
	}

	this->setHealth(140);

	this->animate(0.1f, 0, 8, 1);

	return BarEntity::create();
}

bool Bubble::onCollide()
{
	if(this->getHealth() <= 0)
	{
		this->destroy();

		this->mSplash->create()->animate(0.1f, 1);
		this->mSplash->setCenterPosition(this->getCenterX(), this->getCenterY());

		return true;
	}

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/shot_land.ogg");

	return false;
}

Entity* Bubble::deepCopy()
{
	return new Bubble("bubble.png", 9, 1);
}

#endif