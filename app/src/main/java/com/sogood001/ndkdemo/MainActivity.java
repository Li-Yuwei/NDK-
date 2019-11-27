package com.sogood001.ndkdemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.util.Properties;

public class MainActivity extends AppCompatActivity {

    private ImageView mImageView;
    private EditText mEditText;
    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mImageView = (ImageView) findViewById(R.id.main_image);
        mEditText = (EditText) findViewById(R.id.main_edit);
        mTextView = (TextView) findViewById(R.id.main_text);
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        Properties properties = ConfigPropertiesUtils.getProperties(this);
        ConfigPropertiesUtils.getLocalProperties(this);

    }

    public void btnGetKey(View view) {
        String appKey = NativeHelper.getAppKeyFromC();
        String appSecret = NativeHelper.getAppSecretFromC();

        Log.d("JNI", "Key: " + appKey);
        Log.d("JNI", "Secret: " + appSecret);
        NativeHelper.sayHello("hahahahahaha");
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    public void btnImage(View view) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.ic_launcher);
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int i = width * height;
        int[] color = new int[i];
        //将图片的像素值写入到数组中
        bitmap.getPixels(color, 0, width, 0, 0, width, height);
        color = NativeHelper.convertBitmap(color, width, height);
        bitmap.recycle();
        Bitmap newBitmap = Bitmap.createBitmap(color, width, height, Bitmap.Config.ARGB_8888);
        mImageView.setImageBitmap(newBitmap);

    }

    public void btnEncode(View view) {

        String s = mEditText.getText().toString().trim();
            String encode = null;
            try {
                encode = NativeHelper.base64Encode(s.getBytes("utf-8"));
                mTextView.setText(encode);
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
    }

    public void btnDecode(View view) {
        String s = mTextView.getText().toString();
        try {
            String decode = NativeHelper.base64Decode(s.getBytes("utf-8"));
            mTextView.setText(decode);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
}
