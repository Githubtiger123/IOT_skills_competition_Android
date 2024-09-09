package com.test.newland.playerraw;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.SeekBar;
import android.widget.TextView;

public class SeekBarTest extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener {

    private TextView tv_textView;
    private SeekBar sb_seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_seek_bar_test);

        tv_textView = findViewById(R.id.tv_textView);
        sb_seekBar = findViewById(R.id.sb_seekBar);
        sb_seekBar.setOnSeekBarChangeListener(this);
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
        tv_textView.setText("数值范围0-100，当前值:"+i);
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }
}
