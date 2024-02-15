#include "Policecar.h"

Policecar::Policecar() : image(), location(0.0f)
{

}
 
Policecar::~Policecar()
{

}

//����������
void Policecar::Initialize()
{

	//�����ʒu�̐ݒ�
	location = Vector2D(location.x, location.y);

	/*x = 700;
	y = 1020;*/

	location.x = 640;
	location.y = 1000;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1car.png");

	//�����蔻��̐ݒ�
	box_size = Vector2D( 640.0f,200.0f);
	
}

//�X�V����
void Policecar::Update()
{
	location.y -= 4;
}

//�`�揈��
void Policecar::Draw()
{
	DrawRotaGraphF(location.x,location.y, 1.0,0,image, TRUE);
}

void Policecar::Finalize()
{

}

//�ʒu�����擾
Vector2D Policecar::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Policecar::GetBoxSize() const
{
	return box_size;
}