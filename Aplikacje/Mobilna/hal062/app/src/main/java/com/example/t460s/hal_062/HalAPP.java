package com.example.t460s.hal_062;

import android.app.Application;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.WindowManager;

import java.io.IOException;
import java.util.UUID;


/**
 * Created by T460s on 25.03.2018.
 */

public class HalAPP extends Application {
    private BluetoothConnectionService mBluetoothConnection;
    private BluetoothDevice mBluetoothDevice;
    private static final UUID MY_UUID_INSECURE =
            UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static HalAPP singleton;
    private static int connectionStatus = 0; // zmienna odpowiadająca za możliwość wysyłania

    public static HalAPP getInstance(){
        return singleton;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        singleton = this;
    }

    public static int getConnectionStatus() {
        return connectionStatus;
    }

    public static void setConnectionStatus(int connection) {
        HalAPP.connectionStatus = connection;
    }

    public BluetoothConnectionService getBluetoothConnection() {
        return mBluetoothConnection;
    }

    public void startBTConnectionService(Context context){
        mBluetoothConnection = new BluetoothConnectionService(context);
    }

    public void setBluetoothDevice(BluetoothDevice mBluetoothDevice) {
        this.mBluetoothDevice = mBluetoothDevice;
    }

    public BluetoothDevice getBluetoothDevice() {
        return mBluetoothDevice;
    }

    public void startBTConnection(){
        mBluetoothConnection.startClient(mBluetoothDevice,MY_UUID_INSECURE);
    }

    public void cancel(){
        mBluetoothConnection.cancel();
    }
}
