#ifndef CONST_APPDELEGATE
#define CONST_APPDELEGATE

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

<<<<<<< HEAD
=======
bool AppDelegate::MULTIPLAYER = false;

>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
ScreenManager* AppDelegate::screens = NULL;

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

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* director 	= CCDirector::sharedDirector();
	CCEGLView*  EGLView 	= CCEGLView::sharedOpenGLView();
	CCSize 	screenSize 		= EGLView->getFrameSize();
<<<<<<< HEAD

=======
    
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	director->setOpenGLView(EGLView);
	director->setContentScaleFactor(designResolutionSize.height / screenSize.height);

	vector <string> searchPath;
<<<<<<< HEAD

=======
    
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	searchPath.push_back(resources800x600.directory);

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	Options::SCREEN_WIDTH  = designResolutionSize.width;
	Options::SCREEN_HEIGHT = designResolutionSize.height;

	Options::SCREEN_CENTER_X = designResolutionSize.width / 2;
	Options::SCREEN_CENTER_Y = designResolutionSize.height / 2;

	Options::CAMERA_WIDTH  = screenSize.width;
	Options::CAMERA_HEIGHT = screenSize.height;

	Options::CAMERA_CENTER_X  = screenSize.width / 2;
	Options::CAMERA_CENTER_Y = screenSize.height / 2;

	director->setAlphaBlending(false);
	director->setDepthTest(false);
<<<<<<< HEAD
	director->setDisplayStats(false);
=======
	director->setDisplayStats(true);
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

	director->setProjection(kCCDirectorProjection2D);

	director->setAnimationInterval(1.0f / 60.0f);

	AppDelegate::screens = new ScreenManager();

	Screen* pScene = new SplashScreen();

	director->runWithScene(pScene);   

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
<<<<<<< HEAD
=======
    CCDirector::sharedDirector()->stopAnimation();
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
	CCDirector::sharedDirector()->pause();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

<<<<<<< HEAD
	((Level*) AppDelegate::screens->mScreens[0])->mPauseButton->onTouch(NULL, NULL); // TODO: Make sure that level scene is currently running.
=======
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	if(screens->mCurrentScreenIndex == 0)
	{
        if(!((Level*) AppDelegate::screens->mScreens[0])->mPause)
        {
            ((Level*) AppDelegate::screens->mScreens[0])->mPauseButton->onTouch(NULL, NULL);
        }
	}

	#endif
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}

void AppDelegate::applicationWillEnterForeground()
{
<<<<<<< HEAD
	CCDirector::sharedDirector()->resume();
=======
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

#endif