#pragma once
#include"DxLib.h"

#include"../Utility/Vector2D.h"

class Policecar
{
private:
	int x;
	int y;
	int image;

public:
	Policecar();
	~Policecar();

	void Initialize();        //����������
	void Update();            //�X�V����
	void Draw();              //�`�揈��
	void Finalize();          //�I��������


};

