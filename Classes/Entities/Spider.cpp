#ifndef CONST_SPIDER
#define CONST_SPIDER

#include "Spider.h"

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

Spider::Spider() :
	Entity("spider.png", 4, 1)
	{
		this->mShadow = new Entity("smallshadow.png");
		this->mShadow->setIsShadow();

		this->mVectorX = 0;
		this->mVectorY = 0;

		this->mTalkTime = Utils::randomf(5.0f, 25.0f);
		this->mTalkTimeElapsed = 0;

		this->setSpeed(50);

		this->mShockwave = new Entity("shockwave.png");

		this->animate(0.1f);

		// this->setAsCollidable(); // TODO: Some problem here.
	}

// ===========================================================
// Methods
// ===========================================================

CCPoint Spider::pizzaPositionFromRad(float rad, float distanceFromCenterPercentage) {
	float pizzaRadiusX = 1560 / 2;
	float pizzaRadiusZ = 840 / 2;
	float x = (float) sin(rad) * distanceFromCenterPercentage;
	float z = (float) cos(rad) * distanceFromCenterPercentage;

	return ccp(x * pizzaRadiusX + 800 / 2 + 10, z * pizzaRadiusZ + Options::CAMERA_CENTER_Y);
}

bool Spider::onCollide(BaseEnemy* pEnemy)
{
	pEnemy->removeHealth(60); // TODO: Adjust spider power.

	this->destroy();

	return true;
}

void Spider::follow(float pDeltaTime)
{
	CCPoint vector;

	if (this->mVectorX < 0 || (abs(this->getCenterX() - this->mVectorX) < Utils::coord(10) && abs(this->getCenterY() - this->mVectorY) < Utils::coord(10)))
	{
		float radius = (0.25f + Utils::randomf(0.0f, 1.0f) * 0.6f);
		
		vector = this->pizzaPositionFromRad(Utils::randomf(0.0f, 1.0f) * Utils::Pi * 2.0f, radius);

		this->mVectorX = vector.x;
		this->mVectorY = vector.y;
	}

	vector = Utils::vectorNormalize(this->getCenterX() - this->mVectorX, this->getCenterY() - this->mVectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

void Spider::follow(float pVectorX, float pVectorY, float pDeltaTime)
{
	CCPoint vector = Utils::vectorNormalize(pVectorY, pVectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* Spider::create()
{
	this->mShadow->create();

	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 0);
	}

	if(!this->mShockwave->getParent())
	{
		this->getParent()->addChild(this->mShockwave, 0);
	}

	return Entity::create();
}

bool Spider::destroy()
{
	this->mShadow->destroy();
	this->mShockwave->destroy();

	return Entity::destroy();
}

Entity* Spider::deepCopy()
{
	return new Spider();
}

void Spider::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(!this->isVisible()) return;

	this->follow(pDeltaTime);

	this->mTalkTimeElapsed += pDeltaTime;

	if(this->mTalkTimeElapsed >= this->mTalkTime)
	{
		this->mTalkTimeElapsed -= this->mTalkTime;

		this->mShockwave->setScale(0);
		this->mShockwave->create()->runAction(CCScaleTo::create(0.2f, 1.5f));

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/spider_talk.ogg");
	}
	else
	{
		if(this->mShockwave->isVisible())
		{
			if(this->mTalkTimeElapsed >= 0.2f)
			{
				this->mShockwave->destroy();
			}
		}
	}
	
	this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY());
	this->mShadow->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(5));
}

#endif