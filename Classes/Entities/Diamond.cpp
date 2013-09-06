#ifndef CONST_DIAMOND
#define CONST_DIAMOND

#include "Diamond.h"

// ===========================================================
// Init
// ===========================================================

void Diamond::constructor()
{
	this->setAsCollidable();

	this->mShadow = new Entity("smallshadow.png");
	this->mShadow->setIsShadow();

	this->mAnimationTime = 2.0f;
	this->mDeathAnimationTime = 0.1f;
    
    this->setAnimationStartTimeout(Utils::randomf(0.0f, 2.0f));

	this->reset();
}

// ===========================================================
// Constructors
// ===========================================================

Diamond::Diamond()
{
}

Diamond::Diamond(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->constructor();
	}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void Diamond::reset()
{
	this->mAnimationTimeElapsed = 0.0f;
	this->mDeathAnimationTimeElapsed = 0.0f;

	this->mCenterX = 0;
	this->mCenterY = 0;

	this->mPaddingY = 0;

	this->mIsAnimationReverse = false;
	this->mIsMustDestroy = false;
    this->mSplash = false;

	this->setSpeed(40.0f);

	this->setScale(0.0f);
	this->setOpacity(255.0f);

	this->runAction(CCScaleTo::create(0.5f, 1.0f));
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Diamond::create()
{
	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 0);
	}

	this->mShadow->create();

	Diamond* entity = ((Diamond*) Entity::create());

	entity->reset();
    
    this->mSplash = true;

	return entity;
}

bool Diamond::destroy()
{
	this->mShadow->destroy();
	
	return Entity::destroy();
}

Diamond* Diamond::deepCopy()
{
	return new Diamond("pickup_gem_diamond_24.png", 14, 3);
}

void Diamond::follow(float pVectorX, float pVectorY, float pDeltaTime)
{
	if(this->mCenterX == 0 && this->mCenterY == 0) return;

	float vectorX = pVectorX- this->getCenterX();
	float vectorY = pVectorY - this->getCenterY();

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->mCenterX + vector.x, this->mCenterY + vector.y + Utils::coord(this->mPaddingY));

	this->mCenterX += vector.x;
	this->mCenterY += vector.y;
}

void Diamond::startDestroy()
{
	this->mIsMustDestroy = true;

	this->runAction(CCFadeTo::create(this->mDeathAnimationTime, 0.0f));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_COIN);
}

void Diamond::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(!this->isVisible()) return;

	if(this->mCenterX == 0 && this->mCenterY == 0)
	{
		this->mCenterX = this->getCenterX();
		this->mCenterY = this->getCenterY();
	}
	else
	{
		this->mAnimationTimeElapsed += pDeltaTime;

		if(this->mAnimationTimeElapsed >= this->mAnimationTime)
		{
			this->mAnimationTimeElapsed = 0;

			this->mIsAnimationReverse = !this->mIsAnimationReverse;
		}

		this->mPaddingY -= this->mIsAnimationReverse ? 0.15f : -0.15f;

		this->setCenterPosition(this->mCenterX, this->mCenterY + Utils::coord(this->mPaddingY));

		this->mShadow->setScale(this->getScale() - Utils::coord(this->mPaddingY) / 35);
		this->mShadow->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(10) - Utils::coord(this->mPaddingY));
	}

	if(this->mIsMustDestroy)
	{
		this->mDeathAnimationTimeElapsed += pDeltaTime;

		if(this->mDeathAnimationTimeElapsed >= mDeathAnimationTime)
		{
			this->mDeathAnimationTimeElapsed = 0.0f;
			this->mIsMustDestroy = false;

			this->destroy();
		}
	}
}

bool Diamond::onCollide()
{
	if(this->mIsMustDestroy) return false;

	this->startDestroy();

	return true;
}

#endif