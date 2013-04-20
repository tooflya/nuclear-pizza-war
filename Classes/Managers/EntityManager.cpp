#ifndef CONST_ENTITYMANAGER
#define CONST_ENTITYMANAGER

#include "EntityManager.h"
#include "EntityManagerGroup.h"

void EntityManager::init(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen, int pZOrder)
{
	this->initWithCapacity(pCreateCount * 100);

	this->mUnified = NULL;

	this->mZOrder = pZOrder;
	this->mParent = pScreen;
	this->mLastElementNumber = -1;
	this->mCapacity = pCreateCount; // TODO: increase to pMaxCount

	for(int i = 0; i < pCreateCount; i++)
	{
		Entity* currentEntity = pEntity->deepCopy();

		currentEntity->setEntityManager(this);
		currentEntity->setEntityManagerId(i);

		this->addObject(currentEntity);

		if(pScreen != NULL)
		{
			this->mParent->addChild(currentEntity, pZOrder);
		}
		
		currentEntity->destroy(false);
	}
}

EntityManager::EntityManager(int pCreateCount, Entity* pEntity)
{
	this->init(pCreateCount, -1, pEntity, NULL, 0);
}

EntityManager::EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen)
{
	this->init(pCreateCount, -1, pEntity, pScreen, 0);
}

EntityManager::EntityManager(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen)
{
	this->init(pCreateCount, pMaxCount, pEntity, pScreen, 0);
}

EntityManager::EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen, int pZOrder)
{
	this->init(pCreateCount, -1, pEntity, pScreen, pZOrder);
}

Entity* EntityManager::create()
{
	if (++this->mLastElementNumber < this->mCapacity)
	{
		Entity* object = (Entity*) this->objectAtIndex(this->mLastElementNumber);
		object->create();

		if(Options::UNPUCKING)
		{
			if(this->mUnified != NULL)
			{
				this->mUnified->add(object);
			}
		}

		return object;
	}

	// Create a new object if manager hasn't free object.

	Entity* object = ((Entity*) this->objectAtIndex(0))->deepCopy(); // TODO: Increase CCArray capacity? Really? I think it's works like a charm!

	object->setEntityManager(this);
	object->setEntityManagerId(this->mCapacity);

	this->mParent->addChild(object, this->mZOrder);

	this->addObject(object);

	this->mCapacity++;

	if(Options::UNPUCKING)
	{
		if(this->mUnified != NULL)
		{
			this->mUnified->add(object);
		}
	}

	return object->create();
}

void EntityManager::setUnified(EntityManagerGroup* pEntityManagerGroup)
{
	this->mUnified = pEntityManagerGroup;
}

void EntityManager::destroy(int pIndex)
{
	if(Options::UNPUCKING)
	{
		if(this->mUnified != NULL)
		{
			this->mUnified->remove(((Entity*) this->objectAtIndex(pIndex)));
		}
	}

	if(this->mLastElementNumber >= 0)
	{
		this->exchangeObjectAtIndex(pIndex, this->mLastElementNumber);

		((Entity*) this->objectAtIndex(pIndex))->setEntityManagerId(pIndex);
		((Entity*) this->objectAtIndex(this->mLastElementNumber))->setEntityManagerId(this->mLastElementNumber);

		this->mLastElementNumber--;
	}
}

void EntityManager::changeTexture(Texture* pTexture)
{
	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->changeTexture(pTexture);
	}
}

int EntityManager::getCount()
{
	return this->mLastElementNumber + 1;
}

int EntityManager::getCapacity()
{
	return this->mCapacity;
}

void EntityManager::clear() // Some problem in this method with elements which will change and their ID
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

void EntityManager::setParent(CCNode* pScreen, int pZOrder)
{
	this->mParent = pScreen;

	for(int i = 0; i < this->getCapacity(); i++)
	{
		this->mParent->addChild((Entity*) this->objectAtIndex(i), pZOrder);
	}
}

void EntityManager::setParent(CCNode* pScreen)
{
	this->mParent = pScreen;

	for(int i = 0; i < this->getCapacity(); i++)
	{
		this->mParent->addChild((Entity*) this->objectAtIndex(i));
	}
}

void EntityManager::update(float pDeltaTime)
{
}

#endif