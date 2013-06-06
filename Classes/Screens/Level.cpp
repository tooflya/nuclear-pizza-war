#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

#include "UpgradeManager.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PauseButton : public Entity
{
	private:
		Level* mWorld;

	public:
		PauseButton(Level* pWorld) :
			Entity("pause_button.png")
			{
				this->mWorld = pWorld;

				//this->setRegisterAsTouchable(true);
			}

		void onTouch(CCTouch* touch, CCEvent* event)
		{
			if(this->mWorld->mUpgradeLayer->getParent())
			{
				this->mWorld->removeChild(this->mWorld->mUpgradeLayer);
				this->mWorld->mUnitsLayer->onEnter();

				this->mWorld->mPause = false;
			}
			else
			{
				this->mWorld->addChild(this->mWorld->mUpgradeLayer);
				this->mWorld->mUnitsLayer->onExit();
				
				this->mWorld->mPause = true;
			}
		}

};

// ===========================================================
// Constants
// ===========================================================

int Level::ENTITIES = 0;

int* Level::COINS = new int[3];

const char* Level::LABELS_FONT = Options::SPECIAL_FONT;

const char* Level::PREPARE_FOR_BATTLE_TEXT = "Prepare for Battle";
const char* Level::LEVEL_NUMBER_TEXT = "Level %d %s";
const char* Level::WEALTH_TEXT = "Wealth:";
const char* Level::LOW_HEALTH_TEXT = "Warning: Low Health";
const char* Level::LEVEL_BEGIN_TEXT = "Level %d will begin in %d seconds...";
const char* Level::LEVEL_CLEARED_TEXT = "Level cleared!";
const char* Level::WIN_TEXT = "You won, I guess...";
const char* Level::LARGE_INVASION_TEXT = "- LARGE INVASION";
const char* Level::BEWARE_TEXT = "- BEWARE";
const char* Level::PATIENCE_TEXT = "- PATIENCE";
const char* Level::THE_ELITE_TEXT = "- THE ELITE";
const char* Level::NUKES_TEXT = "- NUKES";
const char* Level::THE_HORDE_TEXT = "- THE HORDE";
const char* Level::DEATH_TEXT = "- DEATH";
const char* Level::ALTERLIFE_TEXT = "- ALTERLIFE";

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Level::Level()
{
	ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
    	case kLanguageRussian:
        	LABELS_FONT = "Arial";

        	PREPARE_FOR_BATTLE_TEXT = "Приготовьтесь к битве";
			LEVEL_NUMBER_TEXT = "Уровень %d %s";
			WEALTH_TEXT = "Материалы:";
			LOW_HEALTH_TEXT = "Внимание: жизни на исходе";
			LEVEL_BEGIN_TEXT = "Уровень %d начнется через %d секунд...";
			LEVEL_CLEARED_TEXT = "Уровень пройден!";
			WIN_TEXT = "Ты выиграл, пока что...";
			LARGE_INVASION_TEXT = "- Большое нападение";
			BEWARE_TEXT = "- Берегись!";
			PATIENCE_TEXT = "- Спокойствие";
			THE_ELITE_TEXT = "- Элита";
			NUKES_TEXT = "- Ядерное оружие";
			THE_HORDE_TEXT = "- Орда";
			DEATH_TEXT = "- Смерть";
			ALTERLIFE_TEXT = "- Возрождение";
        break;
    }

	COINS[0] = 0;
	COINS[1] = 0;
	COINS[2] = 0;

	this->mLastTimeTapLeft = 0;

	this->setRegisterAsTouchable(true);

	this->mPause = false;

	this->mBubbleAppearTime = 1.0f;
	this->mBubbleAppearTimeElapsed = 0;

	this->mHeroLaserTime = 0.2f;
	this->mHeroLaserTimeElapsed = 0;

	this->mStartBattleTime = 5.0f;
	this->mStartBattleTimeElapsed = 0;

	this->mTestLevelTime = 10.0f;
	this->mTestLevelTimeElapsed = 0;

	this->mPizzaPartTime = 10.0f;
	this->mPizzaPartTimeElapsed = 0;

	this->mLowHealthTime = 1.5f;
	this->mLowHealthTimeElapsed = 0;

	this->mUpgradeLevelStartTime = 1.0f;
	this->mUpgradeLevelStartTimeElapsed = 0;

	this->mShowLevelTextPauseTime = 5.0f;
	this->mShowLevelTextPauseTimeElapsed = 0;

	this->mCurrentLevel = 0;

	this->mTextSeconds = 0;

	this->mStartBattleShows = true;
	this->mIsShouldStartLevel = true;
	this->mIsLevelLabelShows = false;
	this->mIsGameStarted = false;
	this->mShouldShowSeconds = false;

	this->mEnemies = new CCArray();
	this->mEnemies->initWithCapacity(4);

	this->mEnemiesGroup = new EntityManagerGroup(4);

	this->mUnitsLayer = new LayerManager();

	this->mMainLayer = new CCLayer();
	this->mStaticLayer = new CCLayer();
	this->mUpgradeLayer = new UpgradeManager(this);

	new BackgroundStarsManager(this->mMainLayer, true);

	this->mBackground = new Entity("pizza_big.png");
	this->mBackground->setIgnoreSorting(true);

	this->generatePizzaDecorations();

	this->mLaser1 = new Entity("laser.png", 1, 4);
	this->mLaser2 = new Entity("laser.png", 1, 4);
	this->mLaser1->animate(0.1f);
	this->mLaser2->animate(0.1f);
	this->mLaser1->setIgnoreSorting(true);
	this->mLaser2->setIgnoreSorting(true);
    
    this->mDiamonds = new EntityManager(5, new Diamond(), this->mUnitsLayer, 5);

	this->mCastleBullets = new EntityManager(5, new BaseBullet(), this->mUnitsLayer, 5);
	this->mCastle = new Castle(this->mCastleBullets);
	this->mPickups = new EntityManager(25, new Pickup(), this->mUnitsLayer, 5);
	this->mWealth = new WealthManager(25, new Entity("pickups.png", 1, 3), this->mStaticLayer, 2);
	this->mBaseBubbles = new EntityManager(5, new Bubble(), this->mUnitsLayer, 3);
	this->mBaseBullets = new EntityManager(50, new BaseBullet(), this->mUnitsLayer, 5);
	this->mHero = new Hero("player1_1.png", this->mBaseBullets, 4, 5);
	this->mEnemyBullets = new EntityManager(25, new EnemyBullet(), this->mUnitsLayer, 5);
	this->mEnemies1 = new EntityManager(20, new FollowEnemy(this->mHero), this->mUnitsLayer, 5);
	this->mEnemies2 = new EntityManager(20, new CastleEnemy(this->mCastle), this->mUnitsLayer, 5);
	this->mEnemies3 = new EntityManager(20, new FiredEnemy(this->mHero, this->mEnemyBullets), this->mUnitsLayer, 5);
	this->mEnemies4 = new EntityManager(20, new BigEnemy(this->mEnemyBullets), this->mUnitsLayer, 5);
	this->mEnemies5 = new EntityManager(20, new MineEnemy(), this->mUnitsLayer, 5);
	this->mSpiders = new EntityManager(5, new Spider(), this->mUnitsLayer, 3);
    
    Entity* diamondIcon = new Entity("diamond_icon.png");
    diamondIcon->create()->setCenterPosition(Utils::coord(24), Options::CAMERA_HEIGHT - Utils::coord(22));
    this->mStaticLayer->addChild(diamondIcon);

	this->mPauseButton = new PauseButton(this);
	this->mPauseButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(50), Options::CAMERA_HEIGHT - Utils::coord(50));

	this->mEnemiesExplosions = new EntityManager(5, new BaseExplosion(), this->mUnitsLayer, 5);
	this->mSpidersExplosions = new EntityManager(5, new SpiderExplosion(), this->mUnitsLayer, 5);
	this->mHeroExplosions = new EntityManager(5, new LongExplosion(), this->mUnitsLayer, 5);

	this->mEnemies->addObject(this->mEnemies1);
	this->mEnemies->addObject(this->mEnemies2);
	this->mEnemies->addObject(this->mEnemies3);
	this->mEnemies->addObject(this->mEnemies4);
	this->mEnemies->addObject(this->mEnemies5);

	this->mEnemiesGroup->add(this->mEnemies1);
	this->mEnemiesGroup->add(this->mEnemies2);
	this->mEnemiesGroup->add(this->mEnemies3);
	this->mEnemiesGroup->add(this->mEnemies4);
	this->mEnemiesGroup->add(this->mEnemies5);

    char text[256];
    sprintf(text, "x %d", CCUserDefault::sharedUserDefault()->getIntegerForKey("diamonds"));
    this->mDiamondCounterText = CCLabelTTF::create(text, LABELS_FONT, Utils::coord(18));
	this->mPrepareToBattle = CCLabelTTF::create(PREPARE_FOR_BATTLE_TEXT, LABELS_FONT, Utils::coord(65));
	this->mLevelName = CCLabelTTF::create(LEVEL_NUMBER_TEXT, LABELS_FONT, Utils::coord(48));
	this->mWealthText = CCLabelTTF::create(WEALTH_TEXT, LABELS_FONT, Utils::coord(18));
	this->mLowHealthText = CCLabelTTF::create(LOW_HEALTH_TEXT, LABELS_FONT, Utils::coord(65));
	this->mLevelStartText = CCLabelTTF::create(LEVEL_BEGIN_TEXT, LABELS_FONT, Utils::coord(24));

	this->mUnitsLayer->addChild(this->mBackground, -1);
	this->mUnitsLayer->addChild(this->mCastle, 4);
	this->mUnitsLayer->addChild(this->mLaser1, 4);
	this->mUnitsLayer->addChild(this->mLaser2, 4);

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mCastle->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mHero->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200));

	this->mPrepareToBattle->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200)));
	this->mLevelName->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150)));
	this->mWealthText->setPosition(ccp(Utils::coord(180), Utils::coord(30)));
	this->mLowHealthText->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200)));
	this->mLevelStartText->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(150)));
	this->mLowHealthText->setColor(ccc3(255.0f, 0.0f, 0.0f));
	this->mLowHealthText->setOpacity(0);
	this->mLevelStartText->setOpacity(0);
    this->mDiamondCounterText->setPosition(ccp(Utils::coord(50), Options::CAMERA_HEIGHT - Utils::coord(22)));
    
	this->addChild(this->mMainLayer);
	this->addChild(this->mStaticLayer);

	this->mMainLayer->addChild(this->mUnitsLayer, 5);

	this->mUnitsLayer->addChild(this->mHero->mShadow->create(), 4);
	this->mUnitsLayer->addChild(this->mHero->mShockwave, 4);
	this->mUnitsLayer->addChild(this->mHero, 5);

	this->mStaticLayer->addChild(this->mPrepareToBattle, 2);
	this->mStaticLayer->addChild(this->mLevelName, 2);
	this->mStaticLayer->addChild(this->mWealthText, 2);
	this->mStaticLayer->addChild(this->mLowHealthText, 2);
	this->mStaticLayer->addChild(this->mLevelStartText, 2);
	this->mStaticLayer->addChild(this->mPauseButton, 2);
    this->mStaticLayer->addChild(this->mDiamondCounterText, 2);

	this->mPrepareToBattle->setOpacity(0.0f);
	this->mLevelName->setOpacity(0.0f);

	this->mSlices = new EntityManager(5, new Slice(), this->mUnitsLayer, 7);

	this->mLeftJoystick = new Joystick();
	this->mRightJoystick = new Joystick();

	this->mStaticLayer->addChild(this->mLeftJoystick);
	this->mStaticLayer->addChild(this->mRightJoystick);

	this->mSpidersRestoreTime = 10.0f;
	this->mSpidersRestoreTimeElasped = 0;

	this->mMaxSpidersCount = 0;

	this->mUpgradeLevelStartText = false;
}

