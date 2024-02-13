#include "Item.h"
#include "DxLib.h"

//�R���X�g���N�^
Item::Item()
{
	rand_x,rand_y = 0;
	coneimage = LoadGraph("Resource/images/cone.bmp");
	for (int i = 0; i < ITEM_MAX; i++)
	{
		cone[i].flg = FALSE;
	}
}

//�f�X�g���N�^
Item::~Item()
{

}

//�X�V
void Item::Update()
{
	//�����_���ŃR�[����\������
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == TRUE)
		{
			rand_x = GetRand(640-200);
			rand_y = GetRand(480 - 200);
			if (rand_x <= 40)
			{
				cone[i].flg = true;
			}
			if (rand_y <= 40)
			{
				cone[i].flg = true;
			}
		}
	}
}

//�`��
void Item::Draw() const
{
	//��Q���i�O�p�R�[���j�摜�̕`��
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == true)
		{
			//��Q���i�O�p�R�[���j�摜�̕`��
			LoadGraphScreen(rand_x, rand_y, "Resource/images/cone.bmp", TRUE);
		}
		else
		{
			SetFontSize(20);
			DrawString(100, 100, "�`��ł��܂���", 0xfff000);
		}
	}

}
