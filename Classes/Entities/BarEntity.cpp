#ifndef CONST_BARENTITY
#define CONST_BARENTITY

#include "BarEntity.h"

// ===========================================================
// Init
// ===========================================================

void BarEntity::constructor()
{
	this->mBarWidth = Utils::coord(28);
	this->mBarHeight = Utils::coord(5);
	
	this->mHealth = 0;
	this->mMaxHealth = 0;

	this->mFireTime = 0;
	this->mMaxFireTime = 0;

	this->mIsHealthBarShow = false;

	this->mIsHealthBarManagement = false;
	this->mIsFireBarManagement = false;

	this->mIsHealthBarHidden = false;
	this->mIsFireBarHidden = false;
}

// ===========================================================
// Constructors
// ===========================================================

BarEntity::BarEntity()
{
	this->constructor();
}

BarEntity::BarEntity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->constructor();
	}

// ===========================================================
// Getters
// ===========================================================

float BarEntity::getHealth()
{
	return this->mHealth;
}

float BarEntity::getMaxHealth()
{
	return this->mMaxHealth;
}

float BarEntity::getFireTime()
{
	return this->mFireTime;
}

float BarEntity::getMaxFireTime()
{
	return this->mMaxFireTime;
}

// ===========================================================
// Setters
// ===========================================================

void BarEntity::setHealth(float pHealth)
{
	// If mMaxHealth is not defined we must to define it as full mHealth
	if(this->mMaxHealth == 0)
	{
		this->mMaxHealth = pHealth;
	}

	this->mHealth = pHealth;

	if(this->mIsHealthBarManagement)
	{
		this->updateBars(HEALTH_BAR_INDEX);
	}
}

void BarEntity::setMaxHealth(float pMaxHealth)
{
	this->mHealth = pMaxHealth;
	this->mMaxHealth = pMaxHealth;
}

void BarEntity::setFireTime(float pFireTime)
{
	// If mMaxFireTime is not defined we must to define it as full mFireTime
	if(this->mMaxFireTime == 0)
	{
		this->mMaxFireTime = pFireTime;
	}

	this->mFireTime = 0;
}

void BarEntity::setMaxFireTime(float pMaxFireTime)
{
	this->mFireTime = pMaxFireTime;
	this->mMaxFireTime = pMaxFireTime;
}

void BarEntity::setBarsManagement(float pHealth, float pFireTime)
{
	this->mIsHealthBarManagement = pHealth;
	this->mIsFireBarManagement = pFireTime;

	this->mIsFireBarShow = pFireTime; // TODO: Maybe it would be greate if I transfer this somewhere...
}

void BarEntity::setBarsWidth(float pWidth)
{
	this->mBarWidth = pWidth;
}

void BarEntity::setBarsHeight(float pHeight)
{
	this->mBarHeight = pHeight;
}

// ===========================================================
// Methods
// ===========================================================

void BarEntity::addHealth(float pHealth)
{
	this->mHealth += pHealth;

	if(this->mHealth >= this->mMaxHealth)
	{
		// Health bar level correction
		this->mHealth = this->mMaxHealth;
	}

	this->updateBars(HEALTH_BAR_INDEX);
	this->updateBars(FIRE_BAR_INDEX); // TODO: I don't want to do that! :(
}

void BarEntity::removeHealth(float pHealth)
{
	this->mHealth -= pHealth;

	// We must call some "die" method if health are not enought
	if(this->mHealth <= 0)
	{
		// TODO: Call "die" method

		// Health bar level correction
		this->mHealth = 0;
	}

	this->updateBars(HEALTH_BAR_INDEX);
	this->updateBars(FIRE_BAR_INDEX); // TODO: I don't want to do that! :(
}

