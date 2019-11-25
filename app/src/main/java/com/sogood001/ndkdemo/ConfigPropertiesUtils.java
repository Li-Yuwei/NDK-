package com.sogood001.ndkdemo;

import android.content.Context;

import java.io.InputStream;
import java.util.Properties;

public class ConfigPropertiesUtils {
    private static Properties getProperties(Context c){
        Properties props = new Properties();
        try {
            //方法一：通过activity中的context攻取setting.properties的FileInputStream
//            InputStream in = c.getAssets().open("appConfig.properties");
            //方法二：通过class获取setting.properties的FileInputStream
            InputStream in = ConfigPropertiesUtils.class.getResourceAsStream("/config.properties");
            props.load(in);
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }


        System.out.println(props.getProperty("serverUrl"));
        return props;
    }

}
