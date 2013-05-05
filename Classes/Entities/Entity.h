#ifndef CONST_ENTITY_H
#define CONST_ENTITY_H

#include "cocos2d.h"

#include "Touchable.h"
#include "Texture.h"
#include "Utils.h"
#include "Options.h"

using namespace cocos2d;

class Level;
class BarEntity;
class EntityManager;
class BatchEntityManager;

class Entity : public CCSprite, public Touchable
{
	protected:
		float mWidth;
		float mHeight;

		float mFrameWidth;
		float mFrameHeight;

		int mFramesCount;

		int mHorizontalFramesCount;
		int mVerticalFramesCount;

		int mCurrentFrameIndex;

		float* mFramesCoordinatesX;
		float* mFramesCoordinatesY;

		bool mAnimationRunning;
		bool mFall;

		bool mIsShadow;
		bool mIsCollidable;

		bool mIsRed;

		float mSpeed;

		float mZ;

		float mPauseBeforeNewAnimationCircleTime;
		float mPauseBeforeNewAnimationCircleTimeElapsed;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		float mAnimationStartTimeout;

		float mAnimationScaleDownTime;
		float mAnimationScaleUpTime;

		float mRedTime;
		float mRedTimeElapsed;

		float mAnimationScaleDownFactor;
		float mAnimationScaleUpFactor;

		int mAnimationStartFrame;
		int mAnimationFinishFrame;
		int mAnimationFramesElapsed;

		int mAnimationRepeatCount;

		bool mIsAnimationReverse;
		bool mIsAnimationReverseNeed;

		bool mIsOutOfTop;

		int id; // For the entities which is childs of EntityManagers
		EntityManager* mEntityManager;
		BatchEntityManager* mBatchEntityManager;

		bool mIgnoreSorting;

	private:
		void constructor(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);

	public:
		Entity();
		Entity(const char* pszFileName);
		Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
		Entity(const char* pszFileName, CCNode* pParent);
		Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);

		const char* mTextureFileName;

		Entity* mShadow; // For shadowed entities
		
		float getWidth();
		float getHeight();
		
		float getWidthScaled();
		float getHeightScaled();

		void setIsShadow();
		void setAsCollidable();

		void setRed();

		bool isSetAsShadow();
		bool isSetAsCollidable();

		bool collideWith(Entity* pEntity);
		bool collideWith(Entity* pEntity, float pFactor);
		bool collideCoordinatesWith(float x, float y, Entity* pEntity);
		bool collideWithCoordinates(float pX1, float pX2, float pY1, float pY2);

		bool circlesCollide(Entity* entity);
		bool circlesCollideWithCoordinates(float pX, float pY, float pRadius);
		bool circlesCollideCoordinatesWith(float pX1, float pY1, float pX2, float pY2, float pRadius);
		
		/**
		 *
		 * Take care about careful position
		 *
		 */

		void setPosition(float pX, float pY);
		void setCenterPosition(float pX, float pY);
		void setCenterPosition(float pX, float pY, bool setWithoutChecks);
		void setX(float pX);
		void setY(float pY);
		void setZ(float pZ);

		void addZ(float pZ);
		void removeZ(float pZ);

		float getCenterPosition();
		float getX();
		float getY();
		float getZ();
		float getCenterX();
		float getCenterY();
		
		/**
		 *
		 * Take care about speed
		 *
		 */

		float getSpeed(float pDeltaTime);
		void setSpeed(float pSpeed);

		bool hasShadow();

		Entity* getShadow();

		void setIgnoreSorting(bool pIgnoreSorting);
		bool isIgnoreSorting();

		virtual void outOfSpace();

		/**
		 *
		 * Take care about EntityManager
		 *
		 */

		virtual bool onCollide();

		virtual Entity* create();

		virtual bool destroy();
		virtual bool destroy(bool pManage);

		void setEntityManager(EntityManager* pEntityManager);
		void setEntityManager(BatchEntityManager* pBatchEntityManager);

		int hasEntityManager();

		void setEntityManagerId(int pId);

		int getEntityManagerId();

		/**
		 *
		 * Take care about animation
		 *
		 */

		int getCurrentFrameIndex();

		virtual void setCurrentFrameIndex(int pIndex);

		void previousFrameIndex();
		void nextFrameIndex();

		virtual void changeTexture(Texture* pTexture);

		bool isAnimationRunning();

		void animate(float pAnimationTime);
		void animate(float pAnimationTime, int pRepeatCount);
		void animate(float pAnimationTime, int pRepeatCount, bool pNeedReverse);
		void animate(float pAnimationTime, float pPauseBeforeNewAnimationCircleTime);
		void animate(float pAnimationTime, int pRepeatCount, float pPauseBeforeNewAnimationCircleTime);
		void animate(float pAnimationTime, int pStartFrame, int pFinishFrame, int pRepeatCount);
		void animate(float pAnimationTime, int pStartFrame, int pFinishFrame);

		void setStartFrame(int pStartFrame);
		void setFinishFrame(int pFinishFrame);

		void setAnimationStartTimeout(float pSecodsTimeout);
    
        void setAnimationReverse(bool pReverse);

		virtual void onAnimationStart();
		virtual void onAnimationEnd();
		virtual void onAnimationCircleEnd();

		/**
		 *
		 * Checing for touch detector
		 *
		 */

		void onEnter();

		void onExit();

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);

		void ccTouchMoved(CCTouch* touch, CCEvent* event);

		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		bool containsTouchLocation(CCTouch* touch);

		virtual void update(float pDeltaTime);

		virtual void draw();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual Entity* deepCopy();
};

#endif