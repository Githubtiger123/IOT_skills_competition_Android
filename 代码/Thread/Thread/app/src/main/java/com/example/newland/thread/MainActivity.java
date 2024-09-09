package com.example.newland.thread;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.health.TimerStat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView tv_textView;

    Handler mhandler = new Handler(Looper.myLooper()){

        @Override
        public void handleMessage(Message msg) {

            super.handleMessage(msg);
            if(msg.what == 0){
                String s = (String) msg.obj;
                tv_textView.setText("结果为"+s);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_time).setOnClickListener(this);
        tv_textView = findViewById(R.id.tv_textView);
    }

    private String waitFor(){

        String s = "1";
        for (int i = 0; i <6 ; i++) {

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            s=s+"0";
        }
        return s;
    }

    @Override
    public void onClick(View view) {

        Toast.makeText(this,"计算完成",Toast.LENGTH_SHORT).show();

        new Thread(new Runnable() {
            @Override
            public void run() {
                Message message = new Message();
                String s = waitFor();
                message.what = 0;
                message.obj = s;
                mhandler.sendMessage(message);


            }
        }).start();
    }
}
