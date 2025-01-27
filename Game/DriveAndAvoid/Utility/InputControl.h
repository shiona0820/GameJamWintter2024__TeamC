#pragma once

#include"Vector2D.h"

//入力値管理機能
class InputControl
{
private:
	static bool now_button[16];       //現在フレーム入力値
	static bool old_button[16];       //過去フレーム入力値
	static float trigger[2];          //左右トリガー入力値
	static Vector2D stick[2];         //左右スティック入力値

	static bool now_button2[16];       //現在フレーム入力値
	static bool old_button2[16];       //過去フレーム入力値
	static float trigger2[2];          //左右トリガー入力値
	static Vector2D stick2[2];         //左右スティック入力値

	static bool now_button3[16];       //現在フレーム入力値
	static bool old_button3[16];       //過去フレーム入力値
	static float trigger3[2];          //左右トリガー入力値
	static Vector2D stick3[2];         //左右スティック入力値

	static bool now_button4[16];       //現在フレーム入力値
	static bool old_button4[16];       //過去フレーム入力値
	static float trigger4[2];          //左右トリガー入力値
	static Vector2D stick4[2];         //左右スティック入力値

public:
	static void Update();             //更新処理


	//ボタン入力取得処理
	static bool GetButton(int button,int cnum);   //押し続ける間
	static bool GetButtonDown(int button,int cnum);   //離した瞬間
	static bool GetButtonUp(int button,int cnum);     //離した瞬間

	//トリガー入力取得処理
	static float GetLeftTrigger();            //左トリガー
	static float GetRightTrigger();           //右トリガー

	//スティック入力値処理
	static Vector2D GetLeftStick();         //左スティック
	static Vector2D GetRightStick();        //右スティック

private:
	//ボタン配列範囲チェック
	static bool CheckButtonRange(int button);
};