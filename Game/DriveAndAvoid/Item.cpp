#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	//画像の読み込み
	coneimage = LoadGraph("Resource/images/cone.bmp");

	//locationの初期化
	location.x = 0;
	location.y = 0;
	//当たり判定のボックスの設定
	box_size = Vector2D(20.0f, 25.0f);
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

//更新
void Item::Update()
{
	//コーンを動かす(y座標)
	location.y++;
}

//描画
void Item::Draw() const 
{
	//障害物（三角コーン）画像の描画
	DrawRotaGraph(location.x, 10 + location.y, 0.7, 0.0, coneimage, true);
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
