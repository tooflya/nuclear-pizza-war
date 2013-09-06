#ifndef CONST_DIAMOND_H
#define CONST_DIAMOND_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Entity.h"
#include "Utils.h"

using namespace cocos2d;

class Diamond : public Entity
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
		// ===========================================================
		// Public fields
        // ===========================================================
    
        bool mIsMustDestroy; // TODO: Remove to private.
        bool mSplash;

		// ===========================================================
		// Constructors
		// ===========================================================

		Diamond();
		Diamond(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

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

		void follow(float pVectorX, float pVectorY, float pDeltaTime);

		void reset();

		void startDestroy();

		// ===========================================================
		// Virtual methods
		// ===========================================================

		Entity* create();
		bool destroy();

		void update(float pDeltaTime);

		Diamond* deepCopy();	

		bool onCollide();
};

#endif