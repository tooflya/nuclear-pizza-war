#ifndef CONST_SPIDEREXPLOSION
#define CONST_SPIDEREXPLOSION

#include "SpiderExplosion.h"

SpiderExplosion::SpiderExplosion()
{
}

SpiderExplosion::SpiderExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->resumeSchedulerAndActions();
	}

SpiderExplosion* SpiderExplosion::deepCopy()
{
<<<<<<< HEAD
	return new SpiderExplosion("actors/explosion1.png", 10, 1);
=======
	return new SpiderExplosion("explosion1.png", 10, 1);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}

Entity* SpiderExplosion::create()
{
	Entity::create();

	this->animate(0.1f, 1);

	return this;
}

void SpiderExplosion::onAnimationEnd()
{
	this->destroy();
}

#endif