package com.tooflya.nuclearpizzawar;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;

public class Game extends Cocos2dxActivity {

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	private native void showAds();
	private native void hideAds();

	static {
		System.loadLibrary("game");
	}
}