// ===========================================================
// Methods
// ===========================================================

void Level::startLevel()
{
	this->mIsGameStarted = true;

	this->mIsLevelLabelShows = true;
	this->mIsShouldStartLevel = false;

	this->mEnemies1->clear();
	this->mEnemies2->clear();
	this->mEnemies3->clear();
	this->mEnemies4->clear();
	this->mEnemies5->clear();

	char level_number_text[256];

	this->mEnemiesWave = new EnemyWave(this);

	switch(++this->mCurrentLevel)
	{
		case 1:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 1, "");
			this->mLevelName->setString(level_number_text);
            
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 0, 0)->addEnemy(5, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 4, 0));

			ENTITIES = 6;
		break;
		case 2:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 2, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(5, 0, 0)->addEnemy(5, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(5, 0, 0)->addEnemy(5, 0, 0));

			ENTITIES = 20;
		break;
		case 3:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 3, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(8, 0, 0)->addEnemy(8, 0, 0));

			ENTITIES = 26;
		break;
		case 4:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 4, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(5, 1, 0));

			ENTITIES = 5;
		break;
		case 5:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 5, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 1, 0)->addEnemy(5, 1, 0));

			ENTITIES = 20;
		break;
		case 6:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 6, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 0));

			ENTITIES = 8;
		break;
		case 7:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 7, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 1, 0)->addEnemy(8, 2, 0)->addEnemy(8, 2, 0));

			ENTITIES = 29;
		break;
		case 8:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 8, LARGE_INVASION_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0)->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 5))->addEnemy(8, 1, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(8, 2, 0)->addEnemy(8, 2, 0));

			ENTITIES = 44;
		break;
		case 9:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 9, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 0, 1));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 2, 1)->addEnemy(5, 2, 1)->addEnemy(5, 1, 1)->addEnemy(5, 0, 1)->addEnemy(3, 2, 1)->addEnemy(7, 2, 1)->addEnemy(20, 0, 1));

			ENTITIES = 70;
		break;
		case 10:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 10, BEWARE_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0));

			ENTITIES = 6;
		break;
		case 11:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 11, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 1, 1));

			ENTITIES = 20;
		break;
		case 12:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 12, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(2, 3, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(3, 1, 0)->addEnemy(3, 1, 0)->addEnemy(3, 1, 0));

			ENTITIES = 11;
		break;
		case 13:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 13, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 0, 1));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 2, 2)->addEnemy(5, 2, 2)->addEnemy(5, 1, 2)->addEnemy(5, 0, 2)->addEnemy(3, 2, 2)->addEnemy(7, 2, 2)->addEnemy(20, 0, 1));

			ENTITIES = 70;
		break;
		case 14:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 14, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(12, 2, 1)->addEnemy(12, 2, 1));

			ENTITIES = 24;
		break;
		case 15:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 15, PATIENCE_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 2));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 25))->addEnemy(2, 3, 1)->addEnemy(2, 3, 1)->addEnemy(2, 3, 1));

			ENTITIES = 16;
		break;
		case 16:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 16, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 1, 2)->addEnemy(10, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(15, 2, 1)->addEnemy(10, 1, 2));

			ENTITIES = 45;
		break;
		case 17:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 17, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 0, 2)->addEnemy(10, 0, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(5, 1, 3));

			ENTITIES = 26;
		break;
		case 18:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 18, THE_ELITE_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 3));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 3))->addEnemy(1, 0, 3)->addEnemy(1, 1, 3)->addEnemy(1, 2, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 3, 3)->addEnemy(1, 0, 3)->addEnemy(1, 0, 3)
				->addEnemy(1, 2, 3)->addEnemy(1, 2, 3)->addEnemy(1, 2, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 1, 3));

			ENTITIES = 36;
		break;
		case 19:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 19, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(4, 0, 2)->addEnemy(4, 1, 2)->addEnemy(4, 2, 2)->addEnemy(4, 3, 1));

			ENTITIES = 16;
		break;
		case 20:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 20, NUKES_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(30, 1, 2));

			ENTITIES = 30;
		break;
		case 21:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 21, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(8, 2, 2)->addEnemy(8, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(3, 3, 3));

			ENTITIES = 27;
		break;
		case 22:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 22, THE_HORDE_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(30, 0, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 30))->addEnemy(10, 1, 3));

			ENTITIES = 40;
		break;
		case 23:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 23, "");
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(15, 1, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 0, 2)->addEnemy(20, 2, 2)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3));

			ENTITIES = 75;
		break;
		case 24:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 24, DEATH_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(2, 3, 2)->addEnemy(2, 3, 2)->addEnemy(2, 3, 2)->addEnemy(2, 3, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(30, 1, 3));

			ENTITIES = 38;
		break;
		case 25:
			sprintf(level_number_text, LEVEL_NUMBER_TEXT, 25, ALTERLIFE_TEXT);
			this->mLevelName->setString(level_number_text);

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 3));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 0, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 3, 3));

			ENTITIES = 120;
		break;
		case 26:
			AppDelegate::screens->set(3.0f, 1, 2);

			ENTITIES = 100;

			return;
		break;
	}

	this->addChild(this->mEnemiesWave);

	this->mLevelName->runAction(CCFadeTo::create(3.0f, 255.0f));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_START_LEVEL);

	this->mLevelStartText->runAction(CCFadeTo::create(1.0f, 0.0f));

	this->mUpgradeLevelStartText = false;
}

