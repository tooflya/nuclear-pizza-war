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

		static MainMenu* mObj;

		static const char* MULTIPLAYER_CONNECTION_TEXT0;
		static const char* MULTIPLAYER_CONNECTION_TEXT1;
		static const char* MULTIPLAYER_CONNECTION_TEXT2;
		static const char* MULTIPLAYER_CONNECTION_TEXT3;

		// ===========================================================
		// Fields
		// ===========================================================

		int mWaitingForConnectionsTicks;

		float mWaitingForConnectionsTimeElapsed;
		float mWaitingForConnectionsTotalTimeElapsed;

		bool mWaitingForConnections;

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
		
		Entity* mPlayBattleButton;
		Entity* mAchievementsButton;
		Entity* mLeaderBoardButton;

		CCLabelTTF* mWaitForBattleCapture;

		// ===========================================================
		// Constructors
		// ===========================================================

		MainMenu();

		// ===========================================================
		// Methods
		// ===========================================================

		static void nativeOnGooglePlusSignInSucceeded();
		static void nativeOnGooglePlusConnedctedToRoom();

		void startWaitingForBattle();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		virtual void onEnter();
		virtual void onEnterTransitionDidFinish();

		virtual void update(float pDeltaTime);
};

#include <jni.h>

extern "C"
{
    extern void onMainMenuStarted();
}

#endif