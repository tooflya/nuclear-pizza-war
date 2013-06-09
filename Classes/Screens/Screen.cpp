#ifndef CONST_SCREEN
#define CONST_SCREEN

#include "Screen.h"

#include "platform/android/jni/JniHelper.h"



#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME "com/tooflya/nuclearpizzawar/BaseGameActivity"

extern "C"
{
    // get env and cache it
    static JNIEnv* getJNIEnv(void)
    {
        
        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm) {
            return NULL;
        }
        
        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
        
        switch (ret) {
            case JNI_OK :
                // Success!
                return env;
                
            case JNI_EDETACHED :
                // Thread not attached
                
                // TODO : If calling AttachCurrentThread() on a native thread
                // must call DetachCurrentThread() in future.
                // see: http://developer.android.com/guide/practices/design/jni.html
                
                if (jvm->AttachCurrentThread(&env, NULL) < 0)
                {
                    return NULL;
                } else {
                    // Success : Attached and obtained JNIEnv!
                    return env;
                }
                
            case JNI_EVERSION :
                // Cannot recover from this error
            default :
                return NULL;
        }
    }
    
    // get class and make it a global reference, release it at endJni().
    static jclass getClassID(JNIEnv *pEnv)
    {
        jclass ret = pEnv->FindClass(CLASS_NAME);
        if (! ret)
        {
        }
        
        return ret;
    }

    static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;
        
        do 
        {
            pEnv = getJNIEnv();
            if (! pEnv)
            {
                break;
            }
            
            jclass classID = getClassID(pEnv);
            
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                break;
            }
            
            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;
            
            bRet = true;
        } while (0);
        
        return bRet;
    }

    void onMainMenuStarted()
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniOnMainMenuStarted", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void GooglePlusstartWaitingForBattle()
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniStartWaitingForBattle", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void broadcastMessage(const int param1, const int param2, const int param3, const int param4)
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniBroadcastMessage", "(IIII)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)param1, (int)param2, (int)param3, (int)param4);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void openLeaderBoard()
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniOpenLeaderBoard", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void openAchievementBoard()
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniOpenAchievementBoard", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void updateLeaderBoard(int data)
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniUpdateLeaderBoard", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, data);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void unlockAchievement(int id)
    {
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfo(methodInfo, "JniUnlockAchievement", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    jint Java_com_tooflya_nuclearpizzawar_Game_nativeOnGooglePlusSignInSucceeded(JNIEnv *env, jobject thiz)
    {
        MainMenu::nativeOnGooglePlusSignInSucceeded();

        return 0;
    }

    jint Java_com_tooflya_nuclearpizzawar_Game_nativeOnGooglePlusConnedctedToRoom(JNIEnv *env, jobject thiz)
    {
        MainMenu::nativeOnGooglePlusConnedctedToRoom();

        return 0;
    }

    jint Java_com_tooflya_nuclearpizzawar_Game_nativeOnGooglePlusRealtimeMessageReceived(JNIEnv *env, jobject thiz, jint param1, jint param2, jint param3, jint param4)
    {
        Level::nativeOnGooglePlusRealtimeMessageReceived(param1, param2, param3, param4);

        return 0;
    }
}

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

// ===========================================================
// Constructors
// ===========================================================

Screen::Screen()
{
	this->scheduleUpdate();
}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual methods
// ===========================================================

bool Screen::containsTouchLocation(CCTouch* touch)
{
	return CCRectMake(-Options::CAMERA_WIDTH / 2, -Options::CAMERA_HEIGHT / 2, Options::CAMERA_WIDTH, Options::CAMERA_HEIGHT).containsPoint(convertTouchToNodeSpaceAR(touch)); // TODO: I should check this instructions;
}

void Screen::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCScene::onEnter();
}

void Screen::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCScene::onExit();
}

#endif