void Level::finishLevel()
{
	this->mIsLevelLabelShows = true;
	this->mIsShouldStartLevel = true;

	this->removeChild(this->mEnemiesWave);
	this->mEnemiesWave->release();
	
	this->mLevelName->setString(LEVEL_CLEARED_TEXT);

	this->mLevelName->runAction(CCFadeTo::create(3.0f, 255.0f));
}

void Level::generatePizzaDecorations()
{
	CCSpriteBatchNode* spriteBatch = CCSpriteBatchNode::create("decorations.png", 75);

	float cx = this->mBackground->getWidth() / 2;
	float cy = this->mBackground->getHeight() / 2;

	float radius = this->mBackground->getWidth() * 0.40f;

	Entity* decorationsSource = new Entity("decorations.png", 2, 2);

	CCArray* decorations = CCArray::create();

	for (int i = 0; i < 75; i++) {
		float angle, dist, x, y;
		bool ok;

		ok = true;

		do {
			angle = Utils::randomf(0.0f, 1.0f) * Utils::Pi * 2.0f;
			dist = (0.3f + Utils::randomf(0.0f, 1.0f) * 0.7f) * radius * 0.95f;
			x = cx + cos(angle) * dist;
			y = cy - sin(angle) * dist * 0.5f;

			int collides = 0;

			for (int i = 0; i < decorations->count(); i++) {
				if (((Entity*) decorations->objectAtIndex(i))->circlesCollideWithCoordinates(x, y, 10.0f)) {
					collides++;

					break;
				}
			}

			if(collides == 0) ok = false;

		} while (ok);

		Entity* decoration = decorationsSource->deepCopy();
		decoration->setCurrentFrameIndex(Utils::random(0, 4));
		decoration->create()->setCenterPosition(x, y);

		decorations->addObject(decoration);

		spriteBatch->addChild(decoration);
	}

	decorations->release();

	this->mBackground->addChild(spriteBatch);
}

 CCPoint Level::getSafePizzaPosition() {
	float angle, dist, x, z;

	float cx = this->mBackground->getCenterX();
	float cy = this->mBackground->getCenterY();

	float radius = this->mBackground->getWidth() * 0.40f;

	angle = Utils::randomf(0.0f, 1.0f) * Utils::Pi * 2.0f;
	dist = (0.3f + Utils::randomf(0.0f, 1.0f) * .7f) * radius * 0.95f;

	x = cx + cos(angle) * dist;
	z = cy + sin(angle) * dist * 0.5f;

	return ccp(x, z);
}

