#pragma once

#define ITEM_MAX  3

class Item
{
private:
	int coneimage;
	int rand_x, rand_y;


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
	};
	struct CONE cone[3];
};
