#ifndef CONST_MINEENEMY
#define CONST_MINEENEMY

#include "MineEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

MineEnemy::MineEnemy() :
	BaseEnemy("alien5.png", 8, 1)
	{
		this->mVectorX = -1;
		this->mVectorY = -1;

		this->setAsCollidable();

		this->setFireTime(Utils::randomf(5.0f, 15.0f));

		this->setBarsManagement(true, true);
		this->hideBars(false, true);

		this->mShootsCount = 1;
        
        this->setAnimationReverse(true);
	}

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

CCPoint MineEnemy::pizzaPositionFromRad(float rad, float distanceFromCenterPercentage) {
	float pizzaRadiusX = 1560 / 2;
	float pizzaRadiusZ = 840 / 2;
	float x = (float) sin(rad) * distanceFromCenterPercentage;
	float z = (float) cos(rad) * distanceFromCenterPercentage;

	return ccp(x * pizzaRadiusX + 800 / 2 + 10, z * pizzaRadiusZ + Options::CAMERA_CENTER_Y);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* MineEnemy::deepCopy()
{
	return new MineEnemy();
}

void MineEnemy::move(float pDeltaTime)
{
	if (this->mVectorX < 0 || (abs(this->getCenterX() - this->mVectorX) < 10 && abs(this->getCenterY() - this->mVectorY) < 10)) { // TODO: Utils::coord()
		CCPoint pos = this->pizzaPositionFromRad(Utils::randomf(0.0f, 1.0f) * (float) Utils::Pi * 2.0f, .25f + Utils::randomf(0.0f, 1.0f) * .6f);
		
		this->mVectorX = pos.x;
		this->mVectorY = pos.y;
	}

	CCPoint vector = Utils::vectorNormalize(this->getCenterX() - this->mVectorX, this->getCenterY() - this->mVectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

void MineEnemy::update(float pDeltaTime)
{
	if(!this->isVisible()) return;

	BaseEnemy::update(pDeltaTime);
}

#endif