#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"
#include "BaseBullet.h"
#include "BaseEnemy.h"

Hero::Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount, bool pBroadcaster) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->setAsCollidable();

		this->mBroadcaster = pBroadcaster;

		this->mAnimationTime = 0.1f;
		this->mAnimationTimeElapsed = 0;

		this->mShockwaveTime = 0.2f;
		this->mShockwaveTimeElapsed = 0;

		this->mAnimationFrameSide = 0;

		this->mShockwave = new Entity("shockwave.png");
		this->mShockwave->setScale(0);

		this->mShadow = new Entity("shadow.png");
		this->mShadow->setIsShadow();

		this->mEngineParticlesAnimationTime = 0.3f;
		this->mEngineParticlesAnimationTimeElapsed = 0;

		this->mBulletsManager = pBulletsManager;

		this->mEngineParticles = new EntityManager(5, new EngineParticle());

		this->mBulletsTexture0 = new Texture("bullet.png", 1, 1);
		this->mBulletsTexture1 = new Texture("bullet1.png", 1, 1);
		this->mBulletsTexture2 = new Texture("bullet2.png", 1, 1); 
		this->mBulletsTexture3 = new Texture("bullet3.png", 1, 1); 

		this->reset();
	}

void Hero::reset()
{
	this->setVisible(true);

	this->setBarsManagement(true, true);
	this->hideBars(false, true);
	this->setFireTime(0.45f);
	this->setMaxFireTime(0.45f);
	this->setPatrons(100);

	this->setZ(Options::MIN_Z);

	this->mBulletsPower = 20;

	this->setHealth(100);

	this->mSpeedStandart = 4.5f;

	this->setSpeed(this->mSpeedStandart);

	this->setCurrentFrameIndex(2);

	this->mFollowCoordinateX = 0;
	this->mFollowCoordinateY = 0;

	this->mFireVectorX = 0;
	this->mFireVectorY = 0;

	this->mShootPaddingStandart = 0;
	this->mShootPadding = this->mShootPaddingStandart;

	this->mIsMove = false;
	this->mIsShouldFire = false;
	this->mIsDoubleFire = false;
	this->mIsTripleFire = false;
	this->mIsQuadrupleFire = false;

	this->mShouldLaserFire = false;
	this->mLaserRegenerationTime = 1;
	this->mLaserRegenerationTimeElapsed = 0;
	this->mLaserMaxPowerTime = 2.0f;
	this->mLaserPowerTime = 0.0f;

	this->mHealthRegenerationTime = 2.0f;
	this->mHealthRegenerationTimeElapsed = 0;

	this->mShootFromLeftHand = true;
	this->mIsFly = false;

	this->mJetPackPowerFull = 100.0f;
	this->mJetPackPower = this->mJetPackPowerFull;

	this->mShockwaveDamage = 3.0f;

	this->mShockwaveScale = 1.5f;
	
	this->mBulletsManager->changeTexture(this->mBulletsTexture0);

	this->mIsOutOfTop = false;
	this->mFall = false;

	this->setZOrder(5);
}

void Hero::laser()
{
	if(this->mLaserPowerTime > this->mLaserMaxPowerTime / 2)
	{
		this->mShouldLaserFire = true;
	}
}

void Hero::startFly()
{
	if(this->mIsFly) return;

	this->mIsFly = true;
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_PLAYER_ACCELERATING);

	if(AppDelegate::MULTIPLAYER && this->mBroadcaster)
	{
		broadcastMessage(0, 0, 0, 0);
	}
}

void Hero::endFly()
{
	if(!this->mIsFly) return;

	this->mIsFly = false;
	this->mFlyDownSpeed = 0;

	if(AppDelegate::MULTIPLAYER && this->mBroadcaster)
	{
		broadcastMessage(1, 0, 0, 0);
	}
}

bool Hero::isCanFly()
{
	return this->mJetPackPower > this->mJetPackPowerFull / 2;
}

