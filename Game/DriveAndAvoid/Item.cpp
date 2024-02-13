#include "Item.h"
#include "DxLib.h"

//�R���X�g���N�^
Item::Item()
{
	coneimage = LoadGraph("Resource/images/cone.bmp");

	for (int i = 0; i < 3; i++)
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

//�`��
void Item::Draw() const 
{
	//��Q���i�O�p�R�[���j�摜�̕`��
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == true /*|| count==i*/)
		{
			//��Q���i�O�p�R�[���j�摜�̕`��
			DrawRotaGraph(200*cone[i].x, 220*cone[i].y, 0.7, 0.0, coneimage, true);
		}

	}

}
