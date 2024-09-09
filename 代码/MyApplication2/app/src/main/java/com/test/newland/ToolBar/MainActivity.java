package com.test.newland.ToolBar;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu,menu);
        setIconsVisible(menu,true);
        return true;
    }

    /**
     * 解决不显示menu icon的问题
     * @param menu
     * @param flag
     */
    private void setIconsVisible(Menu menu, boolean flag) {
        //判断menu是否为空
        if(menu != null) {
            try {
                //如果不为空,就反射拿到menu的setOptionalIconsVisible方法
                Method method = menu.getClass().getDeclaredMethod("setOptionalIconsVisible", Boolean.TYPE);
                //暴力访问该方法
                method.setAccessible(true);
                //调用该方法显示icon
                method.invoke(menu, flag);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent intent = new Intent();
        switch (item.getItemId()){

            case R.id.setting:
                Toast.makeText(this,"打开设置",Toast.LENGTH_SHORT).show();

                Log.d("wang", String.valueOf(getClass()));
                intent.setClass(MainActivity.this,setting.class);
                startActivity(intent);
                break;
            case R.id.exit:
                Toast.makeText(this,"退出",Toast.LENGTH_SHORT).show();
                finish();
                break;
            case R.id.help:
                Toast.makeText(this,"打开帮助",Toast.LENGTH_SHORT).show();
                Log.d("wang", String.valueOf(getClass()));
                intent.setClass(this,help.class);
                startActivity(intent);
                break;
            case R.id.photo:
                Toast.makeText(this,"拍照",Toast.LENGTH_SHORT).show();
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