bool Hero::startFlyDamage()
{
	if(this->mFlyDownSpeed >= 5) return false;
	if(this->getZ() < 10) return false;
	if(!Utils::isOnPizza(this)) return false;

	this->mIsFly = false;
	this->mFlyDownSpeed = 20;

	if(AppDelegate::MULTIPLAYER && this->mBroadcaster)
	{
		broadcastMessage(2, 0, 0, 0);
	}

	return true;
}

float Hero::getPatrons()
{
	return this->mPatrons;
}

void Hero::setPatrons(float pPatrons)
{
	this->mPatrons = pPatrons;
}

void Hero::setFollowCoordinates(float pX, float pY)
{
	this->mIsMove = true;

	this->mFollowCoordinateX = pX;
	this->mFollowCoordinateY = pY + this->getZ();

	this->setSpeed(this->mSpeedStandart);
}

void Hero::follow(float pDeltaTime)
{
	if(this->mIsMove && (abs(this->mFollowCoordinateX) > 1 && abs(this->mFollowCoordinateY) > 1))
	{
		this->setSpeed(this->getSpeed(1.0f) + 0.05f);

		float x = this->mFollowCoordinateX / this->getSpeed(1);
		float y = this->mFollowCoordinateY / this->getSpeed(1);

		x = this->getCenterX() - x * 0.015f;
		y = this->getCenterY() - y * 0.015f;

		this->setCenterPosition(x, y);
	}
}

void Hero::fire(float pVectorX, float pVectorY)
{
	if(BarEntity::fire(pVectorX, pVectorY))
	{
		pVectorX += this->getCenterX();
		pVectorY += this->getCenterY();

		if(this->mIsQuadrupleFire)
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(Utils::coord(45), Utils::coord(45));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(Utils::coord(15), Utils::coord(15));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(-Utils::coord(15), -Utils::coord(15));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(-Utils::coord(45), -Utils::coord(45));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
		
		}
		else if(this->mIsTripleFire)
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(Utils::coord(30), Utils::coord(30));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(-Utils::coord(30), -Utils::coord(30));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
		}
		else if(this->mIsDoubleFire)
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(Utils::coord(15), Utils::coord(15));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
			bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setFirePadding(-Utils::coord(15), -Utils::coord(15));
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
		}
		else
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
			bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
			bullet->setPower(this->mBulletsPower);
			bullet->setFZ(this->getZ());
		}

		this->mPatrons--;

		if(this->mBulletsPower < 30)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_SHOT);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_SHOT2);
		}
	}
}

bool Hero::onCollide(BaseBullet* pBullet)
{
	this->setRed();

	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = Utils::coord(5); // UPGRADE

	if(this->getHealth() <= 0)
	{
		this->destroy();

		return true;
	}

	return false;
}

bool Hero::onCollide(BaseEnemy* pEnemy)
{
	this->setRed();

	this->removeHealth(0.05f); // TODO: Adjust enemy power.

	if(this->getHealth() <= 0)
	{
		return true;
	}

	return false;
}

bool Hero::destroy()
{
	BarEntity::destroy();

	this->mShadow->destroy();
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_PLAYER_DEATH);

	return false;
}

void Hero::setCurrentFrameIndex(int pIndex)
{
	BarEntity::setCurrentFrameIndex(pIndex);
}

