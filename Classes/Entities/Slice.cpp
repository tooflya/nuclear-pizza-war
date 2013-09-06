#ifndef CONST_SLICE
#define CONST_SLICE

#include "Slice.h"

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

Slice::Slice() :
	Entity("ansjovalienbotslice.png")
	{
		this->setIgnoreSorting(true);

		this->setSpeed(200.0f + Utils::randomf(0.0f, 200.0f));

		this->mShadow = new Entity("ansjovalienbotslice.png");
		this->mShadow->setIsShadow();
		this->mShadow->setColor(ccc3(0.0f, 0.0f, 0.0f));
		this->mShadow->setIgnoreSorting(true);
	}

// ===========================================================
// Methods
// ===========================================================

void Slice::setFollowCoordinates(float pVectorX, float pVectorY)
{
	this->mVectorX = this->getCenterX() - pVectorX;
	this->mVectorY = this->getCenterY() - pVectorY;
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* Slice::create()
{
	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 7);
	}

	this->mShadow->create();

	int r = Utils::random(0, 1);

	float x = r == 0 ? -this->getWidth() * 2 : Options::CAMERA_WIDTH + this->getWidth() * 2;
	float y = Utils::random(0, 1) == 0 ? -this->getHeight() * 2 : Options::CAMERA_HEIGHT + this->getHeight() * 2;

	if(r == 0)
	{
		this->setScaleX(-1);
		this->mShadow->setScaleX(-1);
	}
	else
	{
		this->setScaleX(1);
		this->mShadow->setScaleX(1);
	}

	this->setCenterPosition(x, y);

	return Entity::create();
}

bool Slice::destroy()
{
	this->mShadow->destroy();

	return false;
}

Entity* Slice::deepCopy()
{
	return new Slice();
}

void Slice::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	CCPoint vector = Utils::vectorNormalize(this->mVectorX, this->mVectorY, this->getSpeed(0.02f));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);

	if(this->getCenterY() > Options::CAMERA_HEIGHT + this->getHeight() * 4 || this->getCenterY() < -this->getHeight() * 4)
	{
		this->destroy();
	}

	this->mShadow->setCenterPosition(this->getCenterX() + Utils::coord(50), this->getCenterY() - Utils::coord(300));
}

#endif