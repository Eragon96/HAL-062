package com.example.t460s.hal_062;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;



import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by T460s on 27.03.2018.
 */

public class ArmControlScreen extends Activity {
    SeekBar seekBar1;
    SeekBar seekBar2;
    SeekBar seekBar3;
    SeekBar seekBar4;
    SeekBar seekBar5;
    SeekBar seekBar6;
    SeekBar seekBar7;
    Button switchToBluetooth;
    Button switchToEngines;
    FrameHandling mFrameHandling;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.armcontrol_activity);

        mFrameHandling = new FrameHandling();
        seekBar1 = (SeekBar) findViewById(R.id.Seekbar1);
        applySeekbar(seekBar1);
        seekBar2 = (SeekBar) findViewById(R.id.Seekbar2);
        applySeekbar(seekBar2);
        seekBar3 = (SeekBar) findViewById(R.id.Seekbar3);
        applySeekbar(seekBar3);
        seekBar4 = (SeekBar) findViewById(R.id.Seekbar4);
        applySeekbar(seekBar4);
        seekBar5 = (SeekBar) findViewById(R.id.Seekbar5);
        applySeekbar(seekBar5);
        seekBar6 = (SeekBar) findViewById(R.id.Seekbar6);
        applySeekbar(seekBar6);
        seekBar7 = (SeekBar) findViewById(R.id.Seekbar7);
        applySeekbar(seekBar7);
        switchToBluetooth = (Button) findViewById(R.id.switchToBluetooth);
        switchToEngines = (Button) findViewById(R.id.switchToEngines);
        final Timer t = new Timer();

        t.scheduleAtFixedRate(new TimerTask() {
                                  @Override
                                  public void run() {
                                      if (HalAPP.getConnectionStatus() == 1) {
                                          mFrameHandling.sendFrameInt(100,7,ArmValue.values);
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
        switchToEngines.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchEngineControlActivity();
            }
        });

        seekBar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(0,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(0,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(1,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar3.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(2,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar4.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(3,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar5.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(4,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar6.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(5,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });

        seekBar7.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ArmValue.setValue(6,progress - 100);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(100);
            }
        });
    }
    private void launchMainActivity() {

        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
    private void launchEngineControlActivity() {

        Intent intent = new Intent(this, EngineControlScreen.class);
        startActivity(intent);
    }
    private void applySeekbar(SeekBar Bar){
        Bar.setProgress(100);
        Bar.incrementProgressBy(1);
        Bar.setMax(200);
    }
}

