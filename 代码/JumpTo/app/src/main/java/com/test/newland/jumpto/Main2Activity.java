package com.test.newland.jumpto;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class Main2Activity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        findViewById(R.id.btn_finish).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        finish();
    }
}
