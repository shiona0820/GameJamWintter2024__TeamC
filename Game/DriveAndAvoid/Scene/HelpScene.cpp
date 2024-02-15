#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene():help_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	help_image = LoadGraph("Resource/images/Help.png");

	//SEの読み込み
	buttonNO_sound = LoadSoundMem("Resource/sound/buttonNO.mp3");
	//音量設定
	ChangeVolumeSoundMem(255 * 80 / 100, buttonNO_sound);

	//エラーチェック
	if (help_image == -1)
	{
		throw("Resourse/images/Help.pngがありません\n");
	}
}

//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,0))
	{
		PlaySoundMem(buttonNO_sound, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, help_image, FALSE);

}

//終了時処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(help_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}