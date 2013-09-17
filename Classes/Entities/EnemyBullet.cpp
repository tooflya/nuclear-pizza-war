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
<<<<<<< HEAD
	return new EnemyBullet("actors/alienbullet.png", 1, 1);
=======
	return new EnemyBullet("alienbullet.png", 1, 1);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}

#endif