void Level::checkCollisions(float pDeltaTime)
{
	int enemiesNearCastleCount = 0;
	bool castleCanFire = this->mCastle->isCanFire();

	for(int j = 0; j < this->mBaseBubbles->getCount(); j++)
	{
		Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(j);

		Utils::obstacle(this->mHero, bubble, 17, 50);

		for(int j = 0; j < this->mEnemies1->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(j);

			Utils::obstacle(enemy, bubble, 17, 50);
		}

		for(int j = 0; j < this->mEnemies2->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(j);

			Utils::obstacle(enemy, bubble, 17, 50);
		}

		for(int j = 0; j < this->mEnemies3->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(j);

			Utils::obstacle(enemy, bubble, 17, 50);
		}
        
		for(int j = 0; j < this->mEnemies4->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(j);
            
			Utils::obstacle(enemy, bubble, 17, 50);
		}
        
		for(int j = 0; j < this->mEnemies5->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(j);
            
			Utils::obstacle(enemy, bubble, 17, 50);
		}
	}

	for(int i = 0; i < this->mBaseBullets->getCount(); i++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mBaseBullets->objectAtIndex(i);

		for(int j = 0; j < this->mBaseBubbles->getCount(); j++)
		{
			Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(j);

			if(bullet->collideWith(bubble))
			{
				bubble->removeHealth(bullet->getPower());

				bullet->onCollide();
				
				if(bubble->onCollide())
				{
					this->mPickups->create()->setCenterPosition(bubble->getCenterX(), bubble->getCenterY());
				}
			}
		}

		for(int j = 0; j < this->mEnemies1->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int j = 0; j < this->mEnemies2->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int j = 0; j < this->mEnemies3->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}
        
		for(int j = 0; j < this->mEnemies4->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(j);
            
			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}
                    
					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
					this->shake(0.5f, 4.0f);
                    
					ENTITIES--;
				}
			}
		}
        
		for(int j = 0; j < this->mEnemies5->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(j);
            
			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}
                    
					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
					this->shake(0.5f, 4.0f);
                    
					ENTITIES--;
				}
			}
		}
	}
    
	for(int i = 0; i < this->mPickups->getCount(); i++)
	{
		Pickup* pickup = (Pickup*) this->mPickups->objectAtIndex(i);
        
		if(pickup->mIsMustDestroy) continue;
        
		if(this->mHero->collideWith(pickup, Utils::coord(4.0f)))
		{
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY(), pDeltaTime);
            
			if(this->mHero->collideWith(pickup))
			{
				pickup->onCollide();
                
				this->mWealth->add(pickup->getCurrentFrameIndex());
			}
		}
	}
    
	for(int i = 0; i < this->mDiamonds->getCount(); i++)
	{
		Diamond* pickup = (Diamond*) this->mDiamonds->objectAtIndex(i);
        
		if(pickup->mIsMustDestroy) continue;
        
		if(this->mHero->collideWith(pickup, Utils::coord(4.0f)))
		{
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY(), pDeltaTime);
            
			if(this->mHero->collideWith(pickup))
			{
				pickup->onCollide();
                
                char text[256];
                sprintf(text, "x %d", CCUserDefault::sharedUserDefault()->getIntegerForKey("diamonds") + 1);
                this->mDiamondCounterText->setString(text);
                
                CCUserDefault::sharedUserDefault()->setIntegerForKey("diamonds", CCUserDefault::sharedUserDefault()->getIntegerForKey("diamonds") + 1);
			}
		}
	}

	for(int i = 0; i < this->mEnemies1->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

		if(enemy->collideWith(this->mHero))
		{
			this->mHero->onCollide(enemy);
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();
			
			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

			this->shake(0.5f, 4.0f);

			ENTITIES--;
		}

		for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);

					this->mSpidersExplosions->create()->setCenterPosition(spider->getCenterX(), spider->getCenterY());

					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_BIG_EXPLOSION);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}
	}

	for(int i = 0; i < this->mEnemies2->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

		if(enemy->collideWith(this->mHero))
		{
			this->mHero->onCollide(enemy);
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_BASE_DAMAGE);

			this->mHeroExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY() + Utils::coord(50));

			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->shake(0.5f, 5.0f);

			ENTITIES--;
		}

		for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}
	}

	for(int i = 0; i < this->mEnemies3->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

		if(enemy->collideWith(this->mHero))
		{
			this->mHero->onCollide(enemy);
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();

			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

			this->shake(0.5f, 4.0f);

			ENTITIES--;
		}

		for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}
	}
    
	for(int i = 0; i < this->mEnemies4->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(i);
        
		if(enemy->collideWith(this->mHero))
		{
			this->mHero->onCollide(enemy);
		}
        
		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();
            
			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}
            
			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
            
			this->shake(0.5f, 4.0f);
            
			ENTITIES--;
		}
        
		for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);
            
			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);
                
				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}
        
		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}
	}
    
	for(int i = 0; i < this->mEnemies5->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(i);
        
		if(enemy->collideWith(this->mHero))
		{
			this->mHero->onCollide(enemy);
		}
        
		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();
            
			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}
            
			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
            
			this->shake(0.5f, 4.0f);
            
			ENTITIES--;
		}
        
		for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);
            
			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);
                
				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}
        
		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}
	}

	for(int i = 0; i < this->mEnemyBullets->getCount(); i++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mEnemyBullets->objectAtIndex(i);

		for(int j = 0; j < this->mBaseBubbles->getCount(); j++)
		{
			Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(j);

			if(bullet->collideWith(bubble))
			{
				bubble->removeHealth(bullet->getPower());

				bullet->onCollide();
				
				if(bubble->onCollide())
				{
					this->mPickups->create()->setCenterPosition(bubble->getCenterX(), bubble->getCenterY());
				}
			}
		}

		if(this->mHero->collideWith(bullet))
		{
			bullet->destroy();

			this->mHero->onCollide(bullet);
	
			this->mHero->mShootVectorX = bullet->mVectorX;
			this->mHero->mShootVectorY = bullet->mVectorY;

			this->mHero->mShootPadding = Utils::coord(3);

			if(this->mHero->getHealth() <= 0)
			{
				this->mHero->destroy();
				this->mHeroExplosions->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY() + Utils::coord(50));

				this->shake(2.5f, 6.0f);

				AppDelegate::screens->set(3.0f, 1, 1);
			}
		}
	}

	if(enemiesNearCastleCount >= 5)
	{
		this->mCastle->fire();
	}
	else
	{
		this->mCastle->unfire();
	}

	if(this->mCastle->mShockwave->isVisible())
	{
		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
		
		for(int i = 0; i < this->mEnemies4->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(i);
            
			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
		
		for(int i = 0; i < this->mEnemies5->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(i);
            
			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
	}

	if(castleCanFire)
	{
		this->mCastle->fire(this->getClosestEnemy(this->mCastle));
	}

	this->mHeroLaserTimeElapsed += pDeltaTime;

	if(this->mHeroLaserTimeElapsed >= this->mHeroLaserTime)
	{
		this->mHeroLaserTimeElapsed = 0;

		if(this->mHero->mShouldLaserFire)
		{
			BaseEnemy* enemy = this->getClosestEnemy(this->mHero);

			if(enemy != NULL)
			{
				this->mSpidersExplosions->create()->setCenterPosition(enemy->getCenterX() + Utils::coord(Utils::random(-10, 10)), enemy->getCenterY() + Utils::coord(Utils::random(-10, 10)));

				this->mLaserVectorX = enemy->getCenterX();
				this->mLaserVectorY = enemy->getCenterY();

				this->mHero->mLaserVectorX = enemy->getCenterX();
				this->mHero->mLaserVectorY = enemy->getCenterY();

				// TODO: Adjust laser power.
				enemy->removeHealth(10.0f);

				if(enemy->getHealth() <= 0 && enemy->isVisible())
				{
					enemy->death();

					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
			else
			{

			}
		}
	}

	for(int j = 0; j < this->mCastle->mBullets->getCount(); j++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mCastle->mBullets->objectAtIndex(j);

		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				bullet->destroy();
                
                if(enemy->onCollide(bullet))
                {
                    if(Utils::probably(30))
                    {
                        this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    }
                    
                    this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
                    this->shake(0.5f, 4.0f);
                    
                    ENTITIES--;
                }
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				bullet->destroy();
                
                if(enemy->onCollide(bullet))
                {
                    if(Utils::probably(30))
                    {
                        this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    }
                    
                    this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
                    this->shake(0.5f, 4.0f);
                    
                    ENTITIES--;
                }
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				bullet->destroy();
                
                if(enemy->onCollide(bullet))
                {
                    if(Utils::probably(30))
                    {
                        this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    }
                    
                    this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
                    this->shake(0.5f, 4.0f);
                    
                    ENTITIES--;
                }
			}
		}
		
		for(int i = 0; i < this->mEnemies4->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(i);
            
			if(enemy->collideWith(bullet))
			{
				bullet->destroy();
                
                if(enemy->onCollide(bullet))
                {
                    if(Utils::probably(30))
                    {
                        this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    }
                    
                    this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
                    this->shake(0.5f, 4.0f);
                    
                    ENTITIES--;
                }
			}
		}
		
		for(int i = 0; i < this->mEnemies5->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(i);
            
			if(enemy->collideWith(bullet))
			{
				bullet->destroy();
                
                if(enemy->onCollide(bullet))
                {
                    if(Utils::probably(30))
                    {
                        this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    }
                    
                    this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
                    this->shake(0.5f, 4.0f);
                    
                    ENTITIES--;
                }
			}
		}
	}

	if(this->mHero->mShockwave->isVisible())
	{
		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}
		
		for(int i = 0; i < this->mEnemies4->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(i);
            
			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}
                    
					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
					this->shake(0.5f, 4.0f);
                    
					ENTITIES--;
				}
			}
		}
		
		for(int i = 0; i < this->mEnemies5->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(i);
            
			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}
                    
					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
                    
					this->shake(0.5f, 4.0f);
                    
					ENTITIES--;
				}
			}
		}

		for(int i = 0; i < this->mBaseBubbles->getCount(); i++)
		{
			Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(i);

			if(bubble->collideWith(this->mHero->mShockwave))
			{
				bubble->removeHealth(this->mHero->mShockwaveDamage);

				if(bubble->onCollide())
				{
					this->mPickups->create()->setCenterPosition(bubble->getCenterX(), bubble->getCenterY());
				}
			}
		}
	}

	if(this->mCastle->getHealth() <= 0 && this->mCastle->isVisible())
	{
		this->mCastle->destroy();
		this->mHeroExplosions->create()->setCenterPosition(this->mCastle->getCenterX(), this->mCastle->getCenterY() + Utils::coord(50));

		this->shake(2.5f, 6.0f);

		AppDelegate::screens->set(3.0f, 1, 1);
	}
}

