#ifndef CONST_BATCHENTITYMANAGER_H
#define CONST_BATCHENTITYMANAGER_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class BatchEntityManager : public CCSpriteBatchNode
{
	protected:
		int mLastElementNumber;
		int mCapacity;

	public:
		BatchEntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen);
		
		int getCount();
		int getCapacity();

		void clear();

		CCObject* objectAtIndex(int pIndex);

		Entity* create();
		void destroy(int pIndex);
};

#endif