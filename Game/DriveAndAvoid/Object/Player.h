#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"

class Player
{
private:
	bool is_active;      //�L����Ԃ�
	int image;           //�摜�f�[�^
	Vector2D location;   //�ʒu���W
	Vector2D direction;   //sinnkoiu
	Vector2D box_size;   //�����蔻��̑傫��
	float angle;         //�p�x
	float speed;         //����
	float hp;            //�̗�
	float fuel;          //�R��
	int barrier_count;   //�o���A�̖���
	Barrier* barrier;    //�o���A
	int playernum;//�v���C���[�̔ԍ�
	int playerd;//�ǂ��ɓ����������̊i�[
	Vector2D dire;//�v�Z�p

	int crackimg;//�Ԃ̂Ђщ摜�p
	int alpha;//�Ђт𓧂����p
	int hpcheck;

	bool hit_flg;//�U��������������
	bool death_flg;//�����t���O

	bool survival_flg;	// �����t���O

	int blinkingcun;
	bool blinking_flg;

	// �U�����̉摜
	int carRimg, carLimg, doorRimg, doorLimg;

	int Attackflg;		// �U���t���O
	int Bflg, Xflg;		// �U���{�^���̔���p�t���O
	//�h�A�̊p�x
	float DoorRangle, DoorLangle, Door2Rangle, Door2Langle;
	int Acount;		// �h�A�̕`��p
	Vector2D DoorRlocation;		//�h�A�̈ʒu���W�i�E�j
	Vector2D DoorR_size;		//�h�A�̓����蔻��̑傫���i�E�j
	Vector2D DoorLlocation;		//�h�A�̈ʒu���W�i���j
	Vector2D DoorL_size;		//�h�A�̓����蔻��̑傫���i���j


	int explosion_img[3];	// �����摜
	int exNum;				// �����A�j���[�V�����`��p
	int explosion_count;	// �����A�j���[�V�����J�E���g�p

	int explosion_sound;   //����SE
	int blow_sound;        //�Ō�SE
	int taiatari_sound;    //�ԓ��m�̂Ԃ��鎞��SE
	int slip_sound;        //���̂ɂԂ���������SE

	bool sliponce;

public:
	Player();
	~Player();

	void Initialize(int pnum,float x);        //����������
	void Update();            //�X�V����
	void Draw();              //�`�揈��
	void Finalize();          //�I��������

public:
	void SetActive(bool flg);          //�L���t���O�ݒ�
	void DecreaseHp(float value);       //�̗͌�������
	void Hitflg(bool flg);//�U�����������ĂȂ���Ԃ������炤
	Vector2D GetLocation() const;   //�ʒu���擾
	Vector2D GetDirection() const;   //�������擾
	Vector2D GetBoxSize() const;    //�����蔻��̑傫���擾
	float GetSpeed() const;         //�����擾����
	float GetFuel() const;          //�R���擾
	float GetHp() const;            //�̗͎擾
	int GetBarriarCount() const;         //�o���A�̖����擾
	bool IsBarrier() const;         //�o���A�L�������擾
	bool GetHitflg() const;//HP�����炷�̂���񂾂��ɂ���p

	bool GetSurvival_flg() const;	// ����������p�t���O�i������false�ɂȂ�j

	bool GetDeathFlg() const;//�s�k�擾

	// �{�^���t���O��Ԃ�
	int GetBflg() const;
	int GetXflg() const;

	int GetAttackflg() const;//�A�^�b�N�t���O��Ԃ�

	//void direction(Vector2D xy);			//�ǂ��ɓ������������ׂ�
	void RepulsionX(Vector2D xy,Vector2D d);//�Ԃ������甽���N�����p���E
	void RepulsionY(Vector2D xy,Vector2D d);//�Ԃ������甽���N�����p�㉺
	//����̃��P�[�V�����ƌ��������炤

	//�����̎ԂɐN���ł��Ȃ�����
	void Exclusion(Vector2D loce);

	// �����A�j���[�V����
	void Explosion();

	Vector2D GetDoorRLocation() const;   //�h�A�̈ʒu���擾�i�E�j
	Vector2D GetDoorRSize() const;		 //�h�A�̓����蔻��̑傫���擾�i�E�j

	Vector2D GetDoorLLocation() const;   //�h�A�̈ʒu���擾�i���j
	Vector2D GetDoorLSize() const;		 //�h�A�̓����蔻��̑傫���擾�i���j

private:
	void Movement();      //�ړ�����
	void Acceleration();    //��������
};