void BarEntity::updateBars(int pBarIndex)
{
	// For calculation of new coordinates
	float x1;
	float x2;

	float y1;
	float y2;

	switch(pBarIndex)
	{
		case HEALTH_BAR_INDEX:
			// Setting up colors for health bar
			this->R1 = this->mHealth < COLOR_MAX_HEALTH ? 1 : 0;
			this->G1 = this->mHealth > COLOR_MIN_HEALTH ? 1 : 0;
			this->B1 = 0;

			// Is we must to show health bar?
			if(this->mHealth < this->mMaxHealth)
			{
				this->mIsHealthBarShow = true;
			}
			else
			{
				this->mIsHealthBarShow = false;
			}

			// Setting up black rectangle

			x1 = (this->getWidth() - this->mBarWidth) / 2;
			x2 = this->getWidth() - x1 + BAR_PADDING * 2;

			y1 = -Utils::coord(5);
			y2 = y1 - this->mBarHeight;

			this->mRectangleVerticles1[0] = ccp(x1, y1);
			this->mRectangleVerticles1[1] = ccp(x2, y1);
			this->mRectangleVerticles1[2] = ccp(x2, y2);
			this->mRectangleVerticles1[3] = ccp(x1, y2);

			// Setting up health rectangle

			x1 = x1 + BAR_PADDING;
			x2 = x1 + (((x2 - x1) - BAR_PADDING) * (this->getHealth() / this->getMaxHealth()));

			y1 = y1 - BAR_PADDING;
			y2 = y1 - this->mBarHeight + BAR_PADDING * 2;

			if(this->getScaleX() < 0)
			{
				float padding = this->mBarWidth - this->mBarWidth * (this->getHealth() / this->getMaxHealth());

				x1 += padding;
				x2 += padding;
			}

			this->mRectangleVerticles2[0] = ccp(x1, y1);
			this->mRectangleVerticles2[1] = ccp(x2, y1);
			this->mRectangleVerticles2[2] = ccp(x2, y2);
			this->mRectangleVerticles2[3] = ccp(x1, y2);
		break;

		case FIRE_BAR_INDEX:
			// Setting up colors for fire time bar
			this->R2 = 0;
			this->G2 = 200.0 / 255.0;
			this->B2 = 200.0 / 255.0;

			this->mIsFireBarShow = true;

			float padding;

			if(this->mIsHealthBarShow)
			{
				padding = 6;
			}
			else
			{
				padding = 0;
			}

			// Setting up black rectangle

			x1 = (this->getWidth() - this->mBarWidth) / 2;
			x2 = this->getWidth() - x1 + BAR_PADDING * 2;

			y1 = -Utils::coord(5) - padding;
			y2 = y1 - this->mBarHeight;

			this->mRectangleVerticles3[0] = ccp(x1, y1);
			this->mRectangleVerticles3[1] = ccp(x2, y1);
			this->mRectangleVerticles3[2] = ccp(x2, y2);
			this->mRectangleVerticles3[3] = ccp(x1, y2);

			// Setting up fire time rectangle

			x1 = x1 + BAR_PADDING;
			x2 = x1 + (((x2 - x1) - BAR_PADDING) * (this->getFireTime() / this->getMaxFireTime()));

			y1 = y1 - BAR_PADDING;
			y2 = y1 - this->mBarHeight + BAR_PADDING * 2;

			if(this->getScaleX() < 0)
			{
				float padding = this->mBarWidth - this->mBarWidth * (this->getFireTime() / this->getMaxFireTime());

				x1 += padding;
				x2 += padding;
			}

			this->mRectangleVerticles4[0] = ccp(x1, y1);
			this->mRectangleVerticles4[1] = ccp(x2, y1);
			this->mRectangleVerticles4[2] = ccp(x2, y2);
			this->mRectangleVerticles4[3] = ccp(x1, y2);
		break;
	}
}

bool BarEntity::fire(float pVectorX, float pVectorY)
{
	if(this->mFireTime < this->mMaxFireTime)
	{
		return false;
	}
	
	this->mFireTime = 0;

	return true;
}

void BarEntity::hideBars(bool pIsHideHealthBar, bool pIsHideFireBar)
{
	this->mIsHealthBarHidden = pIsHideHealthBar;
	this->mIsFireBarHidden = pIsHideFireBar;
}

// ===========================================================
// Virtual methods
// ===========================================================

void BarEntity::setScaleX(float pScaleX)
{
	Entity::setScaleX(pScaleX);

	if(this->mIsHealthBarShow && this->mIsHealthBarManagement)
	{
		this->updateBars(HEALTH_BAR_INDEX);
	}

	if(this->mIsFireBarShow && this->mIsFireBarManagement)
	{
		this->updateBars(FIRE_BAR_INDEX);
	}
}

void BarEntity::update(float pDeltaTime)
{
	if(!this->isVisible()) return;
	
	Entity::update(pDeltaTime);

	if(this->mIsFireBarManagement)
	{
		if(this->mFireTime < this->mMaxFireTime)
		{
			this->mFireTime += pDeltaTime;

			// Some corection of wrong value if pDeltaTime > (this->mMaxFireTime - this->mFireTime)
			this->mFireTime = this->mFireTime > this->mMaxFireTime ? this->mMaxFireTime : this->mFireTime;

			this->updateBars(FIRE_BAR_INDEX);
		}
	}
}

void BarEntity::draw()
{
	Entity::draw();

	if(this->mIsHealthBarShow && this->mIsHealthBarManagement && !this->mIsHealthBarHidden)
	{
		ccDrawSolidPoly(this->mRectangleVerticles1, VERTICLES_COUNT, ccc4f(0, 0, 0, 1));
		ccDrawSolidPoly(this->mRectangleVerticles2, VERTICLES_COUNT, ccc4f(this->R1, this->G1, this->B1, 1));
	}

	if(this->mIsFireBarShow && this->mIsFireBarManagement && !this->mIsFireBarHidden)
	{
		ccDrawSolidPoly(this->mRectangleVerticles3, VERTICLES_COUNT, ccc4f(0, 0, 0, 1));
		ccDrawSolidPoly(this->mRectangleVerticles4, VERTICLES_COUNT, ccc4f(this->R2, this->G2, this->B2, 1));
	}
}

#endif