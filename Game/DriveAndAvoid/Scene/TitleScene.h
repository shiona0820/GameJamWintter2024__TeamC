#pragma once

#include"SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;        //背景画像
	int menu_image;             //メニュー画像
	int cursor_image;           //カーソル画像
	int end_image;
	int menu_cursor;            //メニューカーソル番号
	int end_cun;
	bool end;

	int title_sound;   //タイトルBGM
	int button_sound;  //ボタン移動SE
	int buttonON_sound;      //ボタン決定SE
	int buttonNO_sound;      //キャンセルボタンSE

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};