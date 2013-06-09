#ifndef CONST_MAINMENU
#define CONST_MAINMENU

#include "MainMenu.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PlayButton : public Entity
{
	public:
		PlayButton(const char* pszFileName) :
			Entity(pszFileName)
			{
				this->setRegisterAsTouchable(true);
			}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				AppDelegate::screens->set(1.0f, 0, 0);
			}
};

class PlayBattleButton : public Entity
{
    private:
        MainMenu* mParent;

    public:
        PlayBattleButton(const char* pszFileName, MainMenu* pParent) :
            Entity(pszFileName)
            {
                this->setOpacity(0.0f);

                this->mParent = pParent;
            }

            void onTouch(CCTouch* touch, CCEvent* event)
            {
                this->mParent->startWaitingForBattle();
            }

            void onCreate()
            {
                this->setRegisterAsTouchable(true);
                this->runAction(CCFadeIn::create(0.3f));
            }
};

class AchievementsButton : public Entity
{
    private:
        MainMenu* mParent;

    public:
        AchievementsButton(const char* pszFileName, MainMenu* pParent) :
            Entity(pszFileName)
            {
                this->setOpacity(0.0f);

                this->mParent = pParent;
            }

            void onTouch(CCTouch* touch, CCEvent* event)
            {
                openAchievementBoard();
            }

            void onCreate()
            {
                this->setRegisterAsTouchable(true);
                this->runAction(CCFadeIn::create(0.3f));
            }
};

class LeaderBoardButton : public Entity
{
    private:
        MainMenu* mParent;

    public:
        LeaderBoardButton(const char* pszFileName, MainMenu* pParent) :
            Entity(pszFileName)
            {
                this->setOpacity(0.0f);

                this->mParent = pParent;
            }

            void onTouch(CCTouch* touch, CCEvent* event)
            {
                openLeaderBoard();
            }

            void onCreate()
            {
                this->setRegisterAsTouchable(true);
                this->runAction(CCFadeIn::create(0.3f));
            }
};

// ===========================================================
// Constants
// ===========================================================

MainMenu* MainMenu::mObj = NULL;

const char* MainMenu::MULTIPLAYER_CONNECTION_TEXT0 = "Waiting for connections";
const char* MainMenu::MULTIPLAYER_CONNECTION_TEXT1 = "Waiting for connections.";
const char* MainMenu::MULTIPLAYER_CONNECTION_TEXT2 = "Waiting for connections..";
const char* MainMenu::MULTIPLAYER_CONNECTION_TEXT3 = "Waiting for connections...";

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

MainMenu::MainMenu()
{
	new BackgroundStarsManager(this);

	const char* str;
    const char* str2;
	ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
    	case kLanguageRussian:
    		str = "button_start_ru.png";
            str2 = "button_battle_start_ru.png";
            
            MainMenu::MULTIPLAYER_CONNECTION_TEXT0 = "Ожидание подключений";
            MainMenu::MULTIPLAYER_CONNECTION_TEXT1 = "Ожидание подключений.";
            MainMenu::MULTIPLAYER_CONNECTION_TEXT2 = "Ожидание подключений..";
            MainMenu::MULTIPLAYER_CONNECTION_TEXT3 = "Ожидание подключений...";
    	break;
    	default:
    		str = "button_start.png";
            str2 = "button_battle_start.png";
    	break;
    }

	this->mBackground = new Entity("splash.png");
	this->mPlayButton = new PlayButton(str);
    this->mPlayBattleButton = new PlayBattleButton(str2, this);
    this->mAchievementsButton = new AchievementsButton("achievements_icon.png", this);
    this->mLeaderBoardButton = new LeaderBoardButton("leaderboard_icon.png", this);

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlayButton->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150));
    this->mPlayBattleButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(220));
    this->mLeaderBoardButton->setCenterPosition(Utils::coord(48), Options::CAMERA_HEIGHT - Utils::coord(48));
    this->mAchievementsButton->setCenterPosition(Utils::coord(58) + this->mLeaderBoardButton->getWidth(), Options::CAMERA_HEIGHT - Utils::coord(48));

	this->addChild(this->mBackground);
	this->addChild(this->mPlayButton);
    this->addChild(this->mPlayBattleButton);
    this->addChild(this->mAchievementsButton);
    this->addChild(this->mLeaderBoardButton);

    this->mWaitForBattleCapture = CCLabelTTF::create(MainMenu::MULTIPLAYER_CONNECTION_TEXT1, Options::SPECIAL_FONT,  Utils::coord(36));
    this->mWaitForBattleCapture->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200)));
    this->mWaitForBattleCapture->setOpacity(0.0f);

    this->addChild(this->mWaitForBattleCapture);

 	// Versions

	CCLabelTTF* mVersionLabel1 = CCLabelTTF::create("Nuclear Pizza War", "Arial",  Utils::coord(16));
	CCLabelTTF* mVersionLabel2 = CCLabelTTF::create("Mojang Inc., Tooflya Inc. - 2013", "Arial",  Utils::coord(16));
	CCLabelTTF* mVersionLabel3 = CCLabelTTF::create("Current version: 1.1.1 (Alpha)", "Arial",  Utils::coord(16));

	mVersionLabel1->setPosition(ccp(Utils::coord(10) + mVersionLabel1->getContentSize().width / 2, Utils::coord(55)));
	mVersionLabel2->setPosition(ccp(Utils::coord(10) + mVersionLabel2->getContentSize().width / 2, Utils::coord(35)));
	mVersionLabel3->setPosition(ccp(Utils::coord(10) + mVersionLabel3->getContentSize().width / 2, Utils::coord(15)));

	this->addChild(mVersionLabel1);
	this->addChild(mVersionLabel2);
	this->addChild(mVersionLabel3);

    // Battles

    this->mWaitingForConnections = false;
    this->mWaitingForConnectionsTimeElapsed = 0;
    this->mWaitingForConnectionsTotalTimeElapsed = 0;
    this->mWaitingForConnectionsTicks = 1;

    MainMenu::mObj = this;
}

