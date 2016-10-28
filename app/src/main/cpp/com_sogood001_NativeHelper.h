//
// Created by li-yuweii on 16-10-28.
//

#ifndef NDKDEMO_COM_SOGOOD001_NATIVEHELPER_H
#define NDKDEMO_COM_SOGOOD001_NATIVEHELPER_H

#include <jni.h>

//声明两个方法，这些方法需要在.C的文件中实现，真正写代码在.C里面

/**
 * 获取APPKEY
 */
JNIEXPORT jstring JNICALL
                    Java_com_sogood001_ndkdemo_NativeHelper_getAppKey(JNIEnv *env, jclass type);

/**
 * 获取Secret
 */
JNIEXPORT jstring JNICALL
                    Java_com_sogood001_ndkdemo_NativeHelper_getAppSecret(JNIEnv *env, jclass type);

JNIEXPORT jint JNICALL
        Java_com_sogood001_ndkdemo_NativeHelper_add(JNIEnv *env, jclass type, jint a, jint b);

//声明，传递字符串的方法
//JNIEXPORT 代表可以被java调用
//JNICALL 代表方法符合JNI接口的调用规范
JNIEXPORT void JNICALL
        Java_com_sogood001_ndkdemo_NativeHelper_sayHello(JNIEnv *env,jclass type, jstring str);

#endif //NDKDEMO_COM_SOGOOD001_NATIVEHELPER_H
