#ifndef CONST_BASEEXPLOSION_H
#define CONST_BASEEXPLOSION_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class BaseExplosion : public Entity
{
	protected:

	private:

	public:
		BaseExplosion();
		BaseExplosion(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual Entity* create();

		virtual void onAnimationEnd();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseExplosion* deepCopy();	
};

#endif