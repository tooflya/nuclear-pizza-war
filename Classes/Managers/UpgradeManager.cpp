#ifndef CONST_UPGRADEMANAGER
#define CONST_UPGRADEMANAGER

#include "UpgradeManager.h"

// ===========================================================
// Inner Classes
// ===========================================================

		class UpgradeButton : public Entity
		{
			protected:
				CCLabelTTF* mLabel;

				Level* mWorld;

				UpgradeManager* mManager;

				EntityManager* mWealth;

			public:
				int* mCoinsNeed;

				int mCurrentIndex;
				int mMaxIndex;

				UpgradeButton(const char* pszFileName, Level* pWorld, UpgradeManager* pManager) :
					Entity(pszFileName)
					{
						this->mWorld = pWorld;
						this->mManager = pManager;
	
						this->mWealth = new EntityManager(10, new Entity("pickups.png", 1, 3), this);

						this->mCoinsNeed = new int[3];

						this->disable();
					}

				virtual void reset()
				{
					this->mCurrentIndex = 0;

					this->disable();
					this->mLabel->setColor(ccc3(255.0f, 255.0f, 255.0f));
				}

				void enable()
				{
					this->setRegisterAsTouchable(true);

					this->setColor(ccc3(255.0f, 255.0f, 255.0f));
				}

				void disable()
				{
					this->setRegisterAsTouchable(false);

					this->setColor(ccc3(100.0f, 100.0f, 100.0f));
				}

				void check()
				{
					if(
						(Level::COINS[0] < this->mCoinsNeed[0] ||
						Level::COINS[1] < this->mCoinsNeed[1] ||
						Level::COINS[2] < this->mCoinsNeed[2]) ||
						this->mCurrentIndex >= this->mMaxIndex)
					{
						this->disable();
					}
					else
					{
						this->enable();
					}

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->generateWealth();
					}
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					for(int a = 0; a < 3; a++)
					{
						for(int i = 0; i < this->mCoinsNeed[a]; i++)
						{
							this->mWorld->mWealth->remove(a);
						}
					}

					this->mManager->check();

					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(Options::SOUND_UPGRADE);
				}

				void generateWealth()
				{
					this->mWealth->clear();

					for(int a = 0; a < 3; a++)
					{
						for(int i = 0; i < this->mCoinsNeed[a]; i++)
						{
							Entity* icon = this->mWealth->create();

							icon->setCurrentFrameIndex(a);
						}
					}

					int p = 0;
					int j;

					for(int i = 0; i < 3; i++)
					{
						int s = 0;

						for(j = 0; j < this->mWealth->getCount(); j++, p++)
						{
							Entity* entity = (Entity*) this->mWealth->objectAtIndex(j);

							if(entity->getCurrentFrameIndex() != i) continue;

							entity->setCenterPosition(Utils::coord(70) + p, Utils::coord(30));

							p += Utils::coord(10);

							s++;
						}

						if(s > 0) p += Utils::coord(5);
					}
				}
		};

		class DamageButton : public UpgradeButton
		{
			public:
				DamageButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_fire_damage_level.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;

					this->mLabel = CCLabelTTF::create(UpgradeManager::FIRE_DAMAGE_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(125), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 3;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(0, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::FIRE_DAMAGE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 6;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 5;
								break;
								case 2:
									this->mCoinsNeed[0] = 12;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 6;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::FIRE_DAMAGE_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 3;

					char text[256];
					sprintf(text, UpgradeManager::FIRE_DAMAGE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class RateButton : public UpgradeButton
		{
			public:
				RateButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_firerate.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;

					this->mLabel = CCLabelTTF::create(UpgradeManager::FIRE_RATE_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(112), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 1;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(1, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::FIRE_RATE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 2;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 2;
								break;
								case 2:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 2;
								break;
								case 3:
									this->mCoinsNeed[0] = 8;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 5;
								break;
								case 4:
									this->mCoinsNeed[0] = 10;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 7;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::FIRE_RATE_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 1;
					
					char text[256];
					sprintf(text, UpgradeManager::FIRE_RATE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class SpeedButton : public UpgradeButton
		{
			public:
				SpeedButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_speed.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::SPEED_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(100), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 1;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(2, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::SPEED_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 1;
									this->mCoinsNeed[1] = 3;
									this->mCoinsNeed[2] = 0;
								break;
								case 2:
									this->mCoinsNeed[0] = 1;
									this->mCoinsNeed[1] = 4;
									this->mCoinsNeed[2] = 1;
								break;
								case 3:
									this->mCoinsNeed[0] = 2;
									this->mCoinsNeed[1] = 5;
									this->mCoinsNeed[2] = 1;
								break;
								case 4:
									this->mCoinsNeed[0] = 2;
									this->mCoinsNeed[1] = 5;
									this->mCoinsNeed[2] = 7;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::SPEED_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 1;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::SPEED_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class RegenerationButton : public UpgradeButton
		{
			public:
				RegenerationButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_regenerate.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::REGENERATION_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(147), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(3, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::REGENERATION_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 2;
									this->mCoinsNeed[2] = 0;
								break;
								case 2:
									this->mCoinsNeed[0] = 5;
									this->mCoinsNeed[1] = 3;
									this->mCoinsNeed[2] = 1;
								break;
								case 3:
									this->mCoinsNeed[0] = 7;
									this->mCoinsNeed[1] = 3;
									this->mCoinsNeed[2] = 1;
								break;
								case 4:
									this->mCoinsNeed[0] = 12;
									this->mCoinsNeed[1] = 2;
									this->mCoinsNeed[2] = 1;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::REGENERATION_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::REGENERATION_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class HealthButton : public UpgradeButton
		{
			public:
				HealthButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_health.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::HEALTH_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(120), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(4, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::HEALTH_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 0;
								break;
								case 2:
									this->mCoinsNeed[0] = 5;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 0;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::HEALTH_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::HEALTH_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class BeamButton : public UpgradeButton
		{
			public:
				BeamButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_count.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::BEEM_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(125), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 3;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(7, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::BEEM_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 8;
								break;
								case 2:
									this->mCoinsNeed[0] = 1;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 8;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::BEEM_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 3;
					
					char text[256];
					sprintf(text, UpgradeManager::BEEM_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class ShockwaveButton : public UpgradeButton
		{
			public:
				ShockwaveButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_nova.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::SHOCKWAVE_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(152), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 2;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(6, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::SHOCKWAVE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 3;
								break;
								case 2:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 4;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::SHOCKWAVE_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 2;
					
					char text[256];
					sprintf(text, UpgradeManager::SHOCKWAVE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class JetpackButton : public UpgradeButton
		{
			public:
				JetpackButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_jetpack.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 2;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::JETPACK_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mHero->update(5, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::JETPACK_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 4;
									this->mCoinsNeed[2] = 0;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();

							sprintf(text, UpgradeManager::JETPACK_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::JETPACK_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class FortificationButton : public UpgradeButton
		{
			public:
				FortificationButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_base_walls.png", pWorld, pManager)
				{
					this->mCurrentIndex = 12;
					this->mMaxIndex = 23;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::FORTIFICATION_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(133), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mCastle->update(2, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::FORTIFICATION_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							this->mCoinsNeed[0] = 2;
							this->mCoinsNeed[1] = 0;
							this->mCoinsNeed[2] = 0;
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::FORTIFICATION_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void update()
				{
					char text[256];
					sprintf(text, UpgradeManager::FORTIFICATION_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mLabel->setColor(ccc3(255.0f, 255.0f, 255.0f));
					}
					else
					{
						this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));
					}
				}

				void reset()
				{
					UpgradeButton::reset();

					this->mCoinsNeed[0] = 2;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::FORTIFICATION_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class BlasterButton : public UpgradeButton
		{
			public:
				BlasterButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_base_shot.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::TOWER_BLASTER_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 1;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mCastle->update(0, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::TOWER_BLASTER_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 2;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 2;
								break;
								case 2:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 0;
									this->mCoinsNeed[2] = 3;
								break;
								case 3:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 4;
									this->mCoinsNeed[2] = 4;
								break;
								case 4:
									this->mCoinsNeed[0] = 4;
									this->mCoinsNeed[1] = 8;
									this->mCoinsNeed[2] = 6;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::TOWER_BLASTER_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 0;
					this->mCoinsNeed[2] = 1;
					
					char text[256];
					sprintf(text, UpgradeManager::TOWER_BLASTER_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class NovaButton : public UpgradeButton
		{
			public:
				NovaButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_base_blast.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::NOVA_DEFENCE_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 1;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->mCastle->update(1, this->mCurrentIndex);

						char text[256];
						sprintf(text, UpgradeManager::NOVA_DEFENCE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 3;
								break;
								case 2:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 1;
									this->mCoinsNeed[2] = 5;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::NOVA_DEFENCE_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 1;
					this->mCoinsNeed[2] = 1;
					
					char text[256];
					sprintf(text, UpgradeManager::NOVA_DEFENCE_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class SpidersButton : public UpgradeButton
		{
			public:
				SpidersButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("shopicons_base_spider.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create(UpgradeManager::DEFENCE_SPIDERS_TEXT1, "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(140), Utils::coord(7)));
					this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));

					this->addChild(this->mLabel);
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 5;
					this->mCoinsNeed[2] = 0;
				}

				void onTouch(CCTouch* touch, CCEvent* event)
				{
					UpgradeButton::onTouch(touch, event);

					if(this->mCurrentIndex < this->mMaxIndex)
					{
						this->mCurrentIndex++;

						this->mWorld->updateSpiders();

						char text[256];
						sprintf(text, UpgradeManager::DEFENCE_SPIDERS_TEXT2, this->mCurrentIndex, this->mMaxIndex);
						this->mLabel->setString(text);

						if(this->mCurrentIndex < this->mMaxIndex)
						{
							switch(this->mCurrentIndex)
							{
								case 1:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 9;
									this->mCoinsNeed[2] = 0;
								break;
								case 2:
									this->mCoinsNeed[0] = 0;
									this->mCoinsNeed[1] = 12;
									this->mCoinsNeed[2] = 0;
								break;
							}

							this->check();
						}
						else
						{
							this->mWealth->clear();
							
							sprintf(text, UpgradeManager::DEFENCE_SPIDERS_TEXT3);
							this->mLabel->setString(text);
							this->mLabel->setPosition(ccp(Utils::coord(60) + this->mLabel->getContentSize().width/2, Utils::coord(7)));
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void reset()
				{
					UpgradeButton::reset();
					
					this->mCoinsNeed[0] = 0;
					this->mCoinsNeed[1] = 5;
					this->mCoinsNeed[2] = 0;
					
					char text[256];
					sprintf(text, UpgradeManager::DEFENCE_SPIDERS_TEXT2, this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

// ===========================================================
// Constants
// ===========================================================

const char* UpgradeManager::FIRE_DAMAGE_TEXT1 = "Fire Damage: 0 / 3";
const char* UpgradeManager::FIRE_DAMAGE_TEXT2 = "Fire Damage: %d / %d";
const char* UpgradeManager::FIRE_DAMAGE_TEXT3 = "Fire Damage: MAX";

const char* UpgradeManager::FIRE_RATE_TEXT1 = "Fire Rate: 0 / 5";
const char* UpgradeManager::FIRE_RATE_TEXT2 = "Fire Rate: %d / %d";
const char* UpgradeManager::FIRE_RATE_TEXT3 = "Fire Rate: MAX";

const char* UpgradeManager::SPEED_TEXT1 = "Speed: 0 / 5";
const char* UpgradeManager::SPEED_TEXT2 = "Speed: %d / %d";
const char* UpgradeManager::SPEED_TEXT3 = "Speed: MAX";

const char* UpgradeManager::REGENERATION_TEXT1 = "Regeneration Rate: 0 / 5";
const char* UpgradeManager::REGENERATION_TEXT2 = "Regeneration Rate: %d / %d";
const char* UpgradeManager::REGENERATION_TEXT3 = "Regeneration Rate: MAX";

const char* UpgradeManager::HEALTH_TEXT1 = "Max Health: 0 / 3";
const char* UpgradeManager::HEALTH_TEXT2 = "Max Health: %d / %d";
const char* UpgradeManager::HEALTH_TEXT3 = "Max Health: MAX";

const char* UpgradeManager::BEEM_TEXT1 = "Beem Ammo: 0 / 3";
const char* UpgradeManager::BEEM_TEXT2 = "Beem Ammo: %d / %d";
const char* UpgradeManager::BEEM_TEXT3 = "Beem Ammo: MAX";

const char* UpgradeManager::SHOCKWAVE_TEXT1 = "Shockwave Damage: 0 / 3";
const char* UpgradeManager::SHOCKWAVE_TEXT2 = "Shockwave Damage: %d / %d";
const char* UpgradeManager::SHOCKWAVE_TEXT3 = "Shockwave Damage: MAX";

const char* UpgradeManager::JETPACK_TEXT1 = "Jetpack Power: 0 / 2";
const char* UpgradeManager::JETPACK_TEXT2 = "Jetpack Power: %d / %d";
const char* UpgradeManager::JETPACK_TEXT3 = "Jetpack Power: MAX";

const char* UpgradeManager::FORTIFICATION_TEXT1 = "Fortification: 12 / 23";
const char* UpgradeManager::FORTIFICATION_TEXT2 = "Fortification: %d / %d";
const char* UpgradeManager::FORTIFICATION_TEXT3 = "Fortification: MAX";

const char* UpgradeManager::TOWER_BLASTER_TEXT1 = "Tower Blaster: 0 / 5";
const char* UpgradeManager::TOWER_BLASTER_TEXT2 = "Tower Blaster: %d / %d";
const char* UpgradeManager::TOWER_BLASTER_TEXT3 = "Tower Blaster: MAX";

const char* UpgradeManager::NOVA_DEFENCE_TEXT1 = "Nova Defence: 0 / 3";
const char* UpgradeManager::NOVA_DEFENCE_TEXT2 = "Nova Defence: %d / %d";
const char* UpgradeManager::NOVA_DEFENCE_TEXT3 = "Nova Defence: MAX";

const char* UpgradeManager::DEFENCE_SPIDERS_TEXT1 = "Defence Spiders: 0 / 3";
const char* UpgradeManager::DEFENCE_SPIDERS_TEXT2 = "Defence Spiders: %d / %d";
const char* UpgradeManager::DEFENCE_SPIDERS_TEXT3 = "Defence Spiders: MAX";

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

UpgradeManager::UpgradeManager(Level* pWorld)
{
	ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
    	case kLanguageRussian:
    		FIRE_DAMAGE_TEXT1 = "Урон стрельбы: 0 / 3";
    		FIRE_DAMAGE_TEXT2 = "Урон стрельбы: %d / %d";
    		FIRE_DAMAGE_TEXT3 = "Урон стрельбы: Макс.";

    		FIRE_RATE_TEXT1 = "Скорость стрельбы: 0 / 5";
    		FIRE_RATE_TEXT2 = "Скорость стрельбы: %d / %d";
    		FIRE_RATE_TEXT3 = "Скорость стрельбы: Макс.";

    		SPEED_TEXT1 = "Скорость: 0 / 5";
    		SPEED_TEXT2 = "Скорость: %d / %d";
    		SPEED_TEXT3 = "Скорость: Макс.";

    		REGENERATION_TEXT1 = "Восстановление: 0 / 5";
    		REGENERATION_TEXT2 = "Восстановление: %d / %d";
    		REGENERATION_TEXT3 = "Восстановление: Макс.";

    		HEALTH_TEXT1 = "Здоровье: 0 / 3";
    		HEALTH_TEXT2 = "Здоровье: %d / %d";
    		HEALTH_TEXT3 = "Здоровье: Макс.";

    		BEEM_TEXT1 = "Урон лазера: 0 / 3";
    		BEEM_TEXT2 = "Урон лазера: %d / %d";
    		BEEM_TEXT3 = "Урон лазера: Макс.";

    		SHOCKWAVE_TEXT1 = "Урон ударной волны: 0 / 3";
    		SHOCKWAVE_TEXT2 = "Урон ударной волны: %d / %d";
    		SHOCKWAVE_TEXT3 = "Урон ударной волны: Макс.";

    		JETPACK_TEXT1 = "Мощность полета: 0 / 2";
    		JETPACK_TEXT2 = "Мощность полета: %d / %d";
    		JETPACK_TEXT3 = "Мощность полета: Макс.";

    		FORTIFICATION_TEXT1 = "Защита башни: 12 / 23";
    		FORTIFICATION_TEXT2 = "Защита башни: %d / %d";
    		FORTIFICATION_TEXT3 = "Защита башни: Макс.";

			TOWER_BLASTER_TEXT1 = "Урон бластера башни: 0 / 5";
			TOWER_BLASTER_TEXT2 = "Урон бластера башни: %d / %d";
			TOWER_BLASTER_TEXT3 = "Урон бластера башни: Макс.";

			NOVA_DEFENCE_TEXT1 = "Мощность защитной волны: 0 / 3";
			NOVA_DEFENCE_TEXT2 = "Мощность защитной волны: %d / %d";
			NOVA_DEFENCE_TEXT3 = "Мощность защитной волны: Макс.";

			DEFENCE_SPIDERS_TEXT1 = "Количество пауков: 0 / 3";
			DEFENCE_SPIDERS_TEXT2 = "Количество пауков: %d / %d";
			DEFENCE_SPIDERS_TEXT3 = "Количество пауков: Макс.";
    	break;
    }

	this->mWorld = pWorld;

	Entity* holder1 = new Entity("holder1.png");
	Entity* holder2 = new Entity("holder1.png");

	holder1->create()->setCenterPosition(Options::CAMERA_CENTER_X - holder1->getWidth() / 2 - Utils::coord(50), Options::CAMERA_CENTER_Y);
	holder2->create()->setCenterPosition(Options::CAMERA_CENTER_X + holder2->getWidth() / 2 + Utils::coord(50), Options::CAMERA_CENTER_Y);

	this->addChild(holder1);
	this->addChild(holder2);

	for(int i = 0; i < 8; i++)
	{
		Entity* holder = new Entity("holder2.png");
		UpgradeButton* icon;

		switch(i)
		{
			case 0:
				icon = new DamageButton(this->mWorld, this);
				this->mDamageButton = icon;
			break;
			case 1:
				icon = new RateButton(this->mWorld, this);
				this->mRateButton = icon;
			break;
			case 2:
				icon = new SpeedButton(this->mWorld, this);
				this->mSpeedButton = icon;
			break;
			case 3:
				icon = new RegenerationButton(this->mWorld, this);
				this->mRegenerationButton = icon;
			break;
			case 4:
				icon = new HealthButton(this->mWorld, this);
				this->mHealthButton = icon;
			break;
			case 5:
				icon = new BeamButton(this->mWorld, this);
				this->mBeamButton = icon;
			break;
			case 6:
				icon = new ShockwaveButton(this->mWorld, this);
				this->mShockWaveButton = icon;
			break;
			case 7:
				icon = new JetpackButton(this->mWorld, this);
				this->mJetpackButton = icon;
			break;
		}

		holder->create()->setCenterPosition(holder1->getWidth() / 2, holder1->getHeight() - holder->getHeight() * i - Utils::coord(2) * (i + 1) - holder->getHeight() / 2 - Utils::coord(2));
		icon->create()->setCenterPosition(Utils::coord(28), holder->getHeight() - icon->getHeight() / 2 - Utils::coord(5));

		holder1->addChild(holder);
		holder->addChild(icon);
	}

	for(int i = 0; i < 4; i++)
	{
		Entity* holder = new Entity("holder2.png");
		UpgradeButton* icon;

		switch(i)
		{
			case 0:
				icon = new FortificationButton(this->mWorld, this);
				this->mFortificationButton = icon;
			break;
			case 1:
				icon = new BlasterButton(this->mWorld, this);
				this->mBlasterButton = icon;
			break;
			case 2:
				icon = new NovaButton(this->mWorld, this);
				this->mNovaButton= icon;
			break;
			case 3:
				icon = new SpidersButton(this->mWorld, this);
				this->mSpidersButton = icon;
			break;
		}

		holder->create()->setCenterPosition(holder1->getWidth() / 2, holder1->getHeight() - holder->getHeight() * i - Utils::coord(2) * (i + 1) - holder->getHeight() / 2 - Utils::coord(2));
		icon->create()->setCenterPosition(Utils::coord(28), holder->getHeight() - icon->getHeight() / 2 - Utils::coord(5));

		holder2->addChild(holder);
		holder->addChild(icon);
	}
}

// ===========================================================
// Methods
// ===========================================================

void UpgradeManager::reset()
{
	this->mDamageButton->reset();
	this->mRateButton->reset();
	this->mSpeedButton->reset();
	this->mRegenerationButton->reset();
	this->mHealthButton->reset();
	this->mBeamButton->reset();
	this->mShockWaveButton->reset();
	this->mJetpackButton->reset();
	this->mFortificationButton->reset();
	this->mBlasterButton->reset();
	this->mNovaButton->reset();
	this->mSpidersButton->reset();
}


void UpgradeManager::check()
{
	this->mFortificationButton->mCurrentIndex = Options::FORTIFICATION_HEALTH_LEVEL;
	((FortificationButton*) this->mFortificationButton)->update();

	this->mDamageButton->check();
	this->mRateButton->check();
	this->mSpeedButton->check();
	this->mRegenerationButton->check();
	this->mHealthButton->check();
	this->mBeamButton->check();
	this->mShockWaveButton->check();
	this->mJetpackButton->check();
	this->mFortificationButton->check();
	this->mBlasterButton->check();
	this->mNovaButton->check();
	this->mSpidersButton->check();

	if(this->mDamageButton->mCurrentIndex >= this->mDamageButton->mMaxIndex && this->mRateButton->mCurrentIndex >= this->mRateButton->mMaxIndex)
	{
		unlockAchievement(2);
	}
}

// ===========================================================
// Virtual Methods
// ===========================================================

void UpgradeManager::onEnter()
{
	CCLayer::onEnter();

	this->check();
}

void UpgradeManager::draw()
{
	CCLayer::draw();
}

void UpgradeManager::update(float pDeltaTime)
{
	CCLayer::update(pDeltaTime);
}

#endif