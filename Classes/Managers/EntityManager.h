#ifndef CONST_ENTITYMANAGER_H
#define CONST_ENTITYMANAGER_H

#include "cocos2d.h"

#include "Entity.h"

class EntityManagerGroup;

using namespace cocos2d;

class EntityManager : public CCArray
{
	protected:
		CCNode* mParent;

		int mLastElementNumber;
		int mCapacity;
		int mZOrder;

		EntityManagerGroup* mUnified;

	public:
		void init(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen, int pZOrder);
		
		EntityManager(int pCreateCount, Entity* pEntity);
		EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen);
		EntityManager(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen);
		EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen, int pZOrder);

		Entity* create();
		void destroy(int pIndex);

		void setParent(CCNode* pScreen);
		void setParent(CCNode* pScreen, int pZOrder);

		void changeTexture(Texture* pTexture);

		void setUnified(EntityManagerGroup* pEntityManagerGroup);
		
		int getCount();
		int getCapacity();

		void clear();

		void update(float pDeltaTime);
};

#endif