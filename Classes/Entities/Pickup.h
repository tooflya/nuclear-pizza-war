#ifndef CONST_PICKUP_H
#define CONST_PICKUP_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Entity.h"
#include "Utils.h"

using namespace cocos2d;

class Pickup : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor();

		// ===========================================================
		// Private fields
		// ===========================================================
		
		float mCenterX;
		float mCenterY;

		float mPaddingY;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		float mDeathAnimationTime;
		float mDeathAnimationTimeElapsed;

		bool mIsAnimationReverse;

		// ===========================================================
		// Private methods
		// ===========================================================

	public:

		bool mIsMustDestroy; // TODO: Remove to private.
		// ===========================================================
		// Public fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		Pickup();
		Pickup(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		// ===========================================================
		// Getters
		// ===========================================================

		// ===========================================================
		// Setters
		// ===========================================================

		// ===========================================================
		// Checkers
		// ===========================================================

		// ===========================================================
		// Events
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void follow(float pVectorX, float pVectorY);

		void reset();

		void startDestroy();

		// ===========================================================
		// Virtual methods
		// ===========================================================

		Entity* create();
		bool destroy();

		void update(float pDeltaTime);

		Pickup* deepCopy();	

		bool onCollide();
};

#endif