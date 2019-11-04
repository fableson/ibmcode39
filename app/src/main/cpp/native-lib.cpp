/*
 * Author:  Frank Ableson fableson@navitend.com
 *
 * Generates a Code39 barcode into an Android Bitmap
 *
 * Code 39 was developed by Dr. David Allais and Ray Stevens of Intermec in 1974.
 * https://en.wikipedia.org/wiki/Code_39#Code_39_mod_43
 *
 * Code adapted from https://www.codeproject.com/Articles/2434/Drawing-Barcodes-in-Windows-Part-1-Code-39
 *
 */

#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "barcodeme"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)



const char * getSequence(char charwewant);

extern "C" JNIEXPORT jstring JNICALL
Java_com_navitend_ten31c_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ woo hoo";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_navitend_ten31c_MainActivity_code39 (
        JNIEnv * env,
        jobject  obj /* this */,
        jstring dataToEncode,
        jobject bitmapbarcode) {

    AndroidBitmapInfo infobarcode;
    void *pixelsbarcode;
    uint8_t	*imagedata;
    int ret;
    int y;
    int x;
    const int NARROW = 1;
    const int WIDE = 3;

    LOGI("code39");
    const char * szData = env->GetStringUTFChars(dataToEncode,NULL) ;

   // LOGI("data to print [%s]",szData);

    if ((ret = AndroidBitmap_getInfo(env, bitmapbarcode, &infobarcode)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }


    if ((ret = AndroidBitmap_lockPixels(env, bitmapbarcode, &pixelsbarcode)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }


    imagedata = (uint8_t *) pixelsbarcode;
    int left = 20; // start here
    const char *p = szData; // walk the string via a pointer
    int k=0;
    while (*p != 0)
    {
        const char * pattern = getSequence(*p);
        if (pattern != NULL) {
            int thiswidth =  0;

            for (int k=0;k<4;k+=1) {
                LOGI("k is [%d]",k);
                // bar
                if (pattern[k*2] == 0) thiswidth = NARROW;
                if (pattern[k*2] == '1') thiswidth = WIDE;
                LOGI("thiswidth is [%d]\t[%d]",thiswidth,left);
                for (y=10;y<=infobarcode.height - 10 - 1;y++) {
                    for (x=left;x<(left+thiswidth);x++) {
                        *(imagedata + x + (y * infobarcode.width)) = 255;
                    }
                }
                left+=thiswidth;
                // space
                if (pattern[k*2+1] == '0') thiswidth = NARROW;
                if (pattern[k*2+1] == '1') thiswidth = WIDE;
                left += thiswidth;
                LOGI("thiswidth is [%d]\t[%d]",thiswidth,left);
            }
            // final bar
            if (pattern[8] == '0') thiswidth = NARROW;
            if (pattern[8] == '1') thiswidth = WIDE;
            LOGI("thiswidth is [%d]\t[%d]",thiswidth,left);
            for (y=10;y<=infobarcode.height - 10 - 1;y++) {
                for (x=left;x<(left+thiswidth);x++) {
                    *(imagedata + x + (y * infobarcode.width)) = 255;
                }
            }
            // inter character gap
            left += WIDE * 2;
        }
        p++;
    }
    AndroidBitmap_unlockPixels(env, bitmapbarcode);

}



const char * getSequence(char charwewant) {
    switch (charwewant) {
        case '*':
            return "010010100";
        case '-':
            return "010000101";
        case '.':
            return "110000100";
        case ' ':
            return "011000100";
        case '$':
            return "010101000";
        case '/':
            return "010100010";
        case '+':
            return "010001010";
        case '%':
            return "000101010";
        case 'A':
            return "100001001";
        case 'B':
            return "001001001";
        case 'C':
            return "101001000";
        case 'D':
            return "000011001";
        case 'E':
            return "100011000";
        case 'F':
            return "001011000";
        case 'G':
            return "000001101";
        case 'H':
            return "100001100";
        case 'I':
            return "001001100";
        case 'J':
            return "000011100";
        case 'K':
            return "100000011";
        case 'L':
            return "001000011";
        case 'M':
            return "101000010";
        case 'N':
            return "000010011";
        case 'O':
            return "100010010";
        case 'P':
            return "001010010";
        case 'Q':
            return "000000111";
        case 'R':
            return "100000110";
        case 'S':
            return "001000110";
        case 'T':
            return "000010110";
        case 'U':
            return "110000001";
        case 'V':
            return "011000001";
        case 'W':
            return "111000000";
        case 'X':
            return "010010001";
        case 'Y':
            return "110010000";
        case 'Z':
            return "011010000";
        case '0':
            return "000110100";
        case '1':
            return "100100001";
        case '2':
            return "001100001";
        case '3':
            return "101100000";
        case '4':
            return "000110001";
        case '5':
            return "100110000";
        case '6':
            return "001110000";
        case '7':
            return "000100101";
        case '8':
            return "100100100";
        case '9':
            return "001100100";
        default:
            return NULL;
    }
}
