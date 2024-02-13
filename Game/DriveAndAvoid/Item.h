#pragma once
#include "Utility/Vector2D.h"

#define ITEM_MAX  3

class Item
{
private:
	int coneimage;
	int count;

	Vector2D location;

public:
	Item();
	~Item();
	void Update();
	void Draw()const;

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
