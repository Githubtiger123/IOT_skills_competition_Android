package com.test.newland.jumpto;

import android.app.Application;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_jump).setOnClickListener(this);
        findViewById(R.id.btn_Int).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){

            case R.id.btn_jump:
                startActivity(new Intent(this,Main2Activity.class));
                break;
            case R.id.btn_Int:
                startActivity(new Intent(this,ActionUriActivity.class));
                break;
        }
    }
}
