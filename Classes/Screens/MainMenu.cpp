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

// ===========================================================
// Constants
// ===========================================================

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
	ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
    	case kLanguageRussian:
    		str = "button_start_ru.png";
    	break;
    	default:
    		str = "button_start.png";
    	break;
    }

	this->mBackground = new Entity("splash.png");
	this->mPlayButton = new PlayButton(str);

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlayButton->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150));

	this->addChild(this->mBackground);
	this->addChild(this->mPlayButton);

 	// Versions

	CCLabelTTF* mVersionLabel1 = CCLabelTTF::create("Nuclear Pizza War", "Arial",  Utils::coord(16));
	CCLabelTTF* mVersionLabel2 = CCLabelTTF::create("Mojang Inc., Tooflya Inc. - 2013", "Arial",  Utils::coord(16));
	CCLabelTTF* mVersionLabel3 = CCLabelTTF::create("Current version: 1.1.0 (Alpha)", "Arial",  Utils::coord(16));

	mVersionLabel1->setPosition(ccp(Utils::coord(10) + mVersionLabel1->getContentSize().width / 2, Utils::coord(55)));
	mVersionLabel2->setPosition(ccp(Utils::coord(10) + mVersionLabel2->getContentSize().width / 2, Utils::coord(35)));
	mVersionLabel3->setPosition(ccp(Utils::coord(10) + mVersionLabel3->getContentSize().width / 2, Utils::coord(15)));

	this->addChild(mVersionLabel1);
	this->addChild(mVersionLabel2);
	this->addChild(mVersionLabel3);
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void MainMenu::onEnter()
{
	Screen::onEnter();
	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Options::SOUND_MAIN_MUSIC, true);
}

#endif