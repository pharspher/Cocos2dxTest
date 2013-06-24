LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

SRC_FILE_LIST := $(../../Classes/*.cpp)
LOCAL_SRC_FILES := jni_src/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Scenes/HelloWorldScene.cpp \
                   ../../Classes/Scenes/MenuScene.cpp \
                   ../../Classes/Scenes/FightScene.cpp \
                   ../../Classes/Card/Card.cpp \
                   ../../Classes/Card/Deck.cpp \
                   ../../Classes/Utils/Log.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

LOCAL_LDLIBS := -lGLESv1_CM

$(call import-add-path, /Users/rogerchuang/SDK/Cocos2d-x/cocos2d-2.1rc0-x-2.1.3) \
$(call import-add-path, /Users/rogerchuang/SDK/Cocos2d-x/cocos2d-2.1rc0-x-2.1.3/cocos2dx/platform/third_party/android/prebuilt) \
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
