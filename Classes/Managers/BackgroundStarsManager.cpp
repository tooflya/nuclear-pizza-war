#ifndef CONST_BACKGROUNDSTARSMANAGER
#define CONST_BACKGROUNDSTARSMANAGER

#include "BackgroundStarsManager.h"

// ===========================================================
// Init
// ===========================================================

void BackgroundStarsManager::constructor(CCNode* pScreen, bool pIsLargeManagement)
{
	this->mIsLargeManagement = pIsLargeManagement;

	this->initWithFile("stars.png", 1000);

	for(int i = 0; i < 1000; i++)
	{
		Entity* star = new Entity("stars.png", 3, 2);

		star->create();

		if(this->mIsLargeManagement)
		{
			star->setCenterPosition(Utils::random(-Options::CAMERA_WIDTH, Options::CAMERA_WIDTH * 2), Utils::random(-Options::CAMERA_HEIGHT, Options::CAMERA_HEIGHT * 2));
		}
		else
		{
			star->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), Utils::random(0, Options::CAMERA_HEIGHT));
		}

		star->setSpeed(0.95f + Utils::randomf(0.0f, 100.0f));
		star->setCurrentFrameIndex(Utils::random(0, 6));

		this->addChild(star);
	}

	pScreen->addChild(this);

	this->scheduleUpdate();
}

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

BackgroundStarsManager::BackgroundStarsManager(CCNode* pScreen) :
	CCSpriteBatchNode()
	{
		this->constructor(pScreen, false);
	}

BackgroundStarsManager::BackgroundStarsManager(CCNode* pScreen, bool pIsLargeManagement) :
	CCSpriteBatchNode()
	{
		this->constructor(pScreen, pIsLargeManagement);
	}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void BackgroundStarsManager::update(float pDeltaTime)
{
	CCSpriteBatchNode::update(pDeltaTime);

	for(int i = 0; i < 1000; i++)
	{
		Entity* star = (Entity*) this->getChildren()->objectAtIndex(i);

		bool finish;

		if(this->mIsLargeManagement)
		{
			finish = star->getCenterY() < -Options::CAMERA_HEIGHT;
		}
		else
		{
			finish = star->getCenterY() < 0;
		}

		if(finish)
		{
			star->setCenterPosition(star->getCenterX(), Options::CAMERA_HEIGHT * 2);
		}
		else
		{
			star->setCenterPosition(star->getCenterX(), star->getCenterY() - star->getSpeed(pDeltaTime));
		}
	}
}

#endif