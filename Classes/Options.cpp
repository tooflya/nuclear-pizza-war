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