void Hero::update(float pDeltaTime)
{
	if(!this->isVisible())
	{
		return;
	}

	BarEntity::update(pDeltaTime);

	// TODO: Remove this to create() or reset()
	if(!((Entity*) this->mEngineParticles->objectAtIndex(0))->getParent())
	{
		this->mEngineParticles->setParent(this->getParent(), 4);
	}

	this->mAnimationTimeElapsed += pDeltaTime;

	if(mAnimationTimeElapsed >= this->mAnimationTime)
	{
		this->mAnimationTimeElapsed -= mAnimationTime;

		this->mAnimationFrameSide = this->mAnimationFrameSide == 3 ? 0 : this->mAnimationFrameSide + 1;
	}

	this->follow(pDeltaTime);

	if(this->mIsShouldFire && (abs(this->mFireVectorX) > 1 && abs(this->mFireVectorY) > 1))
	{
		this->fire(this->mFireVectorX, this->mFireVectorY);
	}

	int pontencialFrame = 8;

	int padding1 = Utils::coord(50);
	int padding2 = Utils::coord(150);
	int padding3 = Utils::coord(100);

	float fcx;
	float fcy;

	if(this->mShouldLaserFire)
	{
		fcx = this->getCenterX() - this->mLaserVectorX;
		fcy = this->getCenterY() - this->mLaserVectorY;
	}
	else if(this->mIsShouldFire)
	{
		fcx = -this->mFireVectorX;
		fcy = -this->mFireVectorY;
	}
	else
	{
		fcx = this->mFollowCoordinateX;
		fcy = this->mFollowCoordinateY;
	}

	if(fcy > padding1)
	{
		pontencialFrame += 4;

		if(fcy > padding2 && abs(fcx) < padding3)
		{
			pontencialFrame += 4;
		}
	}
	else if(fcy < -padding1)
	{
		pontencialFrame -= 4;

		if(fcy < -padding2 && abs(fcx) < padding3)
		{
			pontencialFrame -= 4;
		}
	}

	pontencialFrame += this->mAnimationFrameSide;

	if(fcx > 0)
	{
		this->setScaleX(1);
	}
	else
	{
		this->setScaleX(-1);
	}

	this->setCurrentFrameIndex(pontencialFrame);

    // padding on collide

	if(this->mShootPadding > 0)
	{
		float x = this->mShootVectorX;
		float y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		this->setCenterPosition(x, y);

		this->mShootPadding -= Utils::coord(0.3f);
	}

	
	this->mEngineParticlesAnimationTimeElapsed += pDeltaTime;

	if(this->mEngineParticlesAnimationTimeElapsed >= this->mEngineParticlesAnimationTime)
	{
		this->mEngineParticlesAnimationTimeElapsed -= this->mEngineParticlesAnimationTime;

		if(!this->mIsOutOfTop && !this->mFall)
		{
			this->mEngineParticles->create()->setCenterPosition(this->getCenterX(), this->getCenterY() + this->getZ() - Utils::coord(15));
		}
	}

	this->mHealthRegenerationTimeElapsed += pDeltaTime;

	if(this->mHealthRegenerationTimeElapsed >= this->mHealthRegenerationTime)
	{
		this->mHealthRegenerationTimeElapsed = 0;

		this->addHealth(1);
	}

	this->mLaserRegenerationTimeElapsed += pDeltaTime;



	if(this->mShouldLaserFire)
	{
		this->mLaserPowerTime -= 0.01f;

		if(this->mLaserPowerTime <= 0)
		{
			this->mShouldLaserFire = false;
		}
	}
	else
	{
		if(this->mLaserRegenerationTimeElapsed >= this->mLaserRegenerationTime)
		{
			this->mLaserRegenerationTimeElapsed = 0;

			//

			if(this->mLaserPowerTime < this->mLaserMaxPowerTime)
			{
				this->mLaserPowerTime += 0.1f;
			}
		}
	}

	if(this->mIsFly)
	{
		this->addZ(120.0f * pDeltaTime);

		this->mEngineParticlesAnimationTime = 0.1f;
		this->mJetPackPower = this->mJetPackPower > 0 ? this->mJetPackPower - 1.0f : 0;

		if(this->mJetPackPower <= 0)
		{
			this->endFly();
		}
	}
	else
	{
		if(this->getZ() > Options::MIN_Z)
		{
			this->mEngineParticlesAnimationTime = 1000.0f;

			this->mFlyDownSpeed += 0.04f;
			this->removeZ((this->mFlyDownSpeed * 60.0f) * pDeltaTime);
		}
		else
		{
			this->mEngineParticlesAnimationTime = 0.3f;

			this->mJetPackPower = this->mJetPackPower >= this->mJetPackPowerFull ? this->mJetPackPowerFull : this->mJetPackPower + 1.0f;

			if(this->mFlyDownSpeed >= 10.0f)
			{
				this->mShockwave->setScale(0);
				this->mShockwave->create()->runAction(CCScaleTo::create(0.2f, this->mShockwaveScale));

				this->mFlyDownSpeed = 0;
				this->mShockwaveTimeElapsed = 0;
			
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_JETPACK_FAIL);
			}
		}
	}

	this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY());

	this->mShockwaveTimeElapsed += pDeltaTime;

	if(this->mShockwaveTimeElapsed >= this->mShockwaveTime && this->mShockwave->isVisible())
	{
		this->mShockwave->destroy();
	}
}

