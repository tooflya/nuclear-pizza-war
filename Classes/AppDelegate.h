#ifndef CONST_APPDELEGATE_H
#define CONST_APPDELEGATE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <vector>

#include "Options.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "SplashScreen.h"
#include "Level.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

class ScreenManager;

typedef struct tagResource {
	CCSize size;
	char directory[100];
} Resource;

static Resource resources800x600 	= { CCSizeMake(800, 600),  "Graphics/800x600" };
static CCSize   designResolutionSize  = CCSizeMake(800, 600);

class AppDelegate : private CCApplication
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

	public:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		static bool MULTIPLAYER;

		static ScreenManager* screens;

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

		bool applicationDidFinishLaunching();

		void applicationDidEnterBackground();
		void applicationWillEnterForeground();
};

#endif