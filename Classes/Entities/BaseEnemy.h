#ifndef CONST_BASEENEMY_H
#define CONST_BASEENEMY_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Texture.h"
#include "BarEntity.h"
#include "EntityManager.h"
#include "BaseBullet.h"
#include "Castle.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseEnemy : public BarEntity
{
	protected:
		float mSpeedStandart;

		Hero* mHero;
		EntityManager* mBullets;

		float mFollowPaddingX;
		float mFollowPaddingY;

	private:

	public:

		float mShootVectorX;
		float mShootVectorY;

		float mShootPadding;

		BaseEnemy();
		BaseEnemy(Hero* pHero, EntityManager* pBullets);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets);

		virtual Entity* create();
		virtual bool destroy();

		void onCollideC(Castle* mCastle);
		virtual bool onCollide(BaseBullet* pBullet);
		virtual void onCollide(Hero* pEntity);
		bool onCollide(float pDamage, float pVectorX, float pVectorY);

		void death();

		void update(float pDeltaTime);

		void fire();

		virtual void move(float pDeltaTime);
};

#endif