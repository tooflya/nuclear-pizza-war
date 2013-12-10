#ifndef CONST_CASTLE
#define CONST_CASTLE

#include "Castle.h"
#include "BaseEnemy.h"

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

Castle::Castle(EntityManager* pBullets) :
	BarEntity("artichoke.png", 8, 1)
	{
		this->mFortification = 12;

		this->mBullets = pBullets;

		this->mShockwaveTime = 30000.0f;
		this->mShockwaveTimeElapsed = 0;

		this->setBarsManagement(true, true);
		this->hideBars(false, true);

		this->setHealth(100.0f);
		this->setFireTime(1000.0f);

		this->mShockwave = new Entity("shockwave.png");

		this->mCastleWall1 = new Entity("wall1.png");
		this->mCastleWall2 = new Entity("wall2.png");
		this->mCastleWall3 = new Entity("wall3.png");

		this->mCastleWall1->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(3), Options::CAMERA_CENTER_Y - Utils::coord(36));
		this->mCastleWall2->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(3), Options::CAMERA_CENTER_Y - Utils::coord(36));
		this->mCastleWall3->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(3), Options::CAMERA_CENTER_Y - Utils::coord(36));

		this->mCastleWall1->setIgnoreSorting(true);
		this->mCastleWall2->setIgnoreSorting(true);
		this->mCastleWall3->setIgnoreSorting(true);

		this->mCastleWall3->setVisible(false);

		this->setIgnoreSorting(true);

		this->animate(0.1f);

		this->mShouldShoot = false;
	}

// ===========================================================
// Methods
// ===========================================================

void Castle::reset()
{
	this->mFortification = 12;

	this->setHealth(100.0f);
	this->setFireTime(1000.0f);

	this->mCastleWall1->setIgnoreSorting(true);
	this->mCastleWall2->setIgnoreSorting(true);
	this->mCastleWall3->setIgnoreSorting(true);

	this->mCastleWall3->setVisible(false);

	Options::FORTIFICATION_LEVEL = 2;
	Options::FORTIFICATION_HEALTH_LEVEL = this->mFortification;
}

void Castle::fire()
{
	this->mShouldShoot = true;
}

void Castle::unfire()
{
	this->mShouldShoot = false;
}

void Castle::update(int pType, int pLevel)
{
	switch(pType) // TODO: Adjust power to all upgrades.
	{
		case 0: // Tower Blaster
			switch(pLevel)
			{
				case 1:
					this->setMaxFireTime(20.0f);
				break;
				case 2:
					this->setMaxFireTime(15.0f);
				break;
				case 3:
					this->setMaxFireTime(10.0f);
				break;
				case 4:
					this->setMaxFireTime(5.0f);
				break;
				case 5:
					this->setMaxFireTime(1.0f);
				break;
			}
		break;
		case 1: // Nove Defence
			switch(pLevel)
			{
				case 1:
					this->mShockwaveTime = 15.0f;
				break;
				case 2:
					this->mShockwaveTime = 7.0f;
				break;
				case 3:
					this->mShockwaveTime = 3.0f;
				break;
			}
		break;
		case 2: // Fortification
			this->mFortification++;

			if(this->mFortification <= 0)
			{
				this->mCastleWall1->setVisible(false);
				this->mCastleWall2->setVisible(false);
				this->mCastleWall3->setVisible(false);

				Options::FORTIFICATION_LEVEL = 0;
			}
			else if(this->mFortification < 12)
			{
				this->mCastleWall1->setVisible(true);
				this->mCastleWall2->setVisible(false);
				this->mCastleWall3->setVisible(false);

				Options::FORTIFICATION_LEVEL = 1;
			}
			else if(this->mFortification < 20)
			{
				this->mCastleWall1->setVisible(true);
				this->mCastleWall2->setVisible(true);
				this->mCastleWall3->setVisible(false);

				Options::FORTIFICATION_LEVEL = 2;
			}
			else
			{
				this->mCastleWall1->setVisible(true);
				this->mCastleWall2->setVisible(true);
				this->mCastleWall3->setVisible(true);

				Options::FORTIFICATION_LEVEL = 3;
			}

			Options::FORTIFICATION_HEALTH_LEVEL = this->mFortification;
		break;
	}
}

bool Castle::isCanFire()
{
	return BarEntity::fire(-1, -1);
}

void Castle::fire(BaseEnemy* pEnemy)
{
	if(pEnemy == NULL) return;

	BaseBullet* bullet = (BaseBullet*) this->mBullets->create();
	bullet->setPower(10); // TODO: Add updates.

	bullet->fire(this->getCenterX(), this->getCenterY() + Utils::coord(50), pEnemy->getCenterX(), pEnemy->getCenterY());
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_SHOT);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* Castle::create()
{
	if(!this->mShockwave->getParent())
	{
		this->getParent()->addChild(this->mShockwave, 0);

		this->getParent()->addChild(this->mCastleWall1, 3);
		this->getParent()->addChild(this->mCastleWall2, 3);
		this->getParent()->addChild(this->mCastleWall3, 3);
	}

	return BarEntity::create();
}

void Castle::update(float pDeltaTime)
{
	BarEntity::update(pDeltaTime);

	this->mShockwaveTimeElapsed += pDeltaTime;

	if(this->mShockwaveTimeElapsed >= this->mShockwaveTime && this->mShouldShoot)
	{
		this->mShockwaveTimeElapsed = 0;

		this->mShockwave->setScale(0);
		this->mShockwave->create()->runAction(CCScaleTo::create(0.2f, 5.0f));
	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_BASE_SHOT);

		this->mShouldShoot = false;
	}
	else
	{
		if(this->mShockwave->isVisible())
		{
			if(this->mShockwaveTimeElapsed >= 0.2f)
			{
				this->mShockwave->destroy();
			}
		}
	}

	this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(30));
}

void Castle::removeHealth(float pHealth)
{
	if(this->mFortification <= 0)
	{
		BarEntity::removeHealth(pHealth);

		this->mCastleWall1->setVisible(false);
		this->mCastleWall2->setVisible(false);
		this->mCastleWall3->setVisible(false);

		Options::FORTIFICATION_LEVEL = 0;
	}
	else if(this->mFortification < 12)
	{
		this->mFortification--;

		this->mCastleWall1->setVisible(true);
		this->mCastleWall2->setVisible(false);
		this->mCastleWall3->setVisible(false);

		Options::FORTIFICATION_LEVEL = 1;
	}
	else if(this->mFortification < 20)
	{
		this->mFortification--;

		this->mCastleWall1->setVisible(true);
		this->mCastleWall2->setVisible(true);
		this->mCastleWall3->setVisible(false);

		Options::FORTIFICATION_LEVEL = 2;
	}
	else
	{
		this->mFortification--;

		this->mCastleWall1->setVisible(true);
		this->mCastleWall2->setVisible(true);
		this->mCastleWall3->setVisible(true);

		Options::FORTIFICATION_LEVEL = 3;
	}

	Options::FORTIFICATION_HEALTH_LEVEL = this->mFortification;
}

#endif