LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/Screens \
                    $(LOCAL_PATH)/../../Classes/Entities \
                    $(LOCAL_PATH)/../../Classes/Managers \
                    $(LOCAL_PATH)/../../Classes/Utils \
                    $(LOCAL_PATH)/../../Classes/Graphics \
                    $(LOCAL_PATH)/../../Classes/Enemies \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

APP_OPTIM := release