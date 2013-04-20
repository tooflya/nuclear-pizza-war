#ifndef CONST_BASEBULLET_H
#define CONST_BASEBULLET_H

#include "cocos2d.h"

#include "Entity.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseBullet : public Entity
{
	protected:
		float mPower;

		float mLifeTime;
		float mLifeTimeElapsed;

		bool mIsMoving;

		float mFakeZ;

	private:

	public:
		float mVectorX;
		float mVectorY;

		float mVectorPaddingX;
		float mVectorPaddingY;
		
		BaseBullet();
		BaseBullet(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		float getPower();

		void setPower(float pPower);

		void fire(float pX, float pY, float pVectorX, float pVectorY);

		void setFirePadding(float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		Entity* create();

		virtual bool destroy();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		bool onCollide();

		virtual BaseBullet* deepCopy();	

		void changeTexture(Texture* pTexture);

		virtual void setFZ(float pZ);
};

#endif