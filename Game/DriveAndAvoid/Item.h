#pragma once
#include "Utility/Vector2D.h"
#include "Object/Player.h"

#define ITEM_MAX  10

class Item
{
private:
	int coneimage;
	int count;
	int gWaitTime;
	int min, max;

	Vector2D location;
	Vector2D box_size;
	Player player;

public:
	Item();
	~Item();
	void Update();
	void Draw()const;
	void Initialize(int x);             //初期化処理
	void ResetY(float y);

	Vector2D GetLocation() const; //位置情報の取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさを取得

	struct CONE
	{
		int x, y;
		int w, h;
		int image;
		int flg;
		int speed;
	};
	struct CONE cone[3];

};