BaseEnemy* Level::getClosestEnemy(Entity* mObject)
{
	BaseEnemy* closest = NULL;
	float distance = 0;

	for(int i = 0; i < this->mEnemies1->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

		float d = Utils::distance(mObject->getCenterX(), mObject->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}

	for(int i = 0; i < this->mEnemies2->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

		float d = Utils::distance(mObject->getCenterX(), mObject->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}
		
	for(int i = 0; i < this->mEnemies3->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

		float d = Utils::distance(mObject->getCenterX(), mObject->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}
    
	for(int i = 0; i < this->mEnemies4->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies4->objectAtIndex(i);
        
		float d = Utils::distance(mObject->getCenterX(), mObject->getCenterY(), enemy->getCenterX(), enemy->getCenterY());
        
		if(closest == NULL || distance > d)
		{
			closest = enemy;
            
			distance = d;
		}
	}
    
	for(int i = 0; i < this->mEnemies5->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies5->objectAtIndex(i);
        
		float d = Utils::distance(mObject->getCenterX(), mObject->getCenterY(), enemy->getCenterX(), enemy->getCenterY());
        
		if(closest == NULL || distance > d)
		{
			closest = enemy;
            
			distance = d;
		}
	}

	return closest;
}

void Level::shake(float d, float i)
{
	this->mShaking = true;
	this->mShakeDuration = d;
	this->mShakeIntensity = i;

	this->mShakeDurationElapsed = 0;
}

void Level::updateShake(float pDeltaTime)
{
	if(this->mShaking)
	{
		this->mShakeDurationElapsed += pDeltaTime;

		if(this->mShakeDurationElapsed > this->mShakeDuration)
		{
			this->mShaking = false;
			this->mShakeDuration = 0;
		}
		else
		{
			int sentitX = 1;
			int sentitY = 1;
				
			if(Utils::randomf(0, 1) < 0.5) sentitX = -1;
			if(Utils::randomf(0, 1) < 0.5) sentitY = -1;

			this->mMainLayer->setPosition(this->mMainLayer->getPosition().x + Utils::randomf(0, 1) * this->mShakeIntensity * sentitX, this->mMainLayer->getPosition().y + Utils::randomf(0, 1) * this->mShakeIntensity * sentitY);
		}
	}
}

// ===========================================================
// Virtual Methods
// ===========================================================

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return false;

	if(Screen::ccTouchBegan(touch, event))
	{
		CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

		this->mPointerX = location.x;
		this->mPointerY = location.y;

		if(location.x < Options::CAMERA_CENTER_X)
		{
			this->mLeftJoystick->fade(true);
			this->mLeftJoystick->setCenterPosition(location.x, location.y);

			// Fly
			if(true) // TODO: this->mHero->isCanFly()
			{
				if(Utils::MILLISECONDS - this->mLastTimeTapLeft < 1.5f)
				{
					if(this->mHero->getZ() > Options::MIN_Z)
					{
						if(this->mHero->startFlyDamage())
						{
							this->shake(0.8f, 4.0f);

							this->mLastTimeTapLeft = 0;

							return true;
						}
					}
					else
					{
						this->mHero->startFly();

						this->mLastTimeTapLeft = 0;

						return true;
					}
				}
				else
				{
					this->mLastTimeTapLeft = Utils::MILLISECONDS;
				}
			}
		}
		else
		{
			this->mRightJoystick->fade(true);
			this->mRightJoystick->setCenterPosition(location.x, location.y);

			// Laser
			if(ENTITIES > 0)
			{
				if(Utils::MILLISECONDS - this->mLastTimeTapRight < 1.5f)
				{
					this->mHero->laser();

					this->mLastTimeTapRight = 0;
				}

				this->mLastTimeTapRight = Utils::MILLISECONDS;
			}

			this->mHero->mIsShouldFire = true;
		}

		return true;
	}

	return false;
}

void Level::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return;
	
	CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

	if(location.x < Options::CAMERA_CENTER_X)
	{
		this->mLeftJoystick->fade(false);

		this->mHero->endFly();
	}
	else
	{
		this->mRightJoystick->fade(false);

		this->mHero->mIsShouldFire = false;
	}
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return;

	CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

	if(this->mLeftJoystick->getOpacity() > 0 && location.x < Options::CAMERA_CENTER_X) this->mLeftJoystick->update(location);
	if(this->mRightJoystick->getOpacity() > 0 && location.x > Options::CAMERA_CENTER_X) this->mRightJoystick->update(location);

	this->mPointerX = this->mLeftJoystick->getVector().x;
	this->mPointerY = this->mLeftJoystick->getVector().y;

	float x = this->mPointerX;
	float y = this->mPointerY;

	this->mHeroFollowCoordinateX = x;
	this->mHeroFollowCoordinateY = y;

	if(this->mHero->mIsShouldFire)
	{
		x = -this->mRightJoystick->getVector().x;
		y = -this->mRightJoystick->getVector().y;

		if(this->mRightJoystick->mFullPower) // TODO: Temp solution. I must just normalize (x, y).
		{
			this->mHero->setFireCoordinates(x, y);
		}
	}
}

void Level::update(float pDeltaTime)
{
	if(this->mPause) return;

	CCScene::update(pDeltaTime);

	Utils::MILLISECONDS += pDeltaTime;

	float potencialX = -this->mHero->getCenterX() + Options::CAMERA_CENTER_X;
	float potencialY = -this->mHero->getCenterY() + Options::CAMERA_CENTER_Y + this->mHero->getZ();

	if(potencialY < Utils::coord(300) && potencialY > -Utils::coord(300))
	this->mMainLayer->setPosition(this->mMainLayer->getPosition().x, potencialY);

	if(potencialX < Utils::coord(500) && potencialX > -Utils::coord(500))
	this->mMainLayer->setPosition(potencialX, this->mMainLayer->getPosition().y);

	if(this->mLeftJoystick->getOpacity() > 0)
	{
		this->mHero->setFollowCoordinates(this->mHeroFollowCoordinateX, this->mHeroFollowCoordinateY);
	}

	// Pizza parts

	this->mPizzaPartTimeElapsed += pDeltaTime;

	if(this->mPizzaPartTimeElapsed >= this->mPizzaPartTime)
	{
		this->mPizzaPartTimeElapsed = 0;

		if(Utils::probably(50))
		{
			((Slice*) this->mSlices->create())->setFollowCoordinates(this->mHero->getCenterX(), this->mHero->getCenterY());

			if(Utils::probably(30) && this->mSlices->getCount() < 3)
			{
				this->mPizzaPartTimeElapsed = this->mPizzaPartTime;
			}
		}
	}

	// Bubbles

	if(this->mBaseBubbles->getCount() < 2)
	{
		this->mBubbleAppearTimeElapsed += pDeltaTime;

		if(this->mBubbleAppearTimeElapsed >= this->mBubbleAppearTime)
		{
			this->mBubbleAppearTimeElapsed = 0;
			this->mBubbleAppearTime = 5.0f + Utils::randomf(0.0f, 10.0f);

			CCPoint location = this->getSafePizzaPosition();

			this->mBaseBubbles->create()->setCenterPosition(location.x, location.y);
		}
	}

	// Labels

	this->mLowHealthTimeElapsed += pDeltaTime;

	if(this->mLowHealthTimeElapsed >= this->mLowHealthTime)
	{
		this->mLowHealthTimeElapsed = 0;

		if(this->mHero->getHealth() <= this->mHero->getMaxHealth() / 3 && this->mLowHealthText->getOpacity() <= 0.0f && this->mPrepareToBattle->getOpacity() <= 0.0f && this->mLevelStartText->getOpacity() <= 0.0f)
		{
			if(this->mLowHealthText->getOpacity() <= 0.0f)
			{
				this->mLowHealthText->runAction(CCFadeTo::create(1.0f, 255.0f));
			}
		}
		else
		{
			if(this->mLowHealthText->getOpacity() >= 0.0f)
			{
				this->mLowHealthText->runAction(CCFadeTo::create(1.0f, 0.0f));
			}
		}
	}

	if(this->mUpgradeLevelStartText)
	{
		this->mUpgradeLevelStartTimeElapsed += pDeltaTime;

		if(this->mUpgradeLevelStartTimeElapsed >= this->mUpgradeLevelStartTime)
		{
			this->mUpgradeLevelStartTimeElapsed -= this->mUpgradeLevelStartTime;

            if(this->mCurrentLevel < 25)
            {
                char text[512];
                sprintf(text, LEVEL_BEGIN_TEXT, this->mCurrentLevel + 1, this->mTextSeconds);
                this->mLevelStartText->setString(text);
            }

			this->mTextSeconds--;
		}
	}

	// HERO DEATH

	if(this->mHero->getHealth() <= 0 && this->mHero->isVisible())
	{
		this->mHero->destroy();
		this->mHeroExplosions->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY() + Utils::coord(50));

		this->shake(2.5f, 6.0f);

		AppDelegate::screens->set(3.0f, 1, 1);
	}

	if(this->mStartBattleShows)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime)
		{
			this->mStartBattleShows = false;

			this->mStartBattleTimeElapsed = 0;

			this->mPrepareToBattle->runAction(CCFadeTo::create(3.0f, 255.0f));
		}
	}
	else if(!this->mIsGameStarted)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime && this->mTextSeconds <= 0)
		{
			this->mStartBattleTimeElapsed = 0;

			if(this->mPrepareToBattle->getOpacity() <= 0.0f)
			{
				this->startLevel();
			}
			else
			{
				this->mPrepareToBattle->runAction(CCFadeTo::create(3.0f, 0.0f));
			}
		}
	}

	if(this->mShouldShowSeconds)
	{
		this->mShowLevelTextPauseTimeElapsed += pDeltaTime;

		if(this->mShowLevelTextPauseTimeElapsed >= this->mShowLevelTextPauseTime)
		{
			this->mShowLevelTextPauseTimeElapsed = 0;

			this->mShouldShowSeconds = false;

			this->mUpgradeLevelStartText = true;
			this->mTextSeconds = 5;
			
			this->mLevelStartText->runAction(CCFadeTo::create(1.0f, 255.0f));

			char text[512];
			
			if(this->mCurrentLevel < 25)
			{
				sprintf(text, LEVEL_BEGIN_TEXT, this->mCurrentLevel + 1, this->mTextSeconds);
			}
			else
			{
				sprintf(text, WIN_TEXT);
			}
			
			this->mLevelStartText->setString(text);
		}
	}

	if(this->mIsLevelLabelShows)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime)
		{
			this->mStartBattleTimeElapsed = 0;

			this->mIsLevelLabelShows = false;

			this->mLevelName->runAction(CCFadeTo::create(1.0f, 0.0f));
		}
	}

	if(this->mIsGameStarted)
	{
		this->mTestLevelTimeElapsed += pDeltaTime;

		if(this->mTestLevelTimeElapsed >= this->mTestLevelTime && this->mTextSeconds <= 0)
		{
			if(this->mIsShouldStartLevel)
			{
				this->mTestLevelTimeElapsed = 0;

				this->startLevel();
			}
			else
			{
				if(ENTITIES <= 0)
				{
					this->mTestLevelTimeElapsed = 0;

					this->finishLevel();

					if(this->mCurrentLevel > 0)
					{
						this->mShouldShowSeconds = true;
					}
				}
			}
		}
	}

	// Collisions

	this->checkCollisions(pDeltaTime);

	this->mUnitsLayer->update(pDeltaTime); // What for? O_o

	this->mEnemiesGroup->update(pDeltaTime); // What for? O_o

	this->updateShake(pDeltaTime);

	if(this->mWealth->getCount() <= 0)
	{
		this->mWealthText->setVisible(false);
	}
	else
	{
		this->mWealthText->setVisible(true);
	}

	// Spiders

	if(this->mSpiders->getCount() < this->mMaxSpidersCount)
	{
		this->mSpidersRestoreTimeElasped += pDeltaTime;

		if(this->mSpidersRestoreTimeElasped >= this->mSpidersRestoreTime)
		{
			this->mSpidersRestoreTimeElasped -= this->mSpidersRestoreTime;

			this->mSpiders->create();
		}
	}

	if(this->mHero->mShouldLaserFire)
	{
		if(this->mLaserVectorX != 0 && this->mLaserVectorY != 0)
		{
			this->renderLaserBeam(0, this->mHero->getCenterX(), this->mHero->getCenterY() + this->mHero->getZ(), this->mLaserVectorX, this->mLaserVectorY);
		}
	}
	else
	{
		this->mLaser1->destroy();
		this->mLaser2->destroy();

		this->mLaserVectorX = 0;
		this->mLaserVectorY = 0;
	}

	if(ENTITIES <= 0)
	{
		this->mHero->mShouldLaserFire = false;
	}
}

