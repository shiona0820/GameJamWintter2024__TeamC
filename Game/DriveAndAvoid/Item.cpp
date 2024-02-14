#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	coneimage = LoadGraph("Resource/images/cone.bmp");

	for (int i = 0; i < 3; i++)
	{
		cone[i].flg = FALSE;
	}
	gWaitTime = 0;
}

//デストラクタ
Item::~Item()
{

}

//更新
void Item::Update()
{
	//ランダムでコーンを表示する
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == false || count++)
		{
			cone[i].x = (float)(GetRand(99) * 300 - 40);
			if (cone[i].x<= 40)
			{
				cone[i].flg = true;
			}
			//return TRUE;
		}
	}
}

//描画
void Item::Draw() const 
{
	//障害物（三角コーン）画像の描画
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == true /*|| count==i*/)
		{
			//障害物（三角コーン）画像の描画
			DrawRotaGraph(200*cone[i].x, 220*cone[i].y, 0.7, 0.0, coneimage, true);
		}
		for (int j = 0; j > 600; j++)
		{
			if (gWaitTime >= 600)
			{
				DeleteGraph(coneimage);
			}
		}
		
	}

}
