#include <jni.h>
#include <string>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <android/log.h>

#define TAG "qtfreet00"
#define E(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_qtfreet_antibst_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static int is_file_v2_exists(const char *path) {
    char *dir = dirname(path);
    int cd = chdir(dir);
    if (cd != 0) {
        return 0;
    }
    char *base = basename(path);
    if (access(base, R_OK) == 0) {
        E("find v2 %s success", path);
        return 1;
    } else {
        E("find v2 %s error,error is %s", path, strerror(errno));
    }
    chdir("/");
    return 0;
}

static int is_file_v1_exists(const char *path) {
    if (access(path, R_OK) == 0) {
        E("find v1 %s success", path);
        return 1;
    } else {
        E("find v1 %s error,error is %s", path, strerror(errno));
    }
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_qtfreet_antibst_MainActivity_isBst(JNIEnv *env, jobject thiz) {
    return is_file_v1_exists("/data/.bluestacks.prop") +
           is_file_v2_exists("/data/.bluestacks.prop");

}