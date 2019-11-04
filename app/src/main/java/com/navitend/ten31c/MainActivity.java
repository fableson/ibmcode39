package com.navitend.ten31c;

import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;


public class MainActivity extends AppCompatActivity {


    private final String tag = MainActivity.class.getSimpleName();
    private EditText etBarcode;
    private ImageView ivBarcode;
    private Button bBarcode;


// BEGIN NATIVE CODE RELATED
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();           // created by new application wizard
    public native void code39(String text,Bitmap bitmap);       // our function to generate code 3 of 9 bar code symbol

// END NATIVE CODE RELATED

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bBarcode = findViewById(R.id.bBarcode);

        bBarcode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String textOfInterest = "*" +etBarcode.getText().toString().toUpperCase()+"*";
                Log.i(tag,"clicked! [" + textOfInterest + "]");
                DisplayMetrics displayMetrics = new DisplayMetrics();
                getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
                int height = displayMetrics.heightPixels;
                int width = displayMetrics.widthPixels;
                Bitmap bitmapWip = Bitmap.createBitmap(width-20,100,Config.ALPHA_8);
                code39(textOfInterest,bitmapWip);
                ivBarcode.setImageBitmap(bitmapWip);
            }
        });
        etBarcode = findViewById(R.id.etBarcode);
        ivBarcode = findViewById(R.id.ivBarcode);

        // Example of a call to a native method
        //TextView tv = findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
    }


}
