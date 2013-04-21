#ifndef CONST_UTILS
#define CONST_UTILS

#include "Utils.h"

#include "Entity.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

float Utils::Pi = atan(1.0) * 4;

float Utils::MILLISECONDS = 10.0f;

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

float Utils::randomf(float min, float max)
{
	return min + (float) rand() / ((float) RAND_MAX / (max - min));
}

int Utils::random(int min, int max)
{
	return min + rand() / (RAND_MAX / (max + 1 - min));
}

float Utils::coord(float pCoordinate)
{
	return pCoordinate / CCDirector::sharedDirector()->getContentScaleFactor();
}

float Utils::distance(float dX0, float dY0, float dX1, float dY1)
{
    return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

bool Utils::probably(int pProbably)
{
	return Utils::random(0, 100) < pProbably;
}

CCPoint Utils::vectorNormalize(float pVectorX, float pVectorY, float pMultipleFactor)
{
	float x = pVectorX / sqrt(pVectorX * pVectorX + pVectorY * pVectorY) * pMultipleFactor;
	float y = pVectorY / sqrt(pVectorX * pVectorX + pVectorY * pVectorY) * pMultipleFactor;

	return ccp(x, y);
}

bool Utils::isOnPizza(Entity* pEntity)
{
	float cx = Options::CAMERA_CENTER_X + Utils::coord(25);
	float cy = Options::CAMERA_CENTER_Y + Utils::coord(25);
	float pizzaRadiusX = Utils::coord(775.2f);
	float pizzaRadiusY = Utils::coord(418.2f);
	
	float dx = (pEntity->getCenterX() - cx);
	float dy = (pEntity->getCenterY() - cy) * pizzaRadiusX / pizzaRadiusY;

	return ((dx * dx) + (dy * dy)) <= pizzaRadiusX * pizzaRadiusX;
}

void Utils::obstacle(Entity* pEntity, float pX, float pY, float pMagnet, float pRadius)
{
	if(pEntity->circlesCollideCoordinatesWith(pEntity->getCenterX(), pEntity->getCenterY() - pEntity->getHeight() / 2, pX, pY, Utils::coord(pMagnet)) && pEntity->getZ() <= Options::MIN_Z)
	{
		pRadius = MAX(pEntity->getWidth(), pEntity->getHeight()) + Utils::coord(pRadius);

		float dx = (pX - pEntity->getCenterX()) * 2.5f;
		float dy = (pY - pEntity->getCenterY() + pEntity->getHeight() / 2) * 2.5f;
		{
			float dist = sqrt(dx * dx + dy * dy);

			dx = pX - (float) (dx / dist) * pRadius * 0.4f;
			dy = pY - (float) (dy / dist) * pRadius * 0.4f;
		}

		pEntity->setCenterPosition(dx, dy + pEntity->getHeight() / 2);
	}
}

void Utils::obstacle(Entity* pEntity, Entity* pEntity2, float pMagnet, float pRadius)
{
	Utils::obstacle(pEntity, pEntity2->getCenterX(), pEntity2->getCenterY(), pMagnet, pRadius);
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif