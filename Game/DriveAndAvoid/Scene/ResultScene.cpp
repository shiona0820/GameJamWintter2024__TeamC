#include "ResultScene.h"
#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() : back_ground(NULL)
{

}

ResultScene::~ResultScene()
{

}

//初期化処理
void ResultScene::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/image/back.bmpがありません\n");
	}

}

//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,0))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);
	if (GameMainScene::Wineer == 1);
	switch (GameMainScene::Wineer)
	{
	case 1:
		DrawString(0, 0, "player1", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(0, 0, "player2", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(0, 0, "player3", GetColor(255, 255, 255));
		break;
	}
}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}