void Level::onEnter()
{
	Screen::onEnter();

	this->mPauseButton->setRegisterAsTouchable(true); // Sorry for that but it's bugs of Cocos2d-x :(

	// RESTART

	COINS[0] = 0;
	COINS[1] = 0;
	COINS[2] = 0;

	this->mStartBattleShows = true;
	this->mIsShouldStartLevel = true;
	this->mIsLevelLabelShows = false;
	this->mIsGameStarted = false;
	this->mShouldShowSeconds = false;
	this->mPause = false;

	this->mBubbleAppearTimeElapsed = 0;
	this->mStartBattleTimeElapsed = 0;
	this->mTestLevelTimeElapsed = 0;
	this->mPizzaPartTimeElapsed = 0;
	this->mLowHealthTimeElapsed = 0;
	this->mUpgradeLevelStartTimeElapsed = 0;
	this->mShowLevelTextPauseTimeElapsed = 0;

	this->mCurrentLevel = 0;

	this->mTextSeconds = 0;

	this->mHero->reset();
	this->mCastle->reset();

	this->mEnemies1->clear();
	this->mEnemies2->clear();
	this->mEnemies3->clear();
	this->mEnemies4->clear();
	this->mEnemies5->clear();
    
    this->mDiamonds->clear();

	this->mBaseBubbles->clear();

	this->mBaseBullets->clear();
	this->mEnemyBullets->clear();

	this->mEnemiesExplosions->clear();
	this->mHeroExplosions->clear();

	this->mPickups->clear();
	this->mWealth->clear();

	this->mSpiders->clear();
	this->mMaxSpidersCount = 0;

	this->mPrepareToBattle->stopAllActions();
	this->mLowHealthText->stopAllActions();
	this->mLevelStartText->stopAllActions();
	this->mLevelName->stopAllActions();

	this->mPrepareToBattle->setOpacity(0);
	this->mLowHealthText->setOpacity(0);
	this->mLevelStartText->setOpacity(0);
	this->mLevelName->setOpacity(0);

	this->mUpgradeLayer->reset();

	this->mHero->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200));

	this->mLeftJoystick->setOpacity(0);
	this->mRightJoystick->setOpacity(0);
}

