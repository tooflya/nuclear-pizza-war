#ifndef CONST_SPIDEREXPLOSION_H
#define CONST_SPIDEREXPLOSION_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class SpiderExplosion : public Entity
{
	protected:

	private:

	public:
		SpiderExplosion();
		SpiderExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual Entity* create();

		virtual void onAnimationEnd();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual SpiderExplosion* deepCopy();	
};

#endif