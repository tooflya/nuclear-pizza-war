#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy()
{
}

BaseEnemy::BaseEnemy(Hero* pHero, EntityManager* pBullets)
{
	this->mHero = pHero;
	this->mBullets = pBullets;
}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mShadow = new Entity("shadow.png");
		this->mShadow->setIsShadow();

		this->mShootPadding = 0;

		this->setHealth(100.0f);
		this->setFireTime(Utils::randomf(3.0f, 15.0f));

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.5f));
		this->animate(0.1f);

		this->resumeSchedulerAndActions();
	}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mHero = pHero;
		this->mBullets = pBullets;
	}

void BaseEnemy::death()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ai_death.ogg");

	this->destroy();
}

Entity* BaseEnemy::create()
{
	this->mShadow->create();

	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 4);
	}

	this->mSpeedStandart = 30.0f;

	this->mShootPadding = 0;

	this->setSpeed(this->mSpeedStandart); // I should remove this

	this->setScale(0.0f);
	this->mShadow->setScale(0.0f);

	this->runAction(CCScaleTo::create(0.5f, 1.0f));
	this->mShadow->runAction(CCScaleTo::create(0.5f, 1.0f));

	this->setHealth(100.0f);
	this->setFireTime(Utils::randomf(3.0f, 15.0f));

	return BarEntity::create();
}

bool BaseEnemy::destroy()
{
	BarEntity::destroy();

	this->mShadow->destroy(false);

	if(Utils::probably(50))
	{
		return true;
	}

	return false;
}

void BaseEnemy::onCollideC(Castle* pCastle)
{
	this->removeHealth(10); // TODO: Adjust Castle power.

	this->mShootVectorX = this->getCenterX() > pCastle->getCenterX() ? pCastle->getCenterX() : -pCastle->getCenterX();
	this->mShootVectorY = this->getCenterY() > pCastle->getCenterY() ? pCastle->getCenterY() : -pCastle->getCenterY();

	this->mShootPadding = Utils::coord(3.0f); // UPGRADE
}

bool BaseEnemy::onCollide(BaseBullet* pBullet)
{
	this->setRed();

	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = Utils::coord(3.0f); // UPGRADE

	if(this->getHealth() <= 0)
	{
		this->death();

		return true;
	}

	return false;
}

bool BaseEnemy::onCollide(float pDamage, float pVectorX, float pVectorY)
{
	this->setRed();

	this->removeHealth(pDamage);
	
	this->mShootVectorX = pVectorX;
	this->mShootVectorY = pVectorY;

	this->mShootPadding = Utils::coord(5.0f); // UPGRADE

	if(this->getHealth() <= 0)
	{
		this->death();

		return true;
	}

	return false;
}

void BaseEnemy::onCollide(Hero* pEntity)
{
}

void BaseEnemy::update(float pDeltaTime)
{
	if(this->getScaleX() <= 0)
	{
		return;
	}
	
	if(!this->isVisible()) 
	{
		this->setCenterPosition(-1000, -1000);
		this->mShadow->setCenterPosition(-1000, -1000);

		return;
	}

	BarEntity::update(pDeltaTime);

	float x;
	float y;
	
    // padding on collide

	if(this->mShootPadding > 0)
	{
		x = this->mShootVectorX;
		y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		this->setCenterPosition(x, y);

		this->mShootPadding -= Utils::coord(0.3f);
	}
	else
	{
		this->move(pDeltaTime);
	}

	// Fire

	//if(BarEntity::fire(this->mHero->getCenterX(), this->mHero->getCenterY()))
	//{
		//this->fire();
	//}
}

void BaseEnemy::move(float pDeltaTime)
{

}

void BaseEnemy::fire()
{
	BaseBullet* bullet = ((BaseBullet*) this->mBullets->create());
	bullet->setSpeed(250);
	bullet->setPower(1);
	//bullet->fire(this->getCenterX(), this->getCenterY(), this->mHero->getCenterX(), this->mHero->getCenterY());
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alienshot.ogg");
}

#endif