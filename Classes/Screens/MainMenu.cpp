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