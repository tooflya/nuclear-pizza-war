package com.tooflya.nuclearpizzawar;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.annotation.SuppressLint;
import android.os.Build;
import android.os.Bundle;
import android.view.View;

public class Game extends Cocos2dxActivity {

	@SuppressLint("NewApi")
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		if (Build.VERSION.SDK_INT >= 11) {
			try {
				getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE);
			} catch (Exception ex) {
			}
		}
	}

	private native void showAds();

	private native void hideAds();

	static {
		System.loadLibrary("game");
	}
}
