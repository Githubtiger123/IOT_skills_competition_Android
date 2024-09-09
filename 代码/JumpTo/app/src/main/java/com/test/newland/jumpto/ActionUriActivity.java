package com.test.newland.jumpto;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class ActionUriActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_action_uri);

        findViewById(R.id.btn_dial).setOnClickListener(this);
        findViewById(R.id.btn_sms).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        String PhoneNumber = "1234567890";

        switch (view.getId()){

            case R.id.btn_dial:
                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_DIAL);
                Uri u = Uri.parse("tel:"+PhoneNumber);
                intent.setData(u);
                startActivity(intent);
                break;
            case R.id.btn_sms:
                break;
        }
    }
}