// ===========================================================
// Methods
// ===========================================================

void MainMenu::startWaitingForBattle()
{
    this->mPlayButton->runAction(CCFadeOut::create(0.3f));
    this->mPlayBattleButton->runAction(CCFadeOut::create(0.3f));

    this->mWaitForBattleCapture->runAction(CCFadeIn::create(0.3f));

    this->mWaitingForConnections = true;

    GooglePlusstartWaitingForBattle();
}

void MainMenu::nativeOnGooglePlusSignInSucceeded()
{
    MainMenu::mObj->mPlayBattleButton->create();
    MainMenu::mObj->mAchievementsButton->create();
    MainMenu::mObj->mLeaderBoardButton->create();
}

void MainMenu::nativeOnGooglePlusConnedctedToRoom()
{
    AppDelegate::MULTIPLAYER = true;

    ((Level*) AppDelegate::screens->mScreens[0])->configure();

    AppDelegate::screens->set(1.0f, 0, 0);
}

// ===========================================================
// Virtual Methods
// ===========================================================

void MainMenu::update(float pDeltaTime)
{
    Screen::update(pDeltaTime);
    
    if(this->mWaitingForConnections)
    {
        this->mWaitingForConnectionsTimeElapsed += pDeltaTime;
        this->mWaitingForConnectionsTotalTimeElapsed += pDeltaTime;

        if(this->mWaitingForConnectionsTimeElapsed >= 1.0f)
        {
            this->mWaitingForConnectionsTimeElapsed = 0;

            char text[256];

            {
                switch(this->mWaitingForConnectionsTicks)
                {
                    case 0:
                        sprintf(text, MainMenu::MULTIPLAYER_CONNECTION_TEXT0);
                    break;

                    case 1:
                        sprintf(text, MainMenu::MULTIPLAYER_CONNECTION_TEXT1);
                    break;

                    case 2:
                        sprintf(text, MainMenu::MULTIPLAYER_CONNECTION_TEXT2);
                    break;

                    case 3:
                        sprintf(text, MainMenu::MULTIPLAYER_CONNECTION_TEXT3);
                    break;
                }

                this->mWaitForBattleCapture->setString(text);
            }

            this->mWaitingForConnectionsTicks++;

            if(this->mWaitingForConnectionsTicks > 3) this->mWaitingForConnectionsTicks = 0;
        }

        if(this->mWaitingForConnectionsTotalTimeElapsed >= 30.0f)
        {
            this->mWaitingForConnectionsTotalTimeElapsed = 0;
            this->mWaitingForConnections = false;

            this->mPlayButton->runAction(CCFadeIn::create(0.3f));
            this->mPlayBattleButton->runAction(CCFadeIn::create(0.3f));

            this->mWaitForBattleCapture->runAction(CCFadeOut::create(0.3f));
        }
    }
}

void MainMenu::onEnter()
{
	Screen::onEnter();
	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Options::SOUND_MAIN_MUSIC, true);
}

void MainMenu::onEnterTransitionDidFinish()
{
    Screen::onEnterTransitionDidFinish();

    onMainMenuStarted();
}

#endif