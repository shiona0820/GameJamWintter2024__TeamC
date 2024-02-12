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

	//‰æ‘œ‚Ì“Ç‚İ‚İ.....‰¼‚Å©g‚Ì‰æ‘œ•ÏXÏ‚İ
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
