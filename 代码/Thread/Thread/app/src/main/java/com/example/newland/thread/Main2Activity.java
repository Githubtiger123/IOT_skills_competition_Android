package com.example.newland.thread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.util.Timer;
import java.util.TimerTask;

public class Main2Activity extends AppCompatActivity implements View.OnClickListener {

    private int time = 10;
    private TextView tv_time;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        findViewById(R.id.btn_start).setOnClickListener(this);
        tv_time = findViewById(R.id.tv_time);
    }

    @Override
    public void onClick(View view) {



        timer.schedule(timerTask,0,1000);
    }

    Timer timer = new Timer();
    TimerTask timerTask = new TimerTask() {
        @Override
        public void run() {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        tv_time.setText(String.valueOf(time));
                        time--;
                        if(time<0){
                        timer.cancel();
                    }
                }
                });
            }
    };
}
