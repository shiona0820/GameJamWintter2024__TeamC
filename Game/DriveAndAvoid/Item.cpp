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
	gWaitTime = 100;
	location.x = 0;
	location.y = 0;
	box_size = Vector2D(5.0f, 10.0f);
}

//�f�X�g���N�^
Item::~Item()
{

}

void Item::Initialize(int x)
{
	location.x = x*120;
}

void Item::ResetY(float y)
{
	location.y = y;
}

//�X�V
void Item::Update()
{
	////�����_���ŃR�[����\������
	//for (int i = 0; i < ITEM_MAX; i++)
	//{
	//	if (cone[i].flg == false)
	//	{
	//		cone[i].x = (float)(GetRand(100) * 300 - 40);
	//		if (cone[i].x<= 40)
	//		{
	//			cone[i].flg = true;
	//		}
	//		cone[i].x=1+(int)(rand()*(4-1+1));
	//	}
		//�R�[���𓮂���
		location.y++;
		/*if (gWaitTime >= 700)
		{
			cone[i].x = (float)(GetRand(99) * 300 - 400);
		}*/
	//}
	
}

//�`��
void Item::Draw() const 
{
	//��Q���i�O�p�R�[���j�摜�̕`��
	//DrawRotaGraph(90, 220, 0.7, 0.0, coneimage, TRUE);

	/*for(int j=0;j<gWaitTime;j++)
	//{*/
	//	for (int i = 0; i < ITEM_MAX; i++)
	//	{
	//		if (cone[i].flg == true /*|| count==i*/)
	//		{
				//��Q���i�O�p�R�[���j�摜�̕`��
				DrawRotaGraph(location.x, 10 + location.y, 0.7, 0.0, coneimage, true);
		//	}
		//	//������x�̍��W�ɍs�����������
		//	if (location.y >= 725)
		//	{
		//		DeleteGraph(coneimage);
		//	}
		//}
	//}
}

//�ʒu�����擾
Vector2D Item::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Item::GetBoxSize() const
{
	return box_size;
}
