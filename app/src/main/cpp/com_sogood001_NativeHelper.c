//
// Created by li-yuweii on 16-10-28.
//

#include "com_sogood001_NativeHelper.h"

//加载Android日志库的方法声明
#include <android/log.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/**
 * 获取APPKEY
 */
JNIEXPORT jstring JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_getAppKey(JNIEnv *env, jclass type) {

    const char *str = "123645312156346534";
    //生成Java中的字符串对象
    //指针的指针
    //env = >   JNINativeInterface **   C语言
    jstring ret = (*env)->NewStringUTF(env, str);
    return ret;
}

/**
 * 获取Secret
 */
JNIEXPORT jstring JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_getAppSecret(JNIEnv *env, jclass type) {

    const char *str = "5354354esdfsdxfg4e5sd34g3sd4g3wefwe3wfa";
    //生成Java中的字符串对象
    //指针的指针
    //env = >   JNINativeInterface **   C语言
    jstring ret = (*env)->NewStringUTF(env, str);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_add(JNIEnv *env, jclass type, jint a, jint b) {

    return a + b;
}

JNIEXPORT void JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_sayHello(JNIEnv *env, jclass type, jstring str) {
    //TODO：显示android的日志
    //调用Android的代码，
    //代码需要调用系统的日志库，这个已经在CMakeLists.txt添加了。因此可以直接调用
    const char *TAG = "NativeHelper";
    jboolean b = JNI_FALSE;
    const char *text = (*env)->GetStringUTFChars(env, str, &b);
    //打印日志，直接显示字符串
    __android_log_write(ANDROID_LOG_DEBUG, TAG, text);

    //销毁临时生成的字符串
    (*env)->ReleaseStringUTFChars(env, str, text);
}

JNIEXPORT jintArray JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_convertBitmap(JNIEnv *env, jclass type, jintArray colors_,
                                                      jint width, jint height) {
    jint *colors = (*env)->GetIntArrayElements(env, colors_, NULL);
    jsize len = (*env)->GetArrayLength(env, colors_);
    //创建一个int型的数组
    jintArray ret = (*env)->NewIntArray(env, len);
    //把colors数组中的颜色取反
    for (int i = 0; i < len; ++i) {
        colors[i] ^= 0xFFFFFF;
    }
    //将color里面的值赋值到ret数组
    (*env)->SetIntArrayRegion(env, ret, 0, len, colors);
    (*env)->ReleaseIntArrayElements(env, colors_, colors, 0);
    return ret;
}

//-------------------------------------------------------------
//Base64编码解码代码块

static char Base64Code[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
                            'U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                            'o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7',
                            '8','9','+','/','=','\0'};

/*编码*/
char* encode(char *buf,int length)
{
    char* enbuf,*p;
    p=enbuf=malloc((length%3==0?length/3*4:(length/3+1)*4)*sizeof(char));
    int i;
    char b1,b2,b3,temp;/*辅助变量*/
    /*3字节一次进行解码，没有满足3字节用0补充*/
    for (i=0;i<length;i=i+3){
        b1=buf[i];
        *(p++)=Base64Code[((b1>>2)&0x3f)];
        b2=(i+1)>=length?0:buf[i+1];
        *(p++)=Base64Code[(((b1<<4)&0x3f)+((b2>>4)&0xf))];
        b3=(i+2)>=length?0:buf[i+2];
        /*补充的用code码表中的64位代替，就是=*/
        temp=b2==0?64:(((b2<<2)&0x3f)+((b3>>6)&0x3));
        *(p++)=Base64Code[temp];
        *(p++)=Base64Code[b3==0?64:(b3&0x3f)];
    }
    *(p)='\0';/*字符串结尾*/
    return enbuf;
}
/*取码表索引*/
char getIndex(char c,char* buf)
{
    int i;
    for (i=0;i<strlen(buf);++i){
        if (c==buf[i]){return i;}
    }
    return 0;
}

/*解码*/
char* decode(char* buf,int length)
{
    char b1,b2,b3,b4;
    int i;
    char* debuf,*p;
    p=debuf=malloc((length/4*3)*sizeof(char));
    /*4字节进行解码*/
    for (i=0;i<length;i=i+4){
        b1=getIndex(buf[i],Base64Code);
        b2=getIndex(buf[i+1],Base64Code);
        b3=getIndex(buf[i+2],Base64Code);
        b4=getIndex(buf[i+3],Base64Code);
        *(p++)=((b1<<2)+((b2>>4)&0x3));
        /*64对应=号，表示原字节空*/
        if (b3!=64){
            *(p++)=((b2&0x0f)<<4)+((b3>>2)&0xf);
            if (b4!=64){
                *(p++)=((b3<<6)+b4);
            }
        }
    }
    *(p)='\0';
    return debuf;
}



//Base64编码
JNIEXPORT jstring JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_base64Encode(JNIEnv *env, jclass type, jbyteArray data_) {
    jbyte *data = (*env)->GetByteArrayElements(env, data_, NULL);

    /*GetArrayLength 取数组长度*/
    char* enbuf=encode((char*)data,(*env)->GetArrayLength(env,data_));
    __android_log_write(ANDROID_LOG_DEBUG, "AAAAAA", enbuf);
    /*new一个字节数组*/


    (*env)->ReleaseByteArrayElements(env, data_, data, 0);

    return (*env)->NewStringUTF(env, enbuf);
}

JNIEXPORT jstring JNICALL
Java_com_sogood001_ndkdemo_NativeHelper_base64Decode(JNIEnv *env, jclass type, jbyteArray data_) {
    jbyte *data = (*env)->GetByteArrayElements(env, data_, NULL);

    char* enbuf=decode((char*)data,(*env)->GetArrayLength(env,data_));

    (*env)->ReleaseByteArrayElements(env, data_, data, 0);

    return (*env)->NewStringUTF(env, enbuf);
}