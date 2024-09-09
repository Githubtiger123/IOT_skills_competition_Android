package com.test.newland.jumpgetdata;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class ReceiveActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView tv_receive;
    private int data;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receive);

        findViewById(R.id.btn_send).setOnClickListener(this);
        tv_receive = findViewById(R.id.tv_receive);

        Bundle bundle = getIntent().getExtras();
        data = bundle.getInt("data");
        tv_receive.setText(String.valueOf(data));
        data = data +100;
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){

            case R.id.btn_send:

                Bundle bundle = new Bundle();
                bundle.putInt("data",data);
                Intent intent = new Intent(this,SendActivity.class);
                intent.putExtras(bundle);
                setResult(Activity.RESULT_OK,intent);
                finish();
                break;
        }
    }
}
