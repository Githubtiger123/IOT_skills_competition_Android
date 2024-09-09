package com.test.newland.jump_data;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class SendActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText et_send;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_send);

        et_send = findViewById(R.id.et_send);
        findViewById(R.id.btn_send).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){

            case R.id.btn_send:
                String s = et_send.getText().toString();
                Intent intent = new Intent();
                intent.setClass(this,ReceiveActivity.class);
                Bundle bundle = new Bundle();
                bundle.putString("data",s);
                intent.putExtras(bundle);
                startActivity(intent);
                break;
        }
    }
}
