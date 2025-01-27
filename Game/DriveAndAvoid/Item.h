#pragma once
#include "Utility/Vector2D.h"
#include "Object/Player.h"

#define ITEM_MAX  10

class Item
{
private:
	int coneimage;
	
	Vector2D location;
	Vector2D box_size;
	Player player;

	float angle;
	float speed;

	bool hitflg;

public:
	Item();
	~Item();
	void Update();
	void Draw()const;
	void Initialize(int x);             //初期化処理
	void ResetY(float y);

	bool GetHitflg() const;
	void Hitflg(bool flg);

	Vector2D GetLocation() const; //位置情報の取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさを取得

};
