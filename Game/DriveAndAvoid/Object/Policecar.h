#pragma once
#include"DxLib.h"

#include"../Utility/Vector2D.h"

class Policecar
{
private:
	
	int image;

	Vector2D location;   //�ʒu���
	Vector2D box_size;   //�����蔻��̑傫��

public:
	Policecar();
	~Policecar();

	void Initialize();        //����������
	void Update();            //�X�V����
	void Draw();              //�`�揈��
	void Finalize();          //�I��������

	Vector2D GetLocation() const; //�ʒu���̎擾
	Vector2D GetBoxSize() const;  //�����蔻��̑傫�����擾
};

