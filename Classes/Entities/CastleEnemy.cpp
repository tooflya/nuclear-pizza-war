#ifndef CONST_CASTLEENEMY
#define CONST_CASTLEENEMY

#include "CastleEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

CastleEnemy::CastleEnemy(Castle* pCastle) :
<<<<<<< HEAD
	BaseEnemy("actors/alien2.png", 8, 1)
=======
	BaseEnemy("alien2.png", 8, 1)
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	{
		this->setAsCollidable();
		
		this->setBarsManagement(true, false);

		this->mCastle = pCastle;

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(40));

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.0f));
		this->animate(0.1f, 0, 14);

		// Shockwave

<<<<<<< HEAD
		this->mShockwave = new Entity("actors/alien_shockwave.png");
=======
		this->mShockwave = new Entity("alien_shockwave.png");
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
		this->mShockwave->setIgnoreSorting(true);

		//

		this->mShockwaveTime = 0.2f;
		this->mShockwaveTimeElapsed = 0;

		this->mShockwaveContinueTime = 1.0f;
		this->mShockwaveContinueTimeElapsed = 0;
	}

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

bool CastleEnemy::onCollide()
{
	if(this->mShockwaveTimeElapsed <= 0 && this->mShockwaveContinueTimeElapsed >= this->mShockwaveContinueTime)
	{
		this->mShockwaveContinueTimeElapsed = 0;

		this->mShockwave->setScale(0);
		this->mShockwave->create()->runAction(CCScaleTo::create(this->mShockwaveTime, 1.5f));

<<<<<<< HEAD
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alien_warning.ogg");
=======
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_ALIEN_WARNING);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

		this->removeHealth(20);
	}

	return false;
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* CastleEnemy::create()
{
	if(!this->mShockwave->getParent())
	{
		this->getParent()->addChild(this->mShockwave, 0);
	}

	return BaseEnemy::create();
}

bool CastleEnemy::destroy()
{
	this->mShockwave->destroy();

	return BaseEnemy::destroy();
}

void CastleEnemy::death()
{
<<<<<<< HEAD
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alien_suicide.ogg");
=======
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_ALIEN_SUICIDE);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

	this->destroy();
}

Entity* CastleEnemy::deepCopy()
{
	return new CastleEnemy(this->mCastle);
}

void CastleEnemy::move(float pDeltaTime)
{
	float vectorX = this->getCenterX() - Options::CAMERA_CENTER_X;
	float vectorY = this->getCenterY() - Options::CAMERA_CENTER_Y;

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	float x = this->getCenterX() - vector.x;
	float y = this->getCenterY() - vector.y;

	this->setCenterPosition(x, y);
}

void CastleEnemy::update(float pDeltaTime)
{
	if(!this->isVisible()) return;
	
	BaseEnemy::update(pDeltaTime);

	this->mShockwaveContinueTimeElapsed += pDeltaTime;

	if(this->mShockwave->isVisible())
	{
		this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(10));

		this->mShockwaveTimeElapsed += pDeltaTime;

		if(this->mShockwaveTimeElapsed >= this->mShockwaveTime)
		{
			this->mShockwaveTimeElapsed = 0;

			this->mShockwave->destroy();

			this->mCastle->removeHealth(1.0f);
		}
	}

	float magnet;

	switch(Options::FORTIFICATION_LEVEL)
	{
		case 0:
<<<<<<< HEAD
			magnet = 50.0f;
		break;
		case 1:
			magnet = 60.0f;
		break;
		case 2:
			magnet = 70.0f;
		break;
		case 3:
			magnet = 80.0f;
		break;
	}

	if(this->circlesCollideCoordinatesWith(this->getCenterX(), this->getCenterY(), Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y, Utils::coord((magnet)))) // TODO: Some problem here with small resolutions.
=======
			magnet = 70.0f;
		break;
		case 1:
			magnet = 80.0f;
		break;
		case 2:
			magnet = 90.0f;
		break;
		case 3:
			magnet = 100.0f;
		break;
	}

	if(this->circlesCollideCoordinatesWith(this->getCenterX(), this->getCenterY(), Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y, Utils::coord(magnet)))
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	{
		this->onCollide();
	}
}

#endif