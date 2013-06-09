#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "BarEntity.h"
#include "EntityManager.h"
#include "Utils.h"
#include "Options.h"

using namespace cocos2d;

class BaseBullet;
class BaseEnemy;

class Hero : public BarEntity
{
	class EngineParticle : public Entity
	{
		public:
		EngineParticle() :
			Entity("engine.png", 4, 1)
			{
			}

		Entity* create()
		{
			this->animate(0.1f, 0, 3, 1);

			return Entity::create();
		}

		void onAnimationEnd()
		{
			this->destroy();
		}

		void onAnimationStart()
		{
		}

		Entity* deepCopy()
		{
			return new EngineParticle();
		}
	};

	protected:
		float mShockwaveTime;
		float mShockwaveTimeElapsed;

		float mAltitude;
		float mSpeedStandart;
		float mPatrons;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		float mFollowCoordinateX;
		float mFollowCoordinateY;

		float mFireVectorX;
		float mFireVectorY;

		float mShootPaddingStandart;

		float mEngineParticlesAnimationTime;
		float mEngineParticlesAnimationTimeElapsed;

		float mHealthRegenerationTime;
		float mHealthRegenerationTimeElapsed;

		float mLaserRegenerationTime;
		float mLaserRegenerationTimeElapsed;

		float mLaserMaxPowerTime;
		float mLaserPowerTime;

		float mFlyDownSpeed;

		int mAnimationFrameSide;

		int mBulletsPower;

		bool mShootFromLeftHand;

		bool mIsDoubleFire;
		bool mIsTripleFire;
		bool mIsQuadrupleFire;

		EntityManager* mBulletsManager;
		EntityManager* mEngineParticles;

	private:
		Texture* mBulletsTexture0;
		Texture* mBulletsTexture1;
		Texture* mBulletsTexture2;
		Texture* mBulletsTexture3;

		bool mBroadcaster;

	public:
		float mShootVectorX;
		float mShootVectorY;

		float mLaserVectorX;
		float mLaserVectorY;

		float mShootPadding;

		float mJetPackPowerFull;
		float mJetPackPower;

		bool mShouldLaserFire;

		bool mIsMove;
		bool mIsFly;

		EntityManager* mGases;
		EntityManager* mGasesShadows;

		Entity* mShockwave;

		bool mIsShouldFire;

		Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount, bool pBeroadcaster);

		void reset();

		void laser();
		
		float getPatrons();

		virtual bool destroy();

		void setPatrons(float pPatrons);

		void setFollowCoordinates(float pX, float pY);
		void follow(float pDeltaTime);

		bool onCollide(BaseBullet* pBullet);
		bool onCollide(BaseEnemy* pEnemy);

		virtual void setCurrentFrameIndex(int pIndex);

		void fire(float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		void update(int type, int level);

		void setFireCoordinates(float pVectorX, float pVectorY);

		void startFly();
		void endFly();
		bool isCanFly();
		bool startFlyDamage();

		float mShockwaveDamage;

		float mShockwaveScale;

		virtual void outOfSpace();
};

#endif