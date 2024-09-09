package com.test.newland.jumpgetdata;

import android.app.Activity;
import android.content.Intent;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class SendActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView tv_receive;
    private EditText et_send;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_send);

        findViewById(R.id.btn_send).setOnClickListener(this);
        et_send = findViewById(R.id.et_send);
        tv_receive = findViewById(R.id.tv_receive);


    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        //if(requestCode == 1&&requestCode == Activity.RESULT_OK){

            Bundle bundle = data.getExtras();
            int data1 = bundle.getInt("data");
            tv_receive.setText(String.valueOf(data1));
        //}
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){

            case R.id.btn_send:
                String s = et_send.getText().toString();
                Intent intent = new Intent();
                intent.setClass(this,ReceiveActivity.class);
                Bundle bundle = new Bundle();
                bundle.putInt("data", Integer.parseInt(s));
                intent.putExtras(bundle);
                startActivityForResult(intent,1);
                break;
        }
    }
}
