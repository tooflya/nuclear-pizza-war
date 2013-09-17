#ifndef CONST_MAINMENU_H
#define CONST_MAINMENU_H

#include "cocos2d.h"

#include "AppDelegate.h"

#include "Screen.h"

using namespace cocos2d;

class MainMenu : public Screen
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

<<<<<<< HEAD
=======
		static MainMenu* mObj;

		static const char* MULTIPLAYER_CONNECTION_TEXT0;
		static const char* MULTIPLAYER_CONNECTION_TEXT1;
		static const char* MULTIPLAYER_CONNECTION_TEXT2;
		static const char* MULTIPLAYER_CONNECTION_TEXT3;

>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
		// ===========================================================
		// Fields
		// ===========================================================

<<<<<<< HEAD
=======
		int mWaitingForConnectionsTicks;

		float mWaitingForConnectionsTimeElapsed;
		float mWaitingForConnectionsTotalTimeElapsed;

		bool mWaitingForConnections;

>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
		Entity* mBackground;
		Entity* mPlayButton;

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

		// ===========================================================
		// Fields
		// ===========================================================
<<<<<<< HEAD
=======
		
		Entity* mPlayBattleButton;
		Entity* mAchievementsButton;
		Entity* mLeaderBoardButton;

		CCLabelTTF* mWaitForBattleCapture;
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b

		// ===========================================================
		// Constructors
		// ===========================================================

		MainMenu();

		// ===========================================================
		// Methods
		// ===========================================================
<<<<<<< HEAD
=======

		static void nativeOnGooglePlusSignInSucceeded();
		static void nativeOnGooglePlusConnedctedToRoom();

		void startWaitingForBattle();
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		virtual void onEnter();
<<<<<<< HEAD
};

=======
		virtual void onEnterTransitionDidFinish();

		virtual void update(float pDeltaTime);
};

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <jni.h>

#endif

extern "C"
{
    extern void onMainMenuStarted();
}

>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
#endif