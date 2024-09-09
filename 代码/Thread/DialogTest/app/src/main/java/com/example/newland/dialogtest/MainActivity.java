package com.example.newland.dialogtest;

import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_ShowMsgDlg).setOnClickListener(this);
        findViewById(R.id.btn_ShowSingleDlg).setOnClickListener(this);
        findViewById(R.id.btn_ShowMultiDlg).setOnClickListener(this);
        findViewById(R.id.btn_ShowCustomDlg).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){
            case R.id.btn_ShowMsgDlg:
                ShowMsgDlg();
                break;
            case R.id.btn_ShowSingleDlg:
                ShowSingleDlg();
                break;
            case R.id.btn_ShowMultiDlg:
                ShowMultiDlg();
                break;
            case R.id.btn_ShowCustomDlg:
                ShowCustomDlg();
                break;
        }
    }

    private void ShowCustomDlg() {

    }

    private void ShowMsgDlg() {

        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);//创建AlertDialog类中内部类Builder的对象 传参数上下文
        builder.setTitle("提示信息对话框");//设置标题
        builder.setMessage("是否确定退出！");//设置提示信息
        builder.setIcon(R.mipmap.ic_launcher);//设置图标
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {//设置确定按钮（肯定回答） 与setNegativeButton相对
            @Override                                                                  //参数是按钮的提示信息和点击回调方法
            public void onClick(DialogInterface dialogInterface, int i) {
                //添加处理代码
                Toast.makeText(MainActivity.this,"退出",Toast.LENGTH_SHORT).show();
                finish();
            }
        });
        builder.setNeutralButton("进来看看", new DialogInterface.OnClickListener() {//中性回答
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                //添加处理代码
                Toast.makeText(MainActivity.this,"点进来看看",Toast.LENGTH_SHORT).show();
            }
        });
        builder.setNegativeButton("取消",null);//否定回答
        builder.show();
    }

    private void ShowMultiDlg() {

    }

    private void ShowSingleDlg() {

    }

}
