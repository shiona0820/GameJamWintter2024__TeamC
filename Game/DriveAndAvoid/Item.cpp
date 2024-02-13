#include "Item.h"
#include "DxLib.h"

//コンストラクタ
Item::Item()
{
	rand = 0;
	coneimage = LoadGraph("Resource/images/cone.bmp");
	for (int i = 0; i < ITEM_MAX; i++)
	{
		cone[i].flg = FALSE;
	}
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
		if (cone[i].flg == TRUE)
		{
			SRand(i);
			rand = GetRand(99);
			if (rand <= 40)
			{
				cone[i].flg = true;
			}
		}
	}
}

//描画
void Item::Draw() const
{
	//障害物（三角コーン）画像の描画
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	DrawBox(200, 200, 400, 400, 0xff0000, FALSE);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == true)
		{
			//障害物（三角コーン）画像の描画
			DrawRotaGraph(90, 220, 0.7, 2.0, coneimage, true);
		}
		else
		{
			SetFontSize(20);
			DrawString(100, 100, "描画できません", 0xfff000);
		}
	}

}
