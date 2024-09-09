package com.skillt4.newland.t4;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.nle.mylibrary.forUse.mdbus4150.MdBus4150SensorListener;
import com.nle.mylibrary.forUse.mdbus4150.Modbus4150;
import com.nle.mylibrary.forUse.zigbee.ZigBee;
import com.nle.mylibrary.transfer.ConnectResultListener;
import com.nle.mylibrary.transfer.DataBusFactory;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView tv_temp;
    private TextView tv_hum;
    private ZigBee zigBee;
    private Modbus4150 modbus4150;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_start).setOnClickListener(this);
        findViewById(R.id.btn_stop).setOnClickListener(this);

        tv_temp = findViewById(R.id.tv_temp);
        tv_hum = findViewById(R.id.tv_hum);

        zigBee = new ZigBee(DataBusFactory.newSocketDataBus("192.168.4.15", 6002), new ConnectResultListener() {
            @Override
            public void onConnectResult(boolean b) {

            }
        });

        modbus4150 = new Modbus4150(DataBusFactory.newSocketDataBus("192.168.4.15", 6001), new ConnectResultListener() {
            @Override
            public void onConnectResult(boolean b) {

            }
        });

        //Toolbar toolbar = findViewById(R.id.toolbar);
        //setSupportActionBar(toolbar);
    }

    Handler mhandler = new Handler();
    Runnable runnable = new Runnable() {
        @Override
        public void run() {

            mhandler.postDelayed(runnable,300);
            try {
                double[] vals  = zigBee.getTmpHum();
                String s = Arrays.toString(vals);
                tv_temp.setText("       "+vals[0] + "°C");
                tv_hum.setText("       "+vals[1] + "%rh");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    };

    @Override
    public void onClick(View view) {

        switch (view.getId()){

            case R.id.btn_start:
                mhandler.post(runnable);
                break;
            case R.id.btn_stop:
                mhandler.removeCallbacks(runnable);
                tv_temp.setText("       "+0.0 + "°C");
                tv_hum.setText("       "+0.0 + "%rh");
                break;
        }
    }
}
