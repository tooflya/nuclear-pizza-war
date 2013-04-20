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
	
						this->mWealth = new EntityManager(10, new Entity("actors/pickups.png", 1, 3), this);

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

					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/upgrade.ogg");
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
				UpgradeButton("gui/shopicons_fire_damage_level.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;

					this->mLabel = CCLabelTTF::create("Fire Damage: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(125), Utils::coord(7)));

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
						sprintf(text, "Fire Damage: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Fire Damage: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Fire Damage: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class RateButton : public UpgradeButton
		{
			public:
				RateButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_firerate.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;

					this->mLabel = CCLabelTTF::create("Fire Rate: 0 / 5", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(112), Utils::coord(7)));

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
						sprintf(text, "Fire Rate: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Fire Rate: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Fire Rate: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class SpeedButton : public UpgradeButton
		{
			public:
				SpeedButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_speed.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create("Speed: 0 / 5", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(100), Utils::coord(7)));

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
						sprintf(text, "Speed: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Speed: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Speed: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class RegenerationButton : public UpgradeButton
		{
			public:
				RegenerationButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_regenerate.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create("Regeneration Rate: 0 / 5", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(147), Utils::coord(7)));

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
						sprintf(text, "Regeneration Rate: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Regeneration Rate: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Regeneration Rate: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class HealthButton : public UpgradeButton
		{
			public:
				HealthButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_health.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create("Max Health: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(120), Utils::coord(7)));

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
						sprintf(text, "Max Health: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Max Health: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Max Health: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class BeamButton : public UpgradeButton
		{
			public:
				BeamButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_count.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create("Beem Ammo: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(125), Utils::coord(7)));

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
						sprintf(text, "Beem Ammo: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Beem Ammo: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Beem Ammo: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class ShockwaveButton : public UpgradeButton
		{
			public:
				ShockwaveButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_nova.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create("Shockwave Damage: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(152), Utils::coord(7)));

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
						sprintf(text, "Shockwave Damage: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Shockwave Damage: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Shockwave Damage: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class JetpackButton : public UpgradeButton
		{
			public:
				JetpackButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_jetpack.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 2;
					
					this->mLabel = CCLabelTTF::create("Jetpack power: 0 / 2", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));

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
						sprintf(text, "Jetpack power: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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

							sprintf(text, "Jetpack power: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Jetpack power: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class FortificationButton : public UpgradeButton
		{
			public:
				FortificationButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_base_walls.png", pWorld, pManager)
				{
					this->mCurrentIndex = 12;
					this->mMaxIndex = 23;
					
					this->mLabel = CCLabelTTF::create("Fortification: 12 / 23", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(133), Utils::coord(7)));

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
						sprintf(text, "Fortification: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Fortification: MAX");
							this->mLabel->setString(text);
							this->mLabel->setColor(ccc3(255.0f, 230.0f, 0.0f));

							this->mManager->check();
						}
					}
				}

				void update()
				{
					char text[256];
					sprintf(text, "Fortification: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
					sprintf(text, "Fortification: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class BlasterButton : public UpgradeButton
		{
			public:
				BlasterButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_base_shot.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 5;
					
					this->mLabel = CCLabelTTF::create("Tower Blaster: 0 / 5", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));

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
						sprintf(text, "Tower Blaster: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Tower Blaster: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Tower Blaster: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class NovaButton : public UpgradeButton
		{
			public:
				NovaButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_base_blast.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create("Nova Defence: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(130), Utils::coord(7)));

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
						sprintf(text, "Nova Defence: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Nova Defence: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Nova Defence: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
		};

		class SpidersButton : public UpgradeButton
		{
			public:
				SpidersButton(Level* pWorld, UpgradeManager* pManager) :
				UpgradeButton("gui/shopicons_base_spider.png", pWorld, pManager)
				{
					this->mCurrentIndex = 0;
					this->mMaxIndex = 3;
					
					this->mLabel = CCLabelTTF::create("Defence Spiders: 0 / 3", "Arial",  Utils::coord(16));

					this->mLabel->setPosition(ccp(Utils::coord(140), Utils::coord(7)));

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
						sprintf(text, "Defence Spiders: %d / %d", this->mCurrentIndex, this->mMaxIndex);
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
							
							sprintf(text, "Defence Spiders: MAX");
							this->mLabel->setString(text);
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
					sprintf(text, "Defence Spiders: %d / %d", this->mCurrentIndex, this->mMaxIndex);
					this->mLabel->setString(text);
				}
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

UpgradeManager::UpgradeManager(Level* pWorld)
{
	this->mWorld = pWorld;

	Entity* holder1 = new Entity("gui/holder1.png");
	Entity* holder2 = new Entity("gui/holder1.png");

	holder1->create()->setCenterPosition(Options::CAMERA_CENTER_X - holder1->getWidth() / 2 - Utils::coord(50), Options::CAMERA_CENTER_Y);
	holder2->create()->setCenterPosition(Options::CAMERA_CENTER_X + holder2->getWidth() / 2 + Utils::coord(50), Options::CAMERA_CENTER_Y);

	this->addChild(holder1);
	this->addChild(holder2);

	for(int i = 0; i < 8; i++)
	{
		Entity* holder = new Entity("gui/holder2.png");
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
		Entity* holder = new Entity("gui/holder2.png");
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