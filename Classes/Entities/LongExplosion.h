#ifndef CONST_LongExplosion_H
#define CONST_LongExplosion_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class LongExplosion : public Entity
{
	protected:

	private:

	public:
		LongExplosion();
		LongExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual Entity* create();

		virtual void onAnimationEnd();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual LongExplosion* deepCopy();	
};

#endif