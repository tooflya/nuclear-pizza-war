#ifndef CONST_BACKGROUNDSTARSMANAGER_H
#define CONST_BACKGROUNDSTARSMANAGER_H

#include "cocos2d.h"

#include "Entity.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BackgroundStarsManager : public CCSpriteBatchNode
{
	protected:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
		// ===========================================================
		// Init
		// ===========================================================

		void constructor(CCNode* pScreen, bool pIsLargeManagement);

		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		bool mIsLargeManagement;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		BackgroundStarsManager(CCNode* pScreen);
		BackgroundStarsManager(CCNode* pScreen, bool pIsLargeScreen);

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		void update(float pDeltaTime);
};

#endif