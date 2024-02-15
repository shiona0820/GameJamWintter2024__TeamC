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
	box_size = Vector2D(20.0f, 25.0f);
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

//�X�V
void Item::Update()
{
	//�R�[���𓮂���(y���W)
	location.y++;
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
