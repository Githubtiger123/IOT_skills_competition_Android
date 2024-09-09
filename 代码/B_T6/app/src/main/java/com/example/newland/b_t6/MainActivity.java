package com.example.newland.b_t6;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private SharedPreferences.Editor editor;
    private TextView tv_id;
    private TextView tv_name;
    private TextView tv_amount;
    private String CustA_id = "CustA_id";
    private String CustB_id = "CustB_id";
    private String CustC_id = "CustC_id";
    private String CustA_name = "CustA_name";
    private String CustB_name = "CustB_name";
    private String CustC_name = "CustC_name";
    private String CustA_amount = "CustA_amount";
    private String CustB_amount = "CustB_amount";
    private String CustC_amount = "CustC_amount";

    private String flag = "flag";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        initShared();
        initView();
    }

    private void initView() {

        tv_id = findViewById(R.id.tv_id);
        tv_name = findViewById(R.id.tv_name);
        tv_amount = findViewById(R.id.tv_amount);


    }

    private void initShared() {
        SharedPreferences preferences = getSharedPreferences("Config", Context.MODE_PRIVATE);
        editor = preferences.edit();
        editor.putString(CustA_id,"E2 00 00 1B 21 11 02 37 06 30 D6 6E");
        editor.putString(CustB_id,"E2 00 00 1B 21 10 02 32 22 90 CB E0");
        editor.putString(CustC_id,"E2 00 00 1B 21 10 01 58 22 90 80 7F");
        editor.putString(CustA_name,"客人A");
        editor.putString(CustB_name,"客人B");
        editor.putString(CustC_name,"客人C");
        editor.putString(CustA_amount,"35");
        editor.putString(CustB_amount,"26");
        editor.putString(CustC_amount,"50");
        editor.commit();

    }
}
