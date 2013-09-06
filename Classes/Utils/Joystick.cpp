#ifndef CONST_JOYSTICK
#define CONST_JOYSTICK

#include "Joystick.h"

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

Joystick::Joystick() :
	Entity("onscreen_control_base.png")
	{
		this->mButton = new Entity("onscreen_control_knob.png");
		this->mButton->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);

		this->addChild(this->mButton);

		this->create()->setOpacity(0.0f);
	}

// ===========================================================
// Methods
// ===========================================================

void Joystick::fade(bool pAction)
{
	if(pAction)
	{
		this->runAction(CCFadeTo::create(0.4f, 255.0f));
	}
	else
	{
		this->runAction(CCFadeTo::create(0.4f, 0.0f));
	}
	
	this->mButton->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
}

void Joystick::update(CCPoint pLocation)
{
	float x = pLocation.x - this->getCenterX();
	float y = pLocation.y - this->getCenterY();

	if(x * x + y * y <= Utils::coord(2700.0f))
	{
		this->mFullPower = false;
	}
	else
	{
		float angleRad = atan2(y, x);

		x = cos(angleRad) * Utils::coord(55.5f);
		y = sin(angleRad) * Utils::coord(55.5f);

		this->mFullPower = true;
	}

	this->mVectorX = -x * 10;
	this->mVectorY = -y * 10;
	
	x += this->getWidth() / 2;
	y += this->getHeight() / 2;

	this->mButton->setCenterPosition(x, y);
}

CCPoint Joystick::getVector()
{
	return ccp(this->mVectorX, this->mVectorY);
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Joystick::setOpacity(GLubyte pOpaque)
{
	Entity::setOpacity(pOpaque);

	for(int i = 0; i < this->getChildren()->count(); i++)
	{
		((Entity*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpaque);
	}
}

#endif