#ifndef CONST_FIREDENEMY
#define CONST_FIREDENEMY

#include "FiredEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

FiredEnemy::FiredEnemy(Entity* pTargetEntity, EntityManager* pBullets) :
	BaseEnemy("alien3.png", 8, 1)
	{
		this->mTargetEntity = pTargetEntity;
		this->mBullets = pBullets;

		this->mVectorX = -1;
		this->mVectorY = -1;

		this->setAsCollidable();

		this->setFireTime(Utils::randomf(5.0f, 15.0f));

		this->setBarsManagement(true, true);
		this->hideBars(false, true);

		this->mShootsCount = 1;
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

CCPoint FiredEnemy::pizzaPositionFromRad(float rad, float distanceFromCenterPercentage) {
	float pizzaRadiusX = 1560 / 2;
	float pizzaRadiusZ = 840 / 2;
	float x = (float) sin(rad) * distanceFromCenterPercentage;
	float z = (float) cos(rad) * distanceFromCenterPercentage;

	return ccp(x * pizzaRadiusX + 800 / 2 + 10, z * pizzaRadiusZ + Options::CAMERA_CENTER_Y);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* FiredEnemy::deepCopy()
{
	return new FiredEnemy(this->mTargetEntity, this->mBullets);
}

void FiredEnemy::move(float pDeltaTime)
{
	if (this->mVectorX < 0 || (abs(this->getCenterX() - this->mVectorX) < 10 && abs(this->getCenterY() - this->mVectorY) < 10)) { // TODO: Utils::coord()
		CCPoint pos = this->pizzaPositionFromRad(Utils::randomf(0.0f, 1.0f) * (float) Utils::Pi * 2.0f, .25f + Utils::randomf(0.0f, 1.0f) * .6f);
		
		this->mVectorX = pos.x;
		this->mVectorY = pos.y;
	}

	CCPoint vector = Utils::vectorNormalize(this->getCenterX() - this->mVectorX, this->getCenterY() - this->mVectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

void FiredEnemy::update(float pDeltaTime)
{
	if(!this->isVisible()) return;

	BaseEnemy::update(pDeltaTime);

	if(BarEntity::fire(this->mTargetEntity->getCenterX(), this->mTargetEntity->getCenterY()))
	{
		if(this->mShootsCount == 1)
		{
			((BaseBullet*) this->mBullets->create())->fire(this->getCenterX(), this->getCenterY(), this->mTargetEntity->getCenterX(), this->mTargetEntity->getCenterY());
		}
		else
		{
			BaseBullet* bullet;

			bullet = ((BaseBullet*) this->mBullets->create());
			bullet->fire(this->getCenterX(), this->getCenterY(), this->mTargetEntity->getCenterX(), this->mTargetEntity->getCenterY());
			bullet->setFirePadding(Utils::coord(30), Utils::coord(30));

			bullet = ((BaseBullet*) this->mBullets->create());
			bullet->fire(this->getCenterX(), this->getCenterY(), this->mTargetEntity->getCenterX(), this->mTargetEntity->getCenterY());

			bullet = ((BaseBullet*) this->mBullets->create());
			bullet->fire(this->getCenterX(), this->getCenterY(), this->mTargetEntity->getCenterX(), this->mTargetEntity->getCenterY());
			bullet->setFirePadding(-Utils::coord(30), -Utils::coord(30));
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alienshot.ogg");
	}
}

#endif