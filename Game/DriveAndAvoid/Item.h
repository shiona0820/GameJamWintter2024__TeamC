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
	void Initialize(int x);             //‰Šú‰»ˆ—
	void ResetY(float y);

	Vector2D GetLocation() const; //ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;  //“–‚½‚è”»’è‚Ì‘å‚«‚³‚ğæ“¾

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
