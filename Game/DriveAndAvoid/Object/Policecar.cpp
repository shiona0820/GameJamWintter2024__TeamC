#include "Policecar.h"

Policecar::Policecar()
{

}

Policecar::~Policecar()
{

}

void Policecar::Initialize()
{

	x = 700;
	y = 1020;

	//�摜�̓ǂݍ���.....���Ŏ��g�̉摜�ύX�ς�
	image = LoadGraph("Resource/images/Pcar2.png");

}

void Policecar::Update()
{
	y -= 4;
}

void Policecar::Draw()
{
	DrawRotaGraphF(x,y, 1.0,0,image, TRUE);
}

void Policecar::Finalize()
{

}
