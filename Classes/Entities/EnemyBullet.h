#ifndef CONST_EnemyBullet_H
#define CONST_EnemyBullet_H

#include "cocos2d.h"

#include "Entity.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"
#include "BaseBullet.h"

using namespace cocos2d;

class EnemyBullet : public BaseBullet
{
	public:
		
		EnemyBullet();
		EnemyBullet(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual EnemyBullet* deepCopy();	
};

#endif