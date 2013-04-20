#ifndef CONST_BARENTITY_H
#define CONST_BARENTITY_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class BarEntity : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

		float mHealth;
		float mMaxHealth;

		float mFireTime;
		float mMaxFireTime;

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor();

		// ===========================================================
		// Private fields
		// ===========================================================

		bool mIsHealthBarManagement;
		bool mIsFireBarManagement;

		bool mIsHealthBarShow;
		bool mIsFireBarShow;

		bool mIsHealthBarHidden;
		bool mIsFireBarHidden;

		CCPoint mRectangleVerticles1[4];
		CCPoint mRectangleVerticles2[4];
		CCPoint mRectangleVerticles3[4];
		CCPoint mRectangleVerticles4[4];

		float R1;
		float G1;
		float B1;

		float R2;
		float G2;
		float B2;

		float mBarWidth;
		float mBarHeight;

		static int const HEALTH_BAR_INDEX = 0;
		static int const FIRE_BAR_INDEX = 1;

		static float const COLOR_MAX_HEALTH = 75;
		static float const COLOR_MIN_HEALTH = 45;

		static float const VERTICLES_COUNT = 4;

		static float const BAR_PADDING = 1;

		// ===========================================================
		// Private methods
		// ===========================================================

		void updateBars(int pBarIndex);

	public:
		// ===========================================================
		// Constructors
		// ===========================================================

		BarEntity();
		BarEntity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		// ===========================================================
		// Getters
		// ===========================================================

		float getHealth();
		float getMaxHealth();

		float getFireTime();
		float getMaxFireTime();

		// ===========================================================
		// Setters
		// ===========================================================

		void setBarsManagement(float pHealth, float pFireTime);

		void setHealth(const float pHealth);
		void setMaxHealth(const float pMaxHealth);

		void setFireTime(const float pFireTime);
		void setMaxFireTime(const float pMaxFireTime);

		void setBarsWidth(float pWidth);
		void setBarsHeight(float pHeight);

		// ===========================================================
		// Checkers
		// ===========================================================

		// ===========================================================
		// Events
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void addHealth(float pHealth);

		void removeHealth(float pHealth);

		bool fire(float pVectorX, float pVectorY);

		void hideBars(bool pIsHideHealthBar, bool pIsHideFireBar);

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual void update(float pDeltaTime);

		virtual void draw();

		virtual void setScaleX(float pScaleX);
		
};

#endif