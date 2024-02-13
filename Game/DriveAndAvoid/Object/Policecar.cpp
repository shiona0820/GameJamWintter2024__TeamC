#include "Policecar.h"

Policecar::Policecar() : image(), location(0.0f)
{

}
 
Policecar::~Policecar()
{

}

//初期化処理
void Policecar::Initialize()
{

	//生成位置の設定
	location = Vector2D(location.x, location.y);

	/*x = 700;
	y = 1020;*/

	location.x = 640;
	location.y = 1000;

	//画像の読み込み
	image = LoadGraph("Resource/images/Pcar2.png");

	//当たり判定の設定
	box_size = Vector2D( 640.0f, 300.0f);
	
}

//更新処理
void Policecar::Update()
{
	location.y -= 4;
}

//描画処理
void Policecar::Draw()
{
	DrawRotaGraphF(location.x,location.y, 1.0,0,image, TRUE);
	DrawCircle(location.x, location.y, 3, GetColor(255, 255, 0), TRUE);
	//DrawBoxAA(0, 479, 639, 800, GetColor(255, 255, 255), FALSE);
}

void Policecar::Finalize()
{

}

//位置情報を取得
Vector2D Policecar::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Policecar::GetBoxSize() const
{
	return box_size;
}