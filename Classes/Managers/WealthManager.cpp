#ifndef CONST_WEALTHMANAGER
#define CONST_WEALTHMANAGER

#include "WealthManager.h"
#include "Level.h"

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
		
WealthManager::WealthManager(int pCreateCount, Entity* pEntity, CCNode* pScreen, int pZOrder) :
	BatchEntityManager(pCreateCount, pEntity, pScreen)
	{
	}

// ===========================================================
// Methods
// ===========================================================

void WealthManager::add(int pIndex)
{
	Entity* entity = this->create();

	entity->setCurrentFrameIndex(pIndex);

	Level::COINS[pIndex]++;

	this->update();
}

void WealthManager::remove(int pIndex)
{
	for(int i = 0; i < this->getCount(); i++)
	{
		if(((Entity*) this->objectAtIndex(i))->getCurrentFrameIndex() == pIndex)
		{
			((Entity*) this->objectAtIndex(i))->destroy();

			break;
		}
	}

	Level::COINS[pIndex]--;

	this->update();
}

void WealthManager::update()
{
	int p = 0;
	int s;

	for(int i = 0; i < 3; i++)
	{
		s = 0;

		for(int j = 0; j < this->getCount(); j++, p++)
		{
			Entity* entity = (Entity*) this->objectAtIndex(j);

			if(entity->getCurrentFrameIndex() != i) continue;

			entity->setCenterPosition(Utils::coord(250) + p, Utils::coord(30));

			this->atlasIndexForChild(entity, 10 + j);

			p += Utils::coord(12);
			s++;
		}

		if(s > 0) p += Utils::coord(15);
	}

	this->reorderBatch(true);
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif