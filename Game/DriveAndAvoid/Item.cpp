#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	coneimage = LoadGraph("Resource/images/cone.bmp");

	for (int i = 0; i < 3; i++)
	{
		cone[i].flg = FALSE;
		cone[i].hitflg = FALSE;
	}
	gWaitTime = 100;
	location.x = 0;
	location.y = -10;
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
	////ランダムでコーンを表示する
	//for (int i = 0; i < ITEM_MAX; i++)
	//{
	//	if (cone[i].flg == false)
	//	{
	//		cone[i].x = (float)(GetRand(100) * 300 - 40);
	//		if (cone[i].x<= 40)
	//		{
	//			cone[i].flg = true;
	//		}
	//		cone[i].x=1+(int)(rand()*(4-1+1));
	//	}
		//コーンを動かす
	location.y+=1;
	/*if (gWaitTime >= 700)
	{
		cone[i].x = (float)(GetRand(99) * 300 - 400);
	}*/
	//}

		//操作不可状態であれば、自身を回転させる
	
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
		if (location.x > 1350 || location.y>720 || location.x < -10)
		{
			hitflg = false;
			angle = 0;
		}
		return;
			
	}
	
}

//描画
void Item::Draw() const 
{
	//障害物（三角コーン）画像の描画
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	/*for(int j=0;j<gWaitTime;j++)
	//{*/
	//	for (int i = 0; i < ITEM_MAX; i++)
	//	{
	//		if (cone[i].flg == true /*|| count==i*/)
	//		{
				//障害物（三角コーン）画像の描画
				DrawRotaGraph(location.x, 10 + location.y, 0.7, angle, coneimage, true);
		//	}
		//	//ある程度の座標に行ったら消える
		//	if (location.y >= 725)
		//	{
		//		DeleteGraph(coneimage);
		//	}
		//}
	//}
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
