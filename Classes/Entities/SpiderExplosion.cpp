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
	return new SpiderExplosion("explosion1.png", 10, 1);
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