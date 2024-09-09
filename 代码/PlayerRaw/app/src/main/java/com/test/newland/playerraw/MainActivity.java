package com.test.newland.playerraw;

import android.content.Context;
import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, SeekBar.OnSeekBarChangeListener {

    private MediaPlayer mediaPlayer;
    private int currPosition;
    private ProgressBar pb_click;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_start).setOnClickListener(this);
        findViewById(R.id.btn_stop).setOnClickListener(this);
        findViewById(R.id.btn_pause).setOnClickListener(this);
        findViewById(R.id.btn_click).setOnClickListener(this);
        SeekBar sb_seekBar = findViewById(R.id.sb_seekBar);
        pb_click = findViewById(R.id.pb_click);
        sb_seekBar.setOnSeekBarChangeListener(this);

    }

    @Override
    public void onClick(View view) {

        switch (view.getId()){
            case R.id.btn_start:
                mediaPlayer = MediaPlayer.create(this, R.raw.test);
                mediaPlayer.start();
                if(currPosition!=0){
                    mediaPlayer.seekTo(currPosition);
                }
                break;
            case R.id.btn_stop:
                mediaPlayer.stop();
                break;
            case R.id.btn_pause:
                currPosition = mediaPlayer.getCurrentPosition();
                mediaPlayer.pause();
                break;
            case R.id.btn_click:
                pb_click.setProgress(pb_click.getProgress()+3);
                break;
        }
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

        Toast.makeText(this,"拖动点改变",Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        Toast.makeText(this,"按下",Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        Toast.makeText(this,"松开",Toast.LENGTH_SHORT).show();
    }
}
