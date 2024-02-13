#include "Item.h"
#include "DxLib.h"

//�R���X�g���N�^
Item::Item()
{
	rand = 0;
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
			SRand(i);
			rand = GetRand(99);
			if (rand <= 40)
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

	DrawBox(200, 200, 400, 400, 0xff0000, FALSE);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (cone[i].flg == true)
		{
			//��Q���i�O�p�R�[���j�摜�̕`��
			DrawRotaGraph(90, 220, 0.7, 2.0, coneimage, true);
		}
		else
		{
			SetFontSize(20);
			DrawString(100, 100, "�`��ł��܂���", 0xfff000);
		}
	}

}
