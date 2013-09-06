#ifndef CONST_ENEMYGROUP
#define CONST_ENEMYGROUP

#include "EnemyGroup.h"

#include "Level.h"

// ===========================================================
// Inner Classes
// ===========================================================

class EnemyGroupParams : public CCObject
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

		int mCount;
		int mType;
		int mLevel;

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

		// ===========================================================
		// Constructors
		// ===========================================================

		EnemyGroupParams(int pCount, int pType, int pLevel)
		{
			this->mCount = pCount;
			this->mType = pType;
			this->mLevel = pLevel;
		}

		// ===========================================================
		// Methods
		// ===========================================================

		int getCount()
		{
			return this->mCount;
		}

		int getType()
		{
			return this->mType;
		}

		int getLevel()
		{
			return this->mLevel;
		}
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
};

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

EnemyGroup::EnemyGroup(Level* pWorld, float pTimeOutSinceLastWave)
{
	this->mWorld = pWorld;

	this->mTimeOutSinceLastWave = pTimeOutSinceLastWave;
	this->mTimeOutSinceLastWaveElapsed = 0;

	this->mEmmiters = new CCPoint[8];

	this->mEmmiters[0] = ccp(Utils::coord(50), 		Utils::coord(160));
	this->mEmmiters[1] = ccp(Utils::coord(-100), 	Utils::coord(350));
	this->mEmmiters[2] = ccp(Utils::coord(200), 	Utils::coord(570));
	this->mEmmiters[3] = ccp(Utils::coord(800), 	Utils::coord(70));
	this->mEmmiters[4] = ccp(Utils::coord(1170), 	Utils::coord(350));
	this->mEmmiters[5] = ccp(Utils::coord(800), 	Utils::coord(570));
	this->mEmmiters[6] = ccp(Utils::coord(390), 	Utils::coord(50));
	this->mEmmiters[7] = ccp(Utils::coord(390), 	Utils::coord(580));

	this->mGroups = new CCArray();
	this->mGroups->initWithCapacity(20);

	this->scheduleUpdate();
}

// ===========================================================
// Methods
// ===========================================================

EnemyGroup* EnemyGroup::addEnemy(int pCount, int pType, int pLevel)
{
	this->mGroups->addObject(new EnemyGroupParams(pCount, pType, pLevel));

	return this;
}

// ===========================================================
// Virtual Methods
// ===========================================================

void EnemyGroup::update(float pDeltaTime)
{
	CCNode::update(pDeltaTime);

	this->mTimeOutSinceLastWaveElapsed += pDeltaTime;

	if(this->mTimeOutSinceLastWaveElapsed >= this->mTimeOutSinceLastWave)
	{
		this->mTimeOutSinceLastWaveElapsed = 0;

		for(int a = 0; a < this->mGroups->count(); a++)
		{
			EnemyGroupParams* params = (EnemyGroupParams*) this->mGroups->objectAtIndex(a);
			int r = Utils::random(0, 8);

			float x = ((CCPoint) this->mEmmiters[r]).x;
			float y = ((CCPoint) this->mEmmiters[r]).y;

			for(int i = 0; i < params->getCount(); i++)
			{
				if(i % 4 == 0 && i != 0)
				{
					x = ((CCPoint) this->mEmmiters[r]).x;
					y -= 16;
				}

				x += 16;

				BaseEnemy* enemy = (BaseEnemy*) ((EntityManager*) this->mWorld->mEnemies->objectAtIndex(params->getType()))->create();

				enemy->setCenterPosition(x, y);

				switch(params->getType())
				{
					case 0:
						switch(params->getLevel())
						{
							case 0:
								enemy->setMaxHealth(100.0f);
								enemy->setSpeed(40.0f);
							break;
							case 1:
								enemy->setMaxHealth(200);
								enemy->setSpeed(60.0f);
							break;
							case 2:
								enemy->setMaxHealth(300);
								enemy->setSpeed(90.0f);
							break;
						}
					break;
					case 1:
						switch(params->getLevel())
						{
							case 0:
								enemy->setMaxHealth(100);
								enemy->setSpeed(30.0f);
							break;
							case 1:
								enemy->setMaxHealth(200);
								enemy->setSpeed(40.0f);
							break;
							case 2:
								enemy->setMaxHealth(100);
								enemy->setSpeed(60.0f);
							break;
						}
					break;
					case 2:
						switch(params->getLevel())
						{
							case 0:
								enemy->setMaxHealth(150);
								enemy->setFireTime(Utils::randomf(3.0f, 15.0f));

								((FiredEnemy*) enemy)->mShootsCount = 1;
							break;
							case 1:
								enemy->setMaxHealth(300);
								enemy->setFireTime(Utils::randomf(3.0f, 10.0f));

								((FiredEnemy*) enemy)->mShootsCount = 3;
							break;
							case 2:
								enemy->setMaxHealth(450);
								enemy->setFireTime(Utils::randomf(3.0f, 7.0f));

								((FiredEnemy*) enemy)->mShootsCount = 3;
							break;
						}
					break;
					case 3:
						switch(params->getLevel())
						{
							case 0:
								enemy->setMaxHealth(600);
								enemy->setFireTime(Utils::randomf(3.0f, 15.0f));
								enemy->setSpeed(20.0f);

								((BigEnemy*) enemy)->mShootsCount = 7;
							break;
							case 1:
								enemy->setMaxHealth(1000);
								enemy->setFireTime(Utils::randomf(3.0f, 10.0f));
								enemy->setSpeed(15.0f);
								
								((BigEnemy*) enemy)->mShootsCount = 10;
							break;
							case 2:
								enemy->setMaxHealth(1200);
								enemy->setFireTime(Utils::randomf(3.0f, 7.0f));
								enemy->setSpeed(10.0f);
								
								((BigEnemy*) enemy)->mShootsCount = 12;
							break;
						}
                        break;
					case 4:
						switch(params->getLevel())
                        {
                            case 0:
                                enemy->setMaxHealth(600);
                                enemy->setSpeed(40.0f);
                            break;
                            case 1:
                                enemy->setMaxHealth(1000);
                                enemy->setSpeed(60.0f);
							break;
                            case 2:
                                enemy->setMaxHealth(1200);
                                enemy->setSpeed(80.0f);
							break;
                        }
                    break;
				}
			}
		}

		this->removeFromParent();
		this->release();
	}
}

#endif