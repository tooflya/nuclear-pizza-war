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
	return new LongExplosion("explosion3.png", 17, 1);
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