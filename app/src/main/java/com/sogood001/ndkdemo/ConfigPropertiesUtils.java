package com.sogood001.ndkdemo;

import android.content.Context;
import android.util.Log;

import java.io.InputStream;
import java.util.Properties;

public class ConfigPropertiesUtils {
    public static Properties getProperties(Context c){
        Properties props = new Properties();
        try {
            //方法一：通过activity中的context攻取setting.properties的FileInputStream
            InputStream in = c.getAssets().open("config.properties");
            //方法二：通过class获取setting.properties的FileInputStream

//            InputStream in = ConfigPropertiesUtils.class.getResourceAsStream("/config.properties");
            props.load(in);
            Log.e("LYW", "getProperties:1 "  + props.getProperty("serverUrl"));

        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }

//        System.out.println();
        return props;
    }


    public static Properties getLocalProperties(Context c){
        Properties props = new Properties();
        try {
            //方法一：通过activity中的context攻取setting.properties的FileInputStream
//            InputStream in = c.getAssets().open("appConfig.properties");
            //方法二：通过class获取setting.properties的FileInputStream
            InputStream in = ConfigPropertiesUtils.class.getResourceAsStream("/local.properties");
            props.load(in);
            Log.e("LYW", "getProperties:2 "  + props.getProperty("sdk.dir"));
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }

//        System.out.println();
        return props;
    }
}
