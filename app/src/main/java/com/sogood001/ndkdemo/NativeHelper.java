package com.sogood001.ndkdemo;

/**
 * Created by li-yuweii on 16-10-28.
 */

public class NativeHelper {

    static {
        //加载C代码库，库的名称必须是CMakeLists.txt中指定的名称
        System.loadLibrary("native-lib");
    }

    public static String getAppKeyFromC() {
        return getAppKey();
    }

    /**
     * 实现C语言的调用入口，需要C语言来实现
     *
     * @return
     */
    private static native String getAppKey();


    public static String getAppSecretFromC() {
        return getAppSecret();
    }
    /**
     * 调用C
     * @return
     */
    private static native String getAppSecret();


    /**
     * java向C传递参数有返回值
     * @param a
     * @param b
     * @return
     */
    public static native int add(int a,int b);

    /**
     * Java向C传递参数没有返回值
     * @param name
     */
    public static native void sayHello(String name);

    /**
     * 将图片颜色取反
     * @param colors
     * @param width
     * @param height
     * @return
     */
    public static native int[] convertBitmap(int[] colors,int width,int height);

    public static native String base64Encode(byte[] data);
    public static native String base64Decode(byte[] data);
}
