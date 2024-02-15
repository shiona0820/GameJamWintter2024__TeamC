#include"InputControl.h"
#include"DxLib.h"

//静的メンバ変数定義
bool InputControl::now_button[16] = {};
bool InputControl::old_button[16] = {};
float InputControl::trigger[2] = {};
Vector2D InputControl::stick[2] = {};

//PAD２
//静的メンバ変数定義
bool InputControl::now_button2[16] = {};
bool InputControl::old_button2[16] = {};
float InputControl::trigger2[2] = {};
Vector2D InputControl::stick2[2] = {};

//PAD3
//静的メンバ変数定義
bool InputControl::now_button3[16] = {};
bool InputControl::old_button3[16] = {};
float InputControl::trigger3[2] = {};
Vector2D InputControl::stick3[2] = {};


//入力機能：更新処理
void InputControl::Update()
{
	//XInputコントローラーの入力値を取得する
	XINPUT_STATE input_state = {};
	XINPUT_STATE input_state2 = {};
	XINPUT_STATE input_state3 = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);
	GetJoypadXInputState(DX_INPUT_PAD2, &input_state2);
	GetJoypadXInputState(DX_INPUT_PAD3, &input_state3);

	//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	//トリガー入力値の更新（0.0ｆ～1.0ｆに範囲を制限する）
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新（-1.0ｆ～1.0ｆに範囲を制限する）
	if (input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
	}

	//右スティック入力値の更新（-1.0～1.0fに範囲を制限する）
	if (input_state.ThumbRX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state.ThumbRY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
	}


	/*パッド２*/

		//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button2[i] = now_button2[i];
		now_button2[i] = (bool)input_state2.Buttons[i];
	}

	//トリガー入力値の更新（0.0ｆ～1.0ｆに範囲を制限する）
	trigger2[0] = (float)input_state2.LeftTrigger / (float)UCHAR_MAX;
	trigger2[1] = (float)input_state2.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新（-1.0ｆ～1.0ｆに範囲を制限する）
	if (input_state2.ThumbLX > 0.0f)
	{
		stick2[0].x = (float)input_state2.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick2[0].x = -((float)input_state2.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state2.ThumbLY > 0.0f)
	{
		stick2[0].y = (float)input_state2.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick2[0].y = -((float)input_state2.ThumbLY / (float)SHRT_MIN);
	}

	//右スティック入力値の更新（-1.0～1.0fに範囲を制限する）
	if (input_state2.ThumbRX > 0.0f)
	{
		stick2[1].x = (float)input_state2.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick2[1].x = -((float)input_state2.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state2.ThumbRY > 0.0f)
	{
		stick2[1].y = (float)input_state2.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick2[1].y = -((float)input_state2.ThumbRY / (float)SHRT_MIN);
	}


	/*Pad3*/

		//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button3[i] = now_button3[i];
		now_button3[i] = (bool)input_state3.Buttons[i];
	}

	//トリガー入力値の更新（0.0ｆ～1.0ｆに範囲を制限する）
	trigger3[0] = (float)input_state3.LeftTrigger / (float)UCHAR_MAX;
	trigger3[1] = (float)input_state3.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新（-1.0ｆ～1.0ｆに範囲を制限する）
	if (input_state3.ThumbLX > 0.0f)
	{
		stick3[0].x = (float)input_state3.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick3[0].x = -((float)input_state3.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state3.ThumbLY > 0.0f)
	{
		stick3[0].y = (float)input_state3.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick3[0].y = -((float)input_state3.ThumbLY / (float)SHRT_MIN);
	}

	//右スティック入力値の更新（-1.0～1.0fに範囲を制限する）
	if (input_state3.ThumbRX > 0.0f)
	{
		stick3[1].x = (float)input_state3.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick3[1].x = -((float)input_state3.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state3.ThumbRY > 0.0f)
	{
		stick3[1].y = (float)input_state3.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick3[1].y = -((float)input_state3.ThumbRY / (float)SHRT_MIN);
	}


}

//ボタン取得：押してる間
bool InputControl::GetButton(int button,int cnum)
{


	switch (cnum)
	{
	case 0:
		return CheckButtonRange(button) && (now_button[button] && old_button[button]);
		break;
	case 1:
		return CheckButtonRange(button) && (now_button2[button] && old_button2[button]);
		break;
	case 2:
		return CheckButtonRange(button) && (now_button3[button] && old_button3[button]);
		break;
	default:
		break;
	}

}

//ボタン取得：押した瞬間
bool InputControl::GetButtonDown(int button,int cnum)
{

	switch (cnum)
	{
	case 0:
		return CheckButtonRange(button) && (now_button[button] && !old_button[button]);

		break;
	case 1:
		return CheckButtonRange(button) && (now_button2[button] && !old_button2[button]);

		break;
	case 2:
		return CheckButtonRange(button) && (now_button3[button] && !old_button3[button]);

		break;
	default:
		break;
	}
}

//ボタン取得：離した瞬間
bool InputControl::GetButtonUp(int button, int cnum)
{
	//if (cnum == 0)
	//{
	//	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
	//}
	//else if (cnum == 1)
	//{
	//	return CheckButtonRange(button) && (!now_button2[button] && old_button2[button]);
	//}

	switch (cnum)
	{
	case 0:
		return CheckButtonRange(button) && (now_button[button] && !old_button[button]);

		break;
	case 1:
		return CheckButtonRange(button) && (now_button2[button] && !old_button2[button]);

		break;
	case 2:
		return CheckButtonRange(button) && (now_button3[button] && !old_button3[button]);

		break;
	default:
		break;
	}

}

//左トリガー取得
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

//右トリガー取得
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

//左スティック取得
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

//右スティック取得
Vector2D InputControl::GetRightStick()
{
	return stick[1];
}

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}
