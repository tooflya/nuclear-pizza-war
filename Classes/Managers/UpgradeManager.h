#ifndef CONST_UPGRADEMANAGER_H
#define CONST_UPGRADEMANAGER_H

#include "cocos2d.h"

#include "Level.h"

using namespace cocos2d;

class UpgradeButton;

class UpgradeManager : public CCLayer
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

		Level* mWorld;

		UpgradeButton* mDamageButton;
		UpgradeButton* mRateButton;
		UpgradeButton* mSpeedButton;
		UpgradeButton* mRegenerationButton;
		UpgradeButton* mHealthButton;
		UpgradeButton* mBeamButton;
		UpgradeButton* mShockWaveButton;
		UpgradeButton* mJetpackButton;
		UpgradeButton* mFortificationButton;
		UpgradeButton* mBlasterButton;
		UpgradeButton* mNovaButton;
		UpgradeButton* mSpidersButton;

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

		static const char* FIRE_DAMAGE_TEXT1;
		static const char* FIRE_DAMAGE_TEXT2;
		static const char* FIRE_DAMAGE_TEXT3;

    	static const char* FIRE_RATE_TEXT1;
    	static const char* FIRE_RATE_TEXT2;
    	static const char* FIRE_RATE_TEXT3;

    	static const char* SPEED_TEXT1;
    	static const char* SPEED_TEXT2;
    	static const char* SPEED_TEXT3;

    	static const char* REGENERATION_TEXT1;
    	static const char* REGENERATION_TEXT2;
    	static const char* REGENERATION_TEXT3;

    	static const char* HEALTH_TEXT1;
    	static const char* HEALTH_TEXT2;
    	static const char* HEALTH_TEXT3;

    	static const char* BEEM_TEXT1;
    	static const char* BEEM_TEXT2;
    	static const char* BEEM_TEXT3;

    	static const char* SHOCKWAVE_TEXT1;
    	static const char* SHOCKWAVE_TEXT2;
    	static const char* SHOCKWAVE_TEXT3;

    	static const char* JETPACK_TEXT1;
    	static const char* JETPACK_TEXT2;
    	static const char* JETPACK_TEXT3;

    	static const char* FORTIFICATION_TEXT1;
    	static const char* FORTIFICATION_TEXT2;
    	static const char* FORTIFICATION_TEXT3;

		static const char* TOWER_BLASTER_TEXT1;
		static const char* TOWER_BLASTER_TEXT2;
		static const char* TOWER_BLASTER_TEXT3;

		static const char* NOVA_DEFENCE_TEXT1;
		static const char* NOVA_DEFENCE_TEXT2;
		static const char* NOVA_DEFENCE_TEXT3;

		static const char* DEFENCE_SPIDERS_TEXT1;
		static const char* DEFENCE_SPIDERS_TEXT2;
		static const char* DEFENCE_SPIDERS_TEXT3;

		// ===========================================================
		// Fields
		// ===========================================================

		UpgradeManager(Level* pWorld);

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void check();

		void reset();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		void onEnter();

		void update(float pDeltaTime);

		void draw();
};

#endif