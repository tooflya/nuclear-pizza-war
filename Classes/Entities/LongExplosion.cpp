#ifndef CONST_LongExplosion
#define CONST_LongExplosion

#include "LongExplosion.h"

LongExplosion::LongExplosion()
{
}

LongExplosion::LongExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->resumeSchedulerAndActions();
	}

LongExplosion* LongExplosion::deepCopy()
{
<<<<<<< HEAD
	return new LongExplosion("actors/explosion3.png", 17, 1);
=======
	return new LongExplosion("explosion3.png", 17, 1);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}

Entity* LongExplosion::create()
{
	Entity::create();

	this->animate(0.1f, 1);

	return this;
}

void LongExplosion::onAnimationEnd()
{
	this->destroy();
}

#endif