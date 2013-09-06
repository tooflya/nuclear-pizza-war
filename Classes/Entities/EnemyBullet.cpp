#ifndef CONST_EnemyBullet
#define CONST_EnemyBullet

#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BaseBullet(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->setPower(10);
		this->setSpeed(170);
	}

EnemyBullet* EnemyBullet::deepCopy()
{
	return new EnemyBullet("alienbullet.png", 1, 1);
}

#endif