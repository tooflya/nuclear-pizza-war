#ifndef CONST_OPTIONS
#define CONST_OPTIONS

#include "Options.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

int Options::CENTER_X = 0;
int Options::CENTER_Y = 0;

int Options::SCREEN_WIDTH = 0;
int Options::SCREEN_HEIGHT = 0;

int Options::SCREEN_CENTER_X = 0;
int Options::SCREEN_CENTER_Y = 0;

int Options::CAMERA_WIDTH = 0;
int Options::CAMERA_HEIGHT = 0;

int Options::CAMERA_CENTER_X = 0;
int Options::CAMERA_CENTER_Y = 0;

int Options::FORTIFICATION_LEVEL = 2;
int Options::FORTIFICATION_HEALTH_LEVEL = 12;

float Options::MIN_Z = 1.0f;
float Options::MAX_Z = 160.0f;

bool Options::MUSIC_ENABLE = false;
bool Options::SOUND_ENABLE = false;

bool Options::UNPUCKING = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

const char* Options::SPECIAL_FONT = "Franchise";

#else

const char* Options::SPECIAL_FONT = "Fonts/Franchise.ttf";

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFROM == CC_PLATFORM_MAC)
const char* Options::SOUND_MAIN_MUSIC = "mus_fast02.wav";
const char* Options::SOUND_AI_DEATH = "ai_death.wav";
const char* Options::SOUND_AI_VOICE = "ai_voice.wav";
const char* Options::SOUND_ALIEN_SUICIDE = "alien_suicide.wav";
const char* Options::SOUND_ALIEN_WARNING = "alien_warning.wav";
const char* Options::SOUND_ALIEN_SHOT = "alienshot.wav";
const char* Options::SOUND_BASE_DAMAGE = "basedamage.wav";
const char* Options::SOUND_BASE_SHOT = "baseshot.wav";
const char* Options::SOUND_BEAM = "beam.wav";
const char* Options::SOUND_BIG_EXPLOSION = "big_explosion.wav";
const char* Options::SOUND_CHEESIE_LAND = "cheesy_land.wav";
const char* Options::SOUND_CHEESIE_LAND2 = "cheesy_land2.wav";
const char* Options::SOUND_COIN = "coin.wav";
const char* Options::SOUND_HEALTH = "health.wav";
const char* Options::SOUND_JETPACK_FAIL = "jetpack_fail.wav";
const char* Options::SOUND_PIZZAPLOP = "pizzaplop.wav";
const char* Options::SOUND_PLAYER_ACCELERATING = "player_accelerating.wav";
const char* Options::SOUND_PLAYER_DEATH = "player_death.wav";
const char* Options::SOUND_PLAYER_GETHIT = "player_gethit.wav";
const char* Options::SOUND_PLAYER_JETPACK = "player_jetpack.wav";
const char* Options::SOUND_POWERUP1 = "powerup_1.wav";
const char* Options::SOUND_POWERUP2 = "powerup_2.wav";
const char* Options::SOUND_SHOT_LAND = "shot_land.wav";
const char* Options::SOUND_SHOT = "shot.wav";
const char* Options::SOUND_SHOT2 = "shot2.wav";
const char* Options::SOUND_SLICE_APPROACHING = "slice_approaching.wav";
const char* Options::SOUND_SLICE_DOCKING = "slice_docking.wav";
const char* Options::SOUND_SPIDER_TALK = "spider_talk.wav";
const char* Options::SOUND_START_LEVEL = "start_level.wav";
const char* Options::SOUND_UPGRADE = "upgrade.wav";
#else
const char* Options::SOUND_MAIN_MUSIC = "mus_fast02.ogg";
const char* Options::SOUND_AI_DEATH = "ai_death.ogg";
const char* Options::SOUND_AI_VOICE = "ai_voice.ogg";
const char* Options::SOUND_ALIEN_SUICIDE = "alien_suicide.ogg";
const char* Options::SOUND_ALIEN_WARNING = "alien_warning.ogg";
const char* Options::SOUND_ALIEN_SHOT = "alienshot.ogg";
const char* Options::SOUND_BASE_DAMAGE = "basedamage.ogg";
const char* Options::SOUND_BASE_SHOT = "baseshot.ogg";
const char* Options::SOUND_BEAM = "beam.ogg";
const char* Options::SOUND_BIG_EXPLOSION = "big_explosion.ogg";
const char* Options::SOUND_CHEESIE_LAND = "cheesy_land.ogg";
const char* Options::SOUND_CHEESIE_LAND2 = "cheesy_land2.ogg";
const char* Options::SOUND_COIN = "coin.ogg";
const char* Options::SOUND_HEALTH = "health.ogg";
const char* Options::SOUND_JETPACK_FAIL = "jetpack_fail.ogg";
const char* Options::SOUND_PIZZAPLOP = "pizzaplop.ogg";
const char* Options::SOUND_PLAYER_ACCELERATING = "player_accelerating.ogg";
const char* Options::SOUND_PLAYER_DEATH = "player_death.ogg";
const char* Options::SOUND_PLAYER_GETHIT = "player_gethit.ogg";
const char* Options::SOUND_PLAYER_JETPACK = "player_jetpack.ogg";
const char* Options::SOUND_POWERUP1 = "powerup_1.ogg";
const char* Options::SOUND_POWERUP2 = "powerup_2.ogg";
const char* Options::SOUND_SHOT_LAND = "shot_land.ogg";
const char* Options::SOUND_SHOT = "shot.ogg";
const char* Options::SOUND_SHOT2 = "shot2.ogg";
const char* Options::SOUND_SLICE_APPROACHING = "slice_approaching.ogg";
const char* Options::SOUND_SLICE_DOCKING = "slice_docking.ogg";
const char* Options::SOUND_SPIDER_TALK = "spider_talk.ogg";
const char* Options::SOUND_START_LEVEL = "start_level.ogg";
const char* Options::SOUND_UPGRADE = "upgrade.ogg";
#endif

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

#endif