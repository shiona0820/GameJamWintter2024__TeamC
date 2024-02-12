#pragma once
#include"DxLib.h"

#include"../Utility/Vector2D.h"

class Policecar
{
private:
	int x;
	int y;
	int image;

public:
	Policecar();
	~Policecar();

	void Initialize();        //初期化処理
	void Update();            //更新処理
	void Draw();              //描画処理
	void Finalize();          //終了時処理


};

