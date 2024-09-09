package com.example.newland.dlgtest;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MyDialog extends Dialog implements View.OnClickListener {//创建一个继承Dialog类的类

    private Button btn_ok;
    private Button btn_cancel;
    private TextView tv_title;
    private TextView tv_content;
    private String content;//设置自定义提示的文字
    private String title;//设置自定义提示的标题

    public MyDialog(Context context) {//重写父类构造器
        super(context);
    }

    //设置自定义提示的文字 set构造方法用于别的类设置
    public void setContent(String content) {
        this.content = content;
    }

    //设置自定义提示的标题 set构造方法用于别的类设置
    public void settitle(String title) {
        this.title = title;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_dialog);
        //初始化空间
        initView();
        //设置标题

        tv_title.setText(title);//设置自定义提示的标题
        tv_content.setText(content);//设置自定义提示的文字

    }

    //初始化控件
    private void initView() {
        tv_content = findViewById(R.id.tv_content);
        tv_title = findViewById(R.id.tv_title);
        btn_cancel = findViewById(R.id.btn_Cancel);
        btn_ok = findViewById(R.id.btn_Ok);

        btn_ok.setOnClickListener(this);
        btn_cancel.setOnClickListener(this);
    }

    //实现点击按钮的方法
    @Override
    public void onClick(View view) {
        switch (view.getId()){

            case R.id.btn_Ok:
                //点击确定时的操作
                Toast.makeText(getContext(),"点击确定",Toast.LENGTH_SHORT).show();
                dismiss();//关闭对话框
                break;
            case R.id.btn_Cancel:
                dismiss();//关闭对话框
                break;
        }
    }
}
