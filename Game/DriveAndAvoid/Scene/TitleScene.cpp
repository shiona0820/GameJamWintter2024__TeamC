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
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN,0))
	{
		menu_cursor++;
		//1番下に到達したら、１番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP,0))
	{
		menu_cursor--;
		//1番上に到達したら、１番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,0))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_HELP;
		default:
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
}

//終了処理
void TitleScene::Finalize()
{
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