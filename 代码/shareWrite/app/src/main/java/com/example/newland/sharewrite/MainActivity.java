package com.example.newland.sharewrite;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText et_age;
    private EditText et_name;
    private EditText et_height;
    private EditText et_weight;
    private SharedPreferences preferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        et_age = findViewById(R.id.et_age);
        et_name = findViewById(R.id.et_name);
        et_height = findViewById(R.id.et_height);
        et_weight = findViewById(R.id.et_weight);

        findViewById(R.id.btn_ok).setOnClickListener(this);

        preferences = getSharedPreferences("Config", Context.MODE_PRIVATE);
        
        reload();

    }

    private void reload() {

        String name = preferences.getString("name","");
        int age = preferences.getInt("age",0);
        float weight = preferences.getFloat("weight",0);
        float height = preferences.getFloat("height",0);

        et_name.setText(name);
        et_age.setText(age);
        et_weight.setText(String.valueOf(weight));
        et_height.setText(String.valueOf(height));
    }

    @Override
    public void onClick(View view) {

        String name = et_name.getText().toString();
        String age = et_age.getText().toString();
        String weight = et_weight.getText().toString();
        String height = et_height.getText().toString();

        SharedPreferences.Editor edit = preferences.edit();
        edit.putString("name",name);
        edit.putInt("age", Integer.parseInt(age));
        edit.putFloat("weight", Float.parseFloat(weight));
        edit.putFloat("height", Float.parseFloat(height));

        edit.commit();

        Toast.makeText(MainActivity.this,"保存成功",Toast.LENGTH_SHORT).show();
    }
}
