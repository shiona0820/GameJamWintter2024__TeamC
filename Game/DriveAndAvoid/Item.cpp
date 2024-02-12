#include "Item.h"
#include "DxLib.h"

//�R���X�g���N�^
Item::Item()
{
	coneimage = LoadGraph("Resource/images/cone.bmp");
}

//�f�X�g���N�^
Item::~Item()
{

}

//�X�V
void Item::Update()
{
	//�����_���ŃR�[����\������
	for (int i = 0; i < 3; i++)
	{
		if (cone[i].flg == false)
		{
			rand = GetRand(99);
			if (rand <= 40)
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
	DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	//for (int i = 0; i < 3; i++)
	//{
	//	if (cone[i].flg == true)
	//	{
	//		//��Q���i�O�p�R�[���j�摜�̕`��
	//		DrawRotaGraph(90, 220, 0.7, 2.0, coneimage, true);
	//	}
	//}

}
