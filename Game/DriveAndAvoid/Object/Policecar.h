#pragma once
#include"DxLib.h"

#include"../Utility/Vector2D.h"

class Policecar
{
private:
	
	int image;

	Vector2D location;   //位置情報
	Vector2D box_size;   //当たり判定の大きさ

public:
	Policecar();
	~Policecar();

	void Initialize();        //初期化処理
	void Update();            //更新処理
	void Draw();              //描画処理
	void Finalize();          //終了時処理

	Vector2D GetLocation() const; //位置情報の取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさを取得
};

