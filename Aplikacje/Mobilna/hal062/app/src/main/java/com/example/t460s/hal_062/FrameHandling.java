package com.example.t460s.hal_062;


import android.support.v7.app.AppCompatActivity;

/**
 * Created by T460s on 18.03.2018.
 */

public class FrameHandling extends AppCompatActivity {

    HalAPP mAPP = HalAPP.getInstance();

    public void sendFrameChar(int tag, int length, char[] output) {  //metoda do wysyłania ramek charów

            String y = "#";
            byte[] z1 = y.getBytes();       //wysyłamy #
            mAPP.getBluetoothConnection().write(z1);
            z1[0] = (byte) tag;             // wysyłamy tag
            mAPP.getBluetoothConnection().write(z1);
            for (int i = 0; i < length; i++) {    // pętla wysyła po kolei wszystkie znaki z tablicy
                y = "" + output[i];
                z1 = y.getBytes();
                mAPP.getBluetoothConnection().write(z1);
            }
    }

    public void sendFrameInt(int tag, int length, int[] output) {    //metoda do wysyłania ramek intów

            String y = "#";
            byte[] z1 = y.getBytes();
            mAPP.getBluetoothConnection().write(z1);
            z1[0] = (byte) tag;
            mAPP.getBluetoothConnection().write(z1);
            for (int i = 0; i < length; i++) {
                z1[0] = (byte) output[i];
                mAPP.getBluetoothConnection().write(z1);
            }
    }
}