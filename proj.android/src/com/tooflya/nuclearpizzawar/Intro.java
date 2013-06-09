package com.tooflya.nuclearpizzawar;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.WindowManager;
import android.widget.VideoView;

public class Intro extends Activity {

	@SuppressLint("NewApi")
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		setContentView(R.layout.main);

		if (Build.VERSION.SDK_INT >= 11) {
			try {
				getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE);
			} catch (Exception ex) {
			}
		}

		VideoView videoView = (VideoView) findViewById(R.id.ViewVideo);
		videoView.setVideoURI(Uri.parse("android.resource://"
				+ getPackageName() + "/" + R.raw.intro));

		DisplayMetrics metrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metrics);
		android.widget.RelativeLayout.LayoutParams params = (android.widget.RelativeLayout.LayoutParams) videoView
				.getLayoutParams();
		params.width = metrics.widthPixels;
		params.height = metrics.heightPixels;
		params.leftMargin = 0;
		videoView.setLayoutParams(params);

		videoView
				.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
					@Override
					public void onCompletion(MediaPlayer mp) {
						Intent intent = new Intent(Intro.this, Game.class);
						intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
						((Activity) Intro.this).startActivity(intent);

						finish();
					}
				});

		videoView.setMediaController(null);
		videoView.requestFocus();
		videoView.start();
	}
}
