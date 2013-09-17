#ifndef CONST_BASEEXPLOSION
#define CONST_BASEEXPLOSION

#include "BaseExplosion.h"

BaseExplosion::BaseExplosion()
{
}

BaseExplosion::BaseExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->resumeSchedulerAndActions();
	}

BaseExplosion* BaseExplosion::deepCopy()
{
<<<<<<< HEAD
	return new BaseExplosion("actors/explosion2.png", 17, 1);
=======
	return new BaseExplosion("explosion2.png", 17, 1);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}

Entity* BaseExplosion::create()
{
	Entity::create();

	this->animate(0.03, 1);

	return this;
}

void BaseExplosion::onAnimationEnd()
{
	this->destroy();
}

#endif