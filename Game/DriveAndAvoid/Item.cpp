#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	coneimage = LoadGraph("Resource/images/cone.bmp");
}

//デストラクタ
Item::~Item()
{

}

//更新
void Item::Update()
{
	//ランダムでコーンを表示する
	for (int i = 0; i < 3; i++)
	{
		if (cone[i].flg == false)
		{
			rand = GetRand(99);
			if (rand <= 40)
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
	DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	//for (int i = 0; i < 3; i++)
	//{
	//	if (cone[i].flg == true)
	//	{
	//		//障害物（三角コーン）画像の描画
	//		DrawRotaGraph(90, 220, 0.7, 2.0, coneimage, true);
	//	}
	//}

}
