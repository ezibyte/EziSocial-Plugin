LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ezibyte_social_static

LOCAL_MODULE_FILENAME := libezisocial

LOCAL_SRC_FILES := \
../src/EziFacebookUserBase.cpp \
../src/EziFacebookFriend.cpp \
../src/EziFacebookUser.cpp \
../src/EziFBIncomingRequest.cpp \
../src/EziFBIncomingRequestManager.cpp \
../src/EziSocialObject.cpp \
JNI_EziSocialManager.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include
		
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include
LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,network)
$(call import-module,../extensions)