void Hero::update(int type, int level)
{
	switch(type)
	{
		case 0: // Fire Damage
			switch(level)
			{
				case 1:
					this->mBulletsManager->changeTexture(this->mBulletsTexture1);
					this->mBulletsPower = 25;
				break;
				case 2:
					this->mBulletsManager->changeTexture(this->mBulletsTexture2);
					this->mBulletsPower = 28;
				break;
				case 3:
					this->mBulletsManager->changeTexture(this->mBulletsTexture3);
					this->mBulletsPower = 31;
				break;
			}
		break;

		case 1: // Fire Rate
			switch(level)
			{
				case 1:
					this->setMaxFireTime(0.40f);
				break;
				case 2:
					this->mIsDoubleFire = true;
					this->setMaxFireTime(0.35f);
				break;
				case 3:
					this->setMaxFireTime(0.30f);
				break;
				case 4:
					this->mIsTripleFire = true;
					this->setMaxFireTime(0.25f);
				break;
				case 5:
					this->mIsQuadrupleFire = true;
					this->setMaxFireTime(0.20f);
				break;
			}
		break;

		case 2: // Speed
			switch(level)
			{
				case 1:
					this->mSpeedStandart = 4.3f;
				break;
				case 2:
					this->mSpeedStandart = 4.1f;
				break;
				case 3:
					this->mSpeedStandart = 3.9f;
				break;
				case 4:
					this->mSpeedStandart = 3.7f;
				break;
				case 5:
					this->mSpeedStandart = 3.5f;
				break;
			}
		break;

		case 3: // Health Regeneration
			switch(level)
			{
				case 1:
					this->mHealthRegenerationTime = 1.7f;
				break;
				case 2:
					this->mHealthRegenerationTime = 1.4f;
				break;
				case 3:
					this->mHealthRegenerationTime = 1.1f;
				break;
				case 4:
					this->mHealthRegenerationTime = 0.8f;
				break;
				case 5:
					this->mHealthRegenerationTime = 0.5f;
				break;
			}
		break;

		case 4: // Max Health
			switch(level)
			{
				case 1:
					this->setHealth(150);
				break;
				case 2:
					this->setHealth(200);
				break;
				case 3:
					this->setHealth(250);
				break;
				case 4:
					this->setHealth(300);
				break;
				case 5:
					this->setHealth(350);
				break;
			}
		break;

		case 5: // Jetpack Power
			switch(level)
			{
				case 1:
					this->mJetPackPowerFull += 50.0f;
				break;
				case 2:
					this->mJetPackPowerFull += 50.0f;
				break;
			}
		break;

		case 6: // Shockwave Damage
			switch(level)
			{
				case 1:
					this->mShockwaveDamage = 4.0f;
					this->mShockwaveScale = 2.0f;
				break;
				case 2:
					this->mShockwaveDamage = 5.0f;
					this->mShockwaveScale = 2.5f;
				break;
				case 3:
					this->mShockwaveDamage = 6.0f;
					this->mShockwaveScale = 3.0f;
				break;
			}
		break;

		case 7: // Beam Ammo
			switch(level)
			{
				case 1:
					this->mLaserMaxPowerTime = 2.5f;
				break;
				case 2:
					this->mLaserMaxPowerTime = 3.0f;
				break;
				case 3:
					this->mLaserMaxPowerTime = 3.5f;
				break;
			}
		break;
	}
}

void Hero::setFireCoordinates(float pVectorX, float pVectorY)
{
	this->mFireVectorX = pVectorX;
	this->mFireVectorY = pVectorY;
}

void Hero::outOfSpace()
{
	return;
}

#endif