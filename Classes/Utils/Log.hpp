/*
 * Log.h
 *
 *  Created on: 2013/6/14
 *      Author: rogerchuang
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>

#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace ph {

class Log {
public:
    static void d(const std::string tag, const std::string message) {
        __android_log_print(ANDROID_LOG_DEBUG, tag.c_str(), message.c_str());
    }

    static void e(const std::string tag, const std::string message) {
        __android_log_print(ANDROID_LOG_ERROR, tag.c_str(), message.c_str());
    }

    static void i(const std::string tag, const std::string message) {
        __android_log_print(ANDROID_LOG_INFO, tag.c_str(), message.c_str());
    }

    static void w(const std::string tag, const std::string message) {
        __android_log_print(ANDROID_LOG_WARN, tag.c_str(), message.c_str());
    }

private:
    Log();
};

} /* namespace ph */
#endif /* LOG_H_ */
