#ifndef CONST_FOLLOWENEMY
#define CONST_FOLLOWENEMY

#include "FollowEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

FollowEnemy::FollowEnemy(Entity* pFollowEntity) :
<<<<<<< HEAD
	BaseEnemy("actors/alien1.png", 8, 1)
=======
	BaseEnemy("alien1.png", 8, 1)
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	{
		this->mFollowEntity = pFollowEntity;
		
		this->setAsCollidable();

		this->setBarsManagement(true, false);
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

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* FollowEnemy::deepCopy()
{
	return new FollowEnemy(this->mFollowEntity);
}

void FollowEnemy::move(float pDeltaTime)
{
	float vectorX = this->getCenterX() - this->mFollowEntity->getCenterX();
	float vectorY = this->getCenterY() - this->mFollowEntity->getCenterY();

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

#endif