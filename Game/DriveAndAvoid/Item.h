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
	void Initialize(int x);             //����������
	void ResetY(float y);

	Vector2D GetLocation() const; //�ʒu���̎擾
	Vector2D GetBoxSize() const;  //�����蔻��̑傫�����擾

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
