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
        this->mPackText1 = CCLabelTTF::create("x %d", Options::SPECIAL_FONT, Utils::coord(18));
        this->mPackText2 = CCLabelTTF::create("x %d", Options::SPECIAL_FONT, Utils::coord(18));
        this->mPackText3 = CCLabelTTF::create("x %d", Options::SPECIAL_FONT, Utils::coord(18));
    
        this->mPackText1->setVisible(false);
        this->mPackText2->setVisible(false);
        this->mPackText3->setVisible(false);
        
        pScreen->addChild(this->mPackText1);
        pScreen->addChild(this->mPackText2);
        pScreen->addChild(this->mPackText3);
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
    
    bool dirty;

	for(int i = 0; i < 3; i++)
	{
		s = 0;
        
        dirty = false;

		for(int j = 0; j < this->getCount(); j++)
		{
			Entity* entity = (Entity*) this->objectAtIndex(j);

			if(entity->getCurrentFrameIndex() != i) continue;

			entity->setCenterPosition(Utils::coord(250) + p, Utils::coord(30));

			this->atlasIndexForChild(entity, 10 + j);
            
			s++;
            
            entity->setVisible(true);
            
            //
            
            if(s > 1)
            {
                if(Level::COINS[i] > 10)
                {
                    entity->setVisible(false);
                    
                    dirty = true;
                    
                    continue;
                }
            }
            
			p += Utils::coord(12);
		}

		if(s > 0) p += Utils::coord(15);
        
        if(dirty)
        {
            p += Utils::coord(10);
            
            char text[256];
            sprintf(text, "x %d", Level::COINS[i]);
            
            switch(i)
            {
                case 0:
                    this->mPackText1->setVisible(true);
                    this->mPackText1->setPosition(ccp(Utils::coord(250) + p, Utils::coord(30)));
                    this->mPackText1->setString(text);
                    break;
                    
                case 1:
                    this->mPackText2->setVisible(true);
                    this->mPackText2->setPosition(ccp(Utils::coord(250) + p, Utils::coord(30)));
                    this->mPackText2->setString(text);
                    break;
                    
                case 2:
                    this->mPackText3->setVisible(true);
                    this->mPackText3->setPosition(ccp(Utils::coord(250) + p, Utils::coord(30)));
                    this->mPackText3->setString(text);
                    break;
            }
            
            
            p += Utils::coord(50);
        }
        else
        {
            switch(i)
            {
                case 0:
                    this->mPackText1->setVisible(false);
                    break;
                    
                case 1:
                    this->mPackText2->setVisible(false);
                    break;
                    
                case 2:
                    this->mPackText3->setVisible(false);
                    break;
            }
        }
	}

	this->reorderBatch(true);
}

// ===========================================================
// Virtual Methods
// ===========================================================

void WealthManager::clear()
{
    BatchEntityManager::clear();
    
    this->mPackText1->setVisible(false);
    this->mPackText2->setVisible(false);
    this->mPackText3->setVisible(false);
}

#endif