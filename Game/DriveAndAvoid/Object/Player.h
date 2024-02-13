#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"


//�v���C���[���ǂ��ɓ����������H
enum direction
{
	RGIHT,//�E
	LEFT,//��
	UP,//��
	UNDER,//��

};

class Player
{
private:
	bool is_active;      //�L����Ԃ�
	int image;           //�摜�f�[�^
	Vector2D location;   //�ʒu���W
	Vector2D box_size;   //�����蔻��̑傫��
	float angle;         //�p�x
	float speed;         //����
	float hp;            //�̗�
	float fuel;          //�R��
	int barrier_count;   //�o���A�̖���
	Barrier* barrier;    //�o���A
	int playernum;//�v���C���[�̔ԍ�
	int playerd;//�ǂ��ɓ����������̊i�[
	
	//�����p
	int time2;//�o�ߎ��ԓ���p
	double t;//�o�ߎ��Ԃ��v�Z���Ē��Ɏ�荞�ނ悤
	int y;//�v�Z���ʑ���p	

	float v0;//�����W���v�Z�p

public:
	Player();
	~Player();

	void Initialize(int pnum);        //����������
	void Update();            //�X�V����
	void Draw();              //�`�揈��
	void Finalize();          //�I��������

public:
	void SetActive(bool flg);          //�L���t���O�ݒ�
	void DecreaseHp(float value);       //�̗͌�������
	Vector2D GetLocation() const;   //�ʒu���擾
	Vector2D GetBoxSize() const;    //�����蔻��̑傫���擾
	float GetSpeed() const;         //�����擾����
	float GetFuel() const;          //�R���擾
	float GetHp() const;            //�̗͎擾
	int GetBarriarCount() const;         //�o���A�̖����擾
	bool IsBarrier() const;         //�o���A�L�������擾

	void direction(Vector2D xy);			//�ǂ��ɓ������������ׂ�
	void Repulsion(int time);//�Ԃ������甽���N�����p

private:
	void Movement();      //�ړ�����
	void Acceleration();    //��������
};