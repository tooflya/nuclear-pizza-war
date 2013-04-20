#ifndef CONST_BATCHENTITYMANAGER
#define CONST_BATCHENTITYMANAGER

#include "BatchEntityManager.h"

BatchEntityManager::BatchEntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen) :
	CCSpriteBatchNode()
	{
		this->initWithFile(pEntity->mTextureFileName, 50);

		this->mLastElementNumber = -1;
		this->mCapacity = pCreateCount; // TODO: increase to pMaxCount

		for(int i = 0; i < pCreateCount; i++)
		{
			Entity* currentEntity = pEntity->deepCopy();

			currentEntity->setEntityManager(this);
			currentEntity->setEntityManagerId(i);

			this->addChild(currentEntity);
		
			currentEntity->destroy(false);
		}

		pScreen->addChild(this);
	}

Entity* BatchEntityManager::create()
{
	if (++this->mLastElementNumber < this->mCapacity)
	{
		Entity* object = (Entity*) this->objectAtIndex(this->mLastElementNumber);
		object->create();

		return object;
	}

	// Create a new object if manager hasn't free object.

	Entity* object = ((Entity*) this->objectAtIndex(0))->deepCopy(); // TODO: Increase CCArray capacity? Really? I think it's works like a charm!

	object->setEntityManager(this);
	object->setEntityManagerId(this->mCapacity);

	this->addChild(object);

	this->mCapacity++;

	return object->create();
}

void BatchEntityManager::destroy(int pIndex)
{
	if(this->mLastElementNumber >= 0)
	{
		this->getChildren()->exchangeObjectAtIndex(pIndex, this->mLastElementNumber);

		((Entity*) this->objectAtIndex(pIndex))->setEntityManagerId(pIndex);
		((Entity*) this->objectAtIndex(this->mLastElementNumber))->setEntityManagerId(this->mLastElementNumber);

		this->mLastElementNumber--;
	}
}

void BatchEntityManager::clear() // Some problem in this method with elements which will change and their ID
{
	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->destroy(true);
	}

	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->destroy();
	}
}

int BatchEntityManager::getCount()
{
	return this->mLastElementNumber + 1;
}

int BatchEntityManager::getCapacity()
{
	return this->mCapacity;
}

CCObject* BatchEntityManager::objectAtIndex(int pIndex)
{
	return this->getChildren()->objectAtIndex(pIndex);
}

#endif