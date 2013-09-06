COCOS2DX_PATH = /home/igor/Development/cocos2d-x-2.1.4/cocos2dx
COCOS_PATH = /home/igor/Development/cocos2d-x-2.1.4

COCOS2D_DEBUG = 2

EXECUTABLE = NuclearPizzaWar

INCLUDES =  -I../ \
			-I../Classes \
			-I../Classes/Screens \
			-I../Classes/Enemies \
			-I../Classes/Managers \
			-I../Classes/Entities \
			-I../Classes/Utils \
			-I../Classes/Graphics \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS_PATH)/extensions/ \
			-I$(COCOS_PATH)/external/ \
			-I$(COCOS_PATH)/CocosDenshion/include

SOURCES = ./main.cpp \
			../Classes/Options.cpp \
			../Classes/AppDelegate.cpp \
			../Classes/Utils/Utils.cpp \
			../Classes/Utils/Touchable.cpp \
			../Classes/Utils/Joystick.cpp \
			../Classes/Enemies/EnemyWave.cpp \
			../Classes/Enemies/EnemyGroup.cpp \
			../Classes/Entities/Entity.cpp \
			../Classes/Entities/Pickup.cpp \
			../Classes/Entities/Bubble.cpp \
			../Classes/Entities/FollowEnemy.cpp \
			../Classes/Entities/FiredEnemy.cpp \
			../Classes/Entities/BigEnemy.cpp \
			../Classes/Entities/BarEntity.cpp \
			../Classes/Entities/Hero.cpp \
			../Classes/Entities/Castle.cpp \
			../Classes/Entities/Spider.cpp \
			../Classes/Entities/BaseEnemy.cpp \
			../Classes/Entities/CastleEnemy.cpp \
			../Classes/Entities/BaseBullet.cpp \
			../Classes/Entities/EnemyBullet.cpp \
			../Classes/Entities/MineEnemy.cpp \
			../Classes/Entities/Star.cpp \
			../Classes/Entities/Slice.cpp \
			../Classes/Entities/Diamond.cpp \
			../Classes/Entities/BaseExplosion.cpp \
			../Classes/Entities/LongExplosion.cpp \
			../Classes/Entities/SpiderExplosion.cpp \
			../Classes/Managers/EntityManager.cpp \
			../Classes/Managers/BatchEntityManager.cpp \
			../Classes/Managers/UpgradeManager.cpp \
			../Classes/Managers/EntityManagerGroup.cpp \
			../Classes/Managers/LayerManager.cpp \
			../Classes/Managers/BackgroundStarsManager.cpp \
			../Classes/Screens/Screen.cpp \
			../Classes/Screens/Level.cpp \
			../Classes/Screens/MainMenu.cpp \
			../Classes/Screens/SplashScreen.cpp \
			../Classes/Screens/MojangSplashScreen.cpp \
			../Classes/Managers/ScreenManager.cpp \
			../Classes/Graphics/Texture.cpp \
			../Classes/Screens/GameOver.cpp \
			../Classes/Screens/GameWon.cpp \
			../Classes/Managers/WealthManager.cpp \

COCOS_ROOT = ../../../..
include $(COCOS2DX_PATH)/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \
			 $(LIB_DIR)/libcocosdenshion.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
