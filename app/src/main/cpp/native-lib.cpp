#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_baidu_liliqiang_android_1curl_1ndk_1sample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


#include <string.h>
#include <jni.h>
#include <iostream>
#include <string>
//#include <curl/curl.h>
#include <android/log.h>
#include <curl/curl.h>

#define LOG_TAG "c++ log:"

#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)

using namespace std;

string response;

size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) {

    for (int c = 0; c < size * nmemb; c++) {
        response.push_back(buf[c]);
    }

    return size * nmemb;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_baidu_liliqiang_android_1curl_1ndk_1sample_MainActivity_getCurl(JNIEnv *env,
                                                                           jobject thiz) {

    CURL * curl;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, "http://baidu.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    LOGD("http content::%s", response.c_str());
    string bodyStr = response.c_str();
    return env->NewStringUTF(response.c_str());
}
