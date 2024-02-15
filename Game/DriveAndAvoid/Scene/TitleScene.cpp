#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.png");
	menu_image = LoadGraph("Resource/images/menu.png");
	cursor_image = LoadGraph("Resource/images/cone.bmp");
	end_image = LoadGraph("Resource/images/End.png");

	//BGMの読み込み
	title_sound = LoadSoundMem("Resource/sound/Roll_Crash.mp3");
	button_sound = LoadSoundMem("Resource/sound/button.mp3");
	buttonON_sound = LoadSoundMem("Resource/sound/buttonON.mp3");
	buttonNO_sound = LoadSoundMem("Resource/sound/buttonNO.mp3");
	//BGMの音量設定
	ChangeVolumeSoundMem(255 * 80 / 150, title_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, button_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, buttonON_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, buttonNO_sound);

	end_cun = 0;
	end = false;

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{

	if (end == false)
	{


		//bgmが流れていないときに再生
		if (CheckSoundMem(title_sound) != TRUE)
		{
			PlaySoundMem(title_sound, DX_PLAYTYPE_BACK, TRUE);
		}



		//カーソル下移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN, 0))
		{
			PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);

			menu_cursor++;
			//1番下に到達したら、１番上にする
			if (menu_cursor > 2)
			{
				menu_cursor = 0;
			}
		}

		//カーソル上移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP, 0))
		{
			PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);

			menu_cursor--;
			//1番上に到達したら、１番下にする
			if (menu_cursor < 0)
			{
				menu_cursor = 2;
			}
		}

		//カーソル決定（決定した画面に遷移する）
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B, 0))
		{
			switch (menu_cursor)
			{
			case 0:
				PlaySoundMem(buttonON_sound, DX_PLAYTYPE_BACK, TRUE);
				StopSoundMem(title_sound);
				return eSceneType::E_MAIN;
			case 1:
				PlaySoundMem(buttonON_sound, DX_PLAYTYPE_BACK, TRUE);
				return eSceneType::E_HELP;
			default:
				end = true;
			}
		}

	}
	else
	{

		end_cun++;
		if (end_cun == 130)
		{
			return eSceneType::E_END;
		}
		
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{


	//タイトル画面の描画
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	//メニュー画面の描画
	DrawGraph(150, 300, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(110, 340 + menu_cursor * 90, 0.7, DX_PI / 2.0, cursor_image, TRUE);

	if (end == true)
	{
		DrawGraph(0, 0, end_image, TRUE);

	}
}

//終了処理
void TitleScene::Finalize()
{

	DeleteSoundMem(button_sound);
	DeleteSoundMem(buttonON_sound);
	DeleteSoundMem(buttonNO_sound);

	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}