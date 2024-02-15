#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	//画像の読み込み
	coneimage = LoadGraph("Resource/images/cone.bmp");

	//locationの初期化
	location.x = 0;
	location.y = -10;
	//当たり判定のボックスの設定
	box_size = Vector2D(5.0f, 10.0f);

	angle = 0.0f;
	speed = 3.0f;
	hitflg = false;
}

//デストラクタ
Item::~Item()
{

}

void Item::Initialize(int x)
{
	//GameMainSceneからx座標をとってくるための初期化
	location.x = x*120;
}

void Item::ResetY(float y)
{
	location.y = y;
}

bool Item::GetHitflg() const
{
	return this->hitflg;
}

void Item::Hitflg(bool flg)
{
	this->hitflg = flg;
}


//更新
void Item::Update()
{
	//コーンを動かす(y座標)
	location.y++;

		
		speed = 1.0f;
		if (location.x > 1350 || location.y>720 || location.x < -20)
		{
			hitflg = false;
			angle = 0;
		}

		if (hitflg == true)
		{

			if (location.x > 640)
			{
				location.x += 10;
				angle += DX_PI_F / 24.0f;
			}
			else
			{
				location.x -= 10;
				angle += DX_PI_F / -24.0f;
			}

			//Attackflg = false;


			speed = 1.0f;
			if (location.x > 1350 || location.y > 720 || location.x < -5)
			{
				hitflg = false;
				angle = 0;
			}

		}

		return;
			
	
}

//描画
void Item::Draw() const 
{
	//障害物（三角コーン）画像の描画
	DrawRotaGraph(location.x, 10 + location.y, 0.7, angle, coneimage, true);
}

//位置情報を取得
Vector2D Item::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Item::GetBoxSize() const
{
	return box_size;
}