void Level::onExit()
{
	Screen::onExit();
}

// UPDATES

void Level::updateSpiders()
{
	this->mMaxSpidersCount += 6;
}

void Level::draw()
{
	Screen::draw();

	// Draw laser
}

void Level::renderLaserBeam(float angle, float sx, float sy, float ex, float ey)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_BEAM);

	sy -= 10;
	//sx -= 10;

	this->mLaser1->create();
	this->mLaser1->setAnchorPoint(ccp(0, 0));

	this->mLaser1->setScaleX((ccpDistance(ccp(this->mHero->getX(), this->mHero->getY()), ccp(ex, ey))) / 13);

	//Update laser
	this->mLaser1->setPositionX(sx);
	this->mLaser1->setPositionY(sy);

	//Calculate rotation
	float angleRadians = atan2((ey - sy) , (ex - sx));
	
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees;

	this->mLaser1->setRotation(cocosAngle);

	// 2
	sy += 20;
	//sx += 20;

	this->mLaser2->create();
	this->mLaser2->setAnchorPoint(ccp(0, 0));

	this->mLaser2->setScaleX((ccpDistance(ccp(this->mHero->getX(), this->mHero->getY()), ccp(ex, ey))) / 13);

	//Update laser
	this->mLaser2->setPositionX(sx);
	this->mLaser2->setPositionY(sy);

	//Calculate rotation
	angleRadians = atan2((ey - sy) , (ex - sx));
	
	angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	cocosAngle = -1 * angleDegrees;

	this->mLaser2->setRotation(cocosAngle);
}

#endif