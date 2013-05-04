#ifndef CONST_BigEnemy
#define CONST_BigEnemy

#include "BigEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

BigEnemy::BigEnemy(EntityManager* pBullets) :
	BaseEnemy("alien4.png", 4, 1)
	{
		this->mShadow = new Entity("largeshadow.png");
		this->mShadow->setIsShadow();

		this->mBullets = pBullets;

		this->mVectorX = -1;
		this->mVectorY = -1;

		this->setAsCollidable();

		this->setFireTime(Utils::randomf(5.0f, 15.0f));

		this->setBarsManagement(true, true);
		this->hideBars(false, true);

		this->mShootsCount = 7;
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

CCPoint BigEnemy::pizzaPositionFromRad(float rad, float distanceFromCenterPercentage) {
	float pizzaRadiusX = 1560 / 2;
	float pizzaRadiusZ = 840 / 2;
	float x = (float) sin(rad) * distanceFromCenterPercentage;
	float z = (float) cos(rad) * distanceFromCenterPercentage;

	return ccp(x * pizzaRadiusX + 800 / 2 + 10, z * pizzaRadiusZ + Options::CAMERA_CENTER_Y);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* BigEnemy::deepCopy()
{
	return new BigEnemy(this->mBullets);
}

void BigEnemy::move(float pDeltaTime)
{
	if (this->mVectorX < 0 || (abs(this->getCenterX() - this->mVectorX) < 10 && abs(this->getCenterY() - this->mVectorY) < 10)) { // TODO: Utils::coord()
		CCPoint pos = this->pizzaPositionFromRad(Utils::randomf(0.0f, 1.0f) * (float) Utils::Pi * 2.0f, .25f + Utils::randomf(0.0f, 1.0f) * .6f);
		
		this->mVectorX = pos.x;
		this->mVectorY = pos.y;
	}

	CCPoint vector = Utils::vectorNormalize(this->getCenterX() - this->mVectorX, this->getCenterY() - this->mVectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

void BigEnemy::update(float pDeltaTime)
{
	if(!this->isVisible()) return;

	BaseEnemy::update(pDeltaTime);

	if(BarEntity::fire(0, 0))
	{
		for(int i = 0; i < this->mShootsCount; i++)
		{
			float x = 5.0f * sin(i * 2 * Utils::Pi / this->mShootsCount);
			float y = 5.0f * cos(i * 2 * Utils::Pi / this->mShootsCount);

			((BaseBullet*) this->mBullets->create())->fire(this->getCenterX(), this->getCenterY(), this->getCenterX() + x, this->getCenterY() + y);
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_ALIEN_SHOT);
	}
}

#endif