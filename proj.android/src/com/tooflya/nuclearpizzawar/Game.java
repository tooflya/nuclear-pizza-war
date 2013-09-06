package com.tooflya.nuclearpizzawar;

import java.util.ArrayList;
import java.util.List;

import android.annotation.SuppressLint;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.google.android.gms.common.SignInButton;
import com.google.android.gms.games.GamesClient;
import com.google.android.gms.games.multiplayer.Invitation;
import com.google.android.gms.games.multiplayer.OnInvitationReceivedListener;
import com.google.android.gms.games.multiplayer.Participant;
import com.google.android.gms.games.multiplayer.realtime.RealTimeMessage;
import com.google.android.gms.games.multiplayer.realtime.RealTimeMessageReceivedListener;
import com.google.android.gms.games.multiplayer.realtime.Room;
import com.google.android.gms.games.multiplayer.realtime.RoomConfig;
import com.google.android.gms.games.multiplayer.realtime.RoomStatusUpdateListener;
import com.google.android.gms.games.multiplayer.realtime.RoomUpdateListener;

public class Game extends BaseGameActivity implements
		GameHelper.GameHelperListener, RealTimeMessageReceivedListener,
		RoomStatusUpdateListener, RoomUpdateListener, OnInvitationReceivedListener {

	// Room ID where the currently active game is taking place; null if we're
	// not playing.
	String mRoomId = null;

	// Are we playing in multiplayer mode?
	boolean mMultiplayer = false;

	// The participants in the currently active game
	ArrayList<Participant> mParticipants = null;

	// My participant ID in the currently active game
	String mMyId = null;

	@SuppressLint("NewApi")
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		if (Build.VERSION.SDK_INT >= 11) {
			try {
				getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE);
			} catch (Exception ex) {
			}
		}

		setSignInMessages(getString(R.string.signing_in), getString(R.string.signing_out));
		setUnknownErrorMessage(getString(R.string.unknown_error));
	}

	private native void showAds();

	private native void hideAds();

	private native void nativeOnGooglePlusSignInSucceeded();

	private native void nativeOnGooglePlusConnedctedToRoom();

	private native void nativeOnGooglePlusRealtimeMessageReceived(int param1, int param2, int param3, int param4);

	static {
		System.loadLibrary("game");
	}

	@Override
	public void onSignInFailed() {
		if (mSignInButton == null)
			runOnUiThread(new Runnable() {
				public void run() {
					RelativeLayout.LayoutParams options = new RelativeLayout.LayoutParams(
							RelativeLayout.LayoutParams.WRAP_CONTENT,
							RelativeLayout.LayoutParams.WRAP_CONTENT);

					options.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
					options.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);

					mSignInButton = new SignInButton(Game.this);
					mSignInButton.setOnClickListener(Game.this);
					mLayout.addView(mSignInButton, options);
				}
			});
	}

	@Override
	public void onSignInSucceeded() {
		System.out.println("SIGN IN :).");

		if (mSignInButton != null) {
			mSignInButton.setVisibility(View.GONE);
		}

		getGamesClient().registerInvitationListener(this);

		if (getInvitationId() != null) {
			// acceptInviteToRoom(getInvitationId());

			return;
		}

		nativeOnGooglePlusSignInSucceeded();
		//startQuickGame();
	}

	@Override
	void startQuickGame() {
		System.out.println("STARTED QUICK GAME");
		final int MIN_OPPONENTS = 1, MAX_OPPONENTS = 1;
		Bundle autoMatchCriteria = RoomConfig.createAutoMatchCriteria(MIN_OPPONENTS, MAX_OPPONENTS, 0);
		RoomConfig.Builder rtmConfigBuilder = RoomConfig.builder(this);
		rtmConfigBuilder.setMessageReceivedListener(this);
		rtmConfigBuilder.setRoomStatusUpdateListener(this);
		rtmConfigBuilder.setAutoMatchCriteria(autoMatchCriteria);
		//switchToScreen(R.id.screen_wait);
		getGamesClient().createRoom(rtmConfigBuilder.build());
	}

	@Override
	public void onInvitationReceived(Invitation invitation) {
	}

	@Override
	public void onJoinedRoom(int statusCode, Room room) {
		System.out.println("onJoinedRoom(" + statusCode + ", " + room + ")");
		if (statusCode != GamesClient.STATUS_OK) {
			System.out.println("*** Error: onRoomConnected, status " + statusCode);
			//showGameError();
			return;
		}

		//showWaitingRoom(room);
	}

	@Override
	public void onLeftRoom(int statusCode, String roomId) {
		System.out.println("onLeftRoom, code " + statusCode);
		//switchToMainScreen();
	}

	@Override
	public void onRoomConnected(int statusCode, Room room) {
		System.out.println("onRoomConnected(" + statusCode + ", " + room + ")");
		if (statusCode != GamesClient.STATUS_OK) {
			System.out.println("*** Error: onRoomConnected, status " + statusCode);
			//showGameError();
			return;
		}
		updateRoom(room);
	}

	@Override
	public void onRoomCreated(int statusCode, Room room) {
		System.out.println("onRoomCreated(" + statusCode + ", " + room + ")");
		if (statusCode != GamesClient.STATUS_OK) {
			System.out.println("*** Error: onRoomCreated, status " + statusCode);
			//showGameError();
			return;
		}

		//showWaitingRoom(room);
	}

	@Override
	public void onConnectedToRoom(Room room) {
		System.out.println("onConnectedToRoom.");

		mRoomId = room.getRoomId();
		mParticipants = room.getParticipants();
		mMyId = room.getParticipantId(getGamesClient().getCurrentPlayerId());

		System.out.println("Room ID: " + mRoomId);
		System.out.println("My ID " + mMyId);
		System.out.println("<< CONNECTED TO ROOM>>");

		nativeOnGooglePlusConnedctedToRoom();
	}

	@Override
	public void onDisconnectedFromRoom(Room room) {
		mRoomId = null;
		//showGameError();
	}

	@Override
	public void onPeerDeclined(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onPeerInvitedToRoom(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onPeerJoined(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onPeerLeft(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onPeersConnected(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onPeersDisconnected(Room room, List<String> arg1) {
		updateRoom(room);
	}

	@Override
	public void onRoomAutoMatching(Room room) {
		updateRoom(room);
	}

	@Override
	public void onRoomConnecting(Room room) {
		updateRoom(room);
	}

	void updateRoom(Room room) {
		mParticipants = room.getParticipants();
		//updatePeerScoresDisplay();
	}

	@Override
	public void onRealTimeMessageReceived(RealTimeMessage message) {
		byte[] buf = message.getMessageData();

		nativeOnGooglePlusRealtimeMessageReceived(buf[0], buf[1], buf[2], buf[3]);
	}

	// Message buffer for sending messages
	byte[] mMsgBuf = new byte[4];

	@Override
	public void broadcastMessage(int param1, int param2, int param3, int param4) {
		mMsgBuf[0] = (byte) param1;
		mMsgBuf[1] = (byte) param2;
		mMsgBuf[2] = (byte) param3;
		mMsgBuf[3] = (byte) param4;

		for (Participant p : mParticipants) {
			if (p.getParticipantId().equals(mMyId)) {
				continue;
			}
			if (p.getStatus() != Participant.STATUS_JOINED) {
				continue;
			}

			getGamesClient().sendReliableRealTimeMessage(null, mMsgBuf, mRoomId, p.getParticipantId());
		}
	}
}
