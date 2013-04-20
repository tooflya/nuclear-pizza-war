#ifndef CONST_STAR
#define CONST_STAR

#include "Star.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Star::Star()
{
}

Star::Star(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
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

void Star::init(float pBoundsX1, float pBoundsX2, float pBoundsY1, float pBoundsY2)
{
	this->mBoundsX1 = pBoundsX1;
	this->mBoundsX2 = pBoundsX2 + Utils::coord(300);
	this->mBoundsY1 = pBoundsY1 + Utils::coord(300);
	this->mBoundsY2 = pBoundsY2;

	this->setCenterPosition(Utils::random(this->mBoundsX1, this->mBoundsX2), this->mBoundsY1);
	this->setSpeed(Utils::randomf(100, 350));
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Star::create()
{
	Star* entity = ((Star*) Entity::create());

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	return entity;
}

Star* Star::deepCopy()
{
	return new Star("main-menu/main-menu-star-sprite.png", 1, 3);
}

void Star::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	this->setCenterPosition(this->getCenterX() - this->getSpeed(pDeltaTime), this->getCenterY() - this->getSpeed(pDeltaTime));
	this->setRotation(atan2(-this->getSpeed(pDeltaTime), this->getSpeed(pDeltaTime)) * 180 / Utils::Pi);

	if(!this->collideWithCoordinates(this->mBoundsX1, this->mBoundsX2, this->mBoundsY1, this->mBoundsY2))
	{
		this->destroy();
	}
}

#endif