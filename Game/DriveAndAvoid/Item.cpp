#include "Item.h"
#include "DxLib.h"

//�R���X�g���N�^
Item::Item()
{
	//�摜�̓ǂݍ���
	coneimage = LoadGraph("Resource/images/cone.bmp");

	//location�̏�����
	location.x = 0;
	location.y = 0;
	//�����蔻��̃{�b�N�X�̐ݒ�
	box_size = Vector2D(5.0f, 10.0f);

	angle = 0.0f;
	speed = 3.0f;
	hitflg = false;
}

//�f�X�g���N�^
Item::~Item()
{

}

void Item::Initialize(int x)
{
	//GameMainScene����x���W���Ƃ��Ă��邽�߂̏�����
	location.x = x*120;
}

void Item::ResetY(float y)
{
	location.y = y;
}

bool Item::GetHitflg() const
{
	return this->hitflg;
}

void Item::Hitflg(bool flg)
{
	this->hitflg = flg;
}


//�X�V
void Item::Update()
{
	//�R�[���𓮂���(y���W)
	location.y++;
}

		
		speed = 1.0f;
		if (location.x > 1350 || location.y>720 || location.x < -10)
		{
			hitflg = false;
			angle = 0;
		}
		return;
			
	}
	
}

//�`��
void Item::Draw() const 
{
	//��Q���i�O�p�R�[���j�摜�̕`��
	DrawRotaGraph(location.x, 10 + location.y, 0.7, 0.0, coneimage, true);
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
