#ifndef CONST_TOUCHABLE
#define CONST_TOUCHABLE

#include "Touchable.h"

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

Touchable::Touchable()
{
	this->mIsRegisterAsTouchable = false;
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void Touchable::setRegisterAsTouchable(bool pTouchable)
{
	this->mIsRegisterAsTouchable = pTouchable;
}

void Touchable::onTouch(CCTouch* touch, CCEvent* event)
{
}

// ===========================================================
// Virtual methods
// ===========================================================

bool Touchable::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!this->mIsRegisterAsTouchable)
	{
		return false;
	}

	if(this->containsTouchLocation(touch))
	{
		this->mWasTouched = true;

		return true;
	}

	return true;
}

void Touchable::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(!this->containsTouchLocation(touch))
	{
		this->mWasTouched = false;
	}
}

void Touchable::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mWasTouched)
	{
		this->onTouch(touch, event);
	}

	this->mWasTouched = false;
}

bool Touchable::containsTouchLocation(CCTouch* touch)
{
	return true;
}

#endif