package com.test.newland.jump_data;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ReceiveActivity extends AppCompatActivity {

    private TextView tv_receive;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receive);

        tv_receive = findViewById(R.id.tv_receive);

        Bundle bundle = getIntent().getExtras();
        String data = bundle.getString("data");
        tv_receive.setText(data);
    }
}
