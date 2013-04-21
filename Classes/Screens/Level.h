#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "AppDelegate.h"

#include "EntityManager.h"
#include "BatchEntityManager.h"
#include "EntityManagerGroup.h"
#include "LayerManager.h"
#include "BaseExplosion.h"
#include "LongExplosion.h"
#include "SpiderExplosion.h"
#include "FollowEnemy.h"
#include "FiredEnemy.h"
#include "CastleEnemy.h"
#include "BigEnemy.h"
#include "Pickup.h"
#include "Bubble.h"
#include "Slice.h"
#include "Castle.h"
#include "BaseBullet.h"
#include "EnemyBullet.h"
#include "Hero.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"
#include "EnemyWave.h"
#include "EnemyGroup.h"
#include "WealthManager.h"
#include "Joystick.h"
#include "Spider.h"

class UpgradeManager;

#include "BackgroundStarsManager.h"

using namespace cocos2d;

class Level : public Screen
{
	protected:
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

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		static const char* LABELS_FONT;

		static const char* PREPARE_FOR_BATTLE_TEXT;
		static const char* LEVEL_NUMBER_TEXT;
		static const char* WEALTH_TEXT;
		static const char* LOW_HEALTH_TEXT;
		static const char* LEVEL_BEGIN_TEXT;
		static const char* LEVEL_CLEARED_TEXT;
		static const char* WIN_TEXT;
		static const char* LARGE_INVASION_TEXT;
		static const char* BEWARE_TEXT;
		static const char* PATIENCE_TEXT;
		static const char* THE_ELITE_TEXT;
		static const char* NUKES_TEXT;
		static const char* THE_HORDE_TEXT;
		static const char* DEATH_TEXT;
		static const char* ALTERLIFE_TEXT;

		// ===========================================================
		// Fields
		// ===========================================================

		float mStartBattleTime;
		float mStartBattleTimeElapsed;

		float mBubbleAppearTime;
		float mBubbleAppearTimeElapsed;

		float mTestLevelTime;
		float mTestLevelTimeElapsed;

		float mPizzaPartTime;
		float mPizzaPartTimeElapsed;

		float mLowHealthTime;
		float mLowHealthTimeElapsed;

		float mShakeDuration;
		float mShakeIntensity;
		float mShakeDurationElapsed;

		float mPointerX;
		float mPointerY;

		float mSpidersRestoreTime;
		float mSpidersRestoreTimeElasped;

		float mUpgradeLevelStartTime;
		float mUpgradeLevelStartTimeElapsed;

		float mShowLevelTextPauseTime;
		float mShowLevelTextPauseTimeElapsed;

		float mHeroFollowCoordinateX;
		float mHeroFollowCoordinateY;

		float mHeroLaserTime;
		float mHeroLaserTimeElapsed;

		float mLaserVectorX;
		float mLaserVectorY;

		bool mStartBattleShows;
		bool mIsGameStarted;
		bool mIsLevelLabelShows;
		bool mIsShouldStartLevel;
		bool mShaking;

		bool mUpgradeLevelStartText;

		bool mShouldShowSeconds;

		int mCurrentLevel;
		int mMaxSpidersCount;

		int mTextSeconds;

		EntityManager* mEnemies1;
		EntityManager* mEnemies2;
		EntityManager* mEnemies3;
		EntityManager* mEnemies4;

		EntityManager* mEnemyBullets;

		EntityManager* mSlices;
		EntityManager* mSpiders;

		EntityManager* mEnemiesExplosions;

		CCLayer* mMainLayer;
		CCLayer* mStaticLayer;

		CCLabelTTF* mPrepareToBattle;
		CCLabelTTF* mLevelName;
		CCLabelTTF* mWealthText;
		CCLabelTTF* mLowHealthText;
		CCLabelTTF* mLevelStartText;

		Entity* mBackground;
		Entity* mLaser1;
		Entity* mLaser2;

		EntityManager* mBaseBullets;
		EntityManager* mCastleBullets;
		EntityManager* mBaseBubbles;
		EntityManager* mPickups;
		EntityManager* mHeroExplosions;
		EntityManager* mSpidersExplosions;

		EnemyWave* mEnemiesWave;

		Joystick* mLeftJoystick;
		Joystick* mRightJoystick;

		long mLastTimeTapLeft;
		long mLastTimeTapRight;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void startLevel();
		void finishLevel();

		void generatePizzaDecorations();

		CCPoint getSafePizzaPosition();

		void checkCollisions(float pDeltaTime);

		void shake(float d, float i);
		void updateShake(float pDeltaTime);

		BaseEnemy* getClosestEnemy(Entity* mObject);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		static int ENTITIES;

		static int* COINS;

		// ===========================================================
		// Fields
		// ===========================================================

		Entity* mPauseButton;

		CCArray* mEnemies;

		Castle* mCastle;

		EntityManagerGroup* mEnemiesGroup;

		UpgradeManager* mUpgradeLayer;

		LayerManager* mUnitsLayer;

		WealthManager* mWealth;

		Hero* mHero;

		bool mPause;

		// ===========================================================
		// Constructors
		// ===========================================================

		Level();

		// ===========================================================
		// Methods
		// ===========================================================

		void updateSpiders();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		void ccTouchMoved(CCTouch* touch, CCEvent* event);
		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		virtual	void update(float pDeltaTime);
		virtual void draw();

		virtual void onEnter();
		virtual void onExit();

		void renderLaserBeam(float angle, float sx, float sy, float ex, float ey);
};

#endif