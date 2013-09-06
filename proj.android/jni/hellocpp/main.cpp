#include "AppDelegate.cpp"
#include "Options.cpp"
#include "Texture.cpp"
#include "EntityManager.cpp"
#include "BatchEntityManager.cpp"
#include "Entity.cpp"
#include "Screen.cpp"
#include "Level.cpp"
#include "ScreenManager.cpp"
#include "GameOver.cpp"
#include "GameWon.cpp"
#include "Hero.cpp"
#include "Utils.cpp"
#include "BaseBullet.cpp"
#include "Castle.cpp"
#include "Pickup.cpp"
#include "BarEntity.cpp"
#include "BaseEnemy.cpp"
#include "Touchable.cpp"
#include "EntityManagerGroup.cpp"
#include "FollowEnemy.cpp"
#include "CastleEnemy.cpp"
#include "LayerManager.cpp"
#include "Options.cpp"
#include "BaseExplosion.cpp"
#include "Slice.cpp"
#include "SplashScreen.cpp"
#include "EnemyWave.cpp"
#include "EnemyGroup.cpp"
#include "EnemyBullet.cpp"
#include "BackgroundStarsManager.cpp"
#include "BigEnemy.cpp"
#include "FiredEnemy.cpp"
#include "Bubble.cpp"
#include "MainMenu.cpp"
#include "WealthManager.cpp"
#include "UpgradeManager.cpp"
#include "Joystick.cpp"
#include "SpiderExplosion.cpp"
#include "Spider.cpp"
#include "LongExplosion.cpp"
#include "Diamond.cpp"
#include "MineEnemy.cpp"
#include "MojangSplashScreen.cpp"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}
