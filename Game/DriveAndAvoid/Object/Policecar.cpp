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

	//画像の読み込み.....仮で自身の画像変更済み
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
