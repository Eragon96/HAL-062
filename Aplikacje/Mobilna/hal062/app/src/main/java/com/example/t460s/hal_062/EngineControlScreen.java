package com.example.t460s.hal_062;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


import java.util.Timer;
import java.util.TimerTask;

import io.github.controlwear.virtual.joystick.android.JoystickView;

/**
 * Created by T460s on 16.03.2018.
 */


public class EngineControlScreen extends Activity{

    Button engineOn;
    Button engineOff;
    TextView textViewX;
    TextView textViewY;
    Button switchToBluetooth;
    Button switchToArm;
    FrameHandling mFrameHandling;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.enginecontrol_activity);

        mFrameHandling = new FrameHandling();
        engineOn = (Button) findViewById(R.id.engineOn);
        engineOff = (Button) findViewById(R.id.engineOff);
        switchToBluetooth = (Button) findViewById(R.id.switchToBluetooth);
        switchToArm = (Button) findViewById(R.id.switchToArm);
        textViewY = (TextView) findViewById(R.id.textViewY);
        textViewX = (TextView) findViewById(R.id.textViewX);
        JoystickView joystick = (JoystickView) findViewById(R.id.joystickView);
        final Timer t = new Timer();



        engineOn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(mFrameHandling != null){
                    char[] charTab = {'1'};
                    mFrameHandling.sendFrameChar(101,1,charTab);
                }
            }
        });
        engineOff.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(mFrameHandling != null){
                    char[] charTab = {'0'};
                    mFrameHandling.sendFrameChar(101,1,charTab);
                }
            }
        });
        t.scheduleAtFixedRate(new TimerTask() {
                                  @Override
                                  public void run() {
                                      if (HalAPP.getConnectionStatus() == 1) {
                                          int[] outputTab = {JoystickValue.joystickX,JoystickValue.joystickY};
                                          mFrameHandling.sendFrameInt(100,2,outputTab);
                                      }
                                  }
                              },//Set how long before to start calling the TimerTask (in milliseconds)
                0,
                //Set the amount of time between each execution (in milliseconds)
                100);

        switchToBluetooth.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchMainActivity();
            }
        });

        switchToArm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchArmcontrolScreen();
            }
        });

        joystick.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                int x = - (int) ( (double) strength * Math.sin( (double) angle * 6.28 / 360.0 ));
                int y = (int) ( (double) strength * Math.cos( (double) angle * 6.28 / 360.0 ));
                textViewX.setText("x = " + x);
                textViewY.setText("y = " + y);
                JoystickValue.setX(x);
                JoystickValue.setY(y);
            }
        });
    }
    private void launchMainActivity() {

        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }

    private void launchArmcontrolScreen() {

        // Intent intent = new Intent(this, ArmControlScreen.class);
        // startActivity(intent);
    }
}
