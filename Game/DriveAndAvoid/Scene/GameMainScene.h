#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Object/Policecar.h"
#include "../Item.h"


class GameMainScene : public SceneBase
{
private:
	bool startflg;		// �Q�[���J�n�t���O
	int starttimer;		// �Q�[���J�n���̃J�E���g�_�E���p
	int number_img[3];
	int startnum;

	int high_score;     //�n�C�X�R�A
	int back_ground;    //�w�i�摜
	int audience_img;	//�ϋq�摜

	int mileage;        //�w�i�摜�𓮂����悤
	int mileage2;        //�ϋq�摜�������p
	int enemy_image[3]; //�G�摜
	int enemy_count[3]; //�ʂ�߂����G�J�E���g
	Player* player;     //�v���C���[
	Player* player2;     //�v���C���[2
	Enemy** enemy;       //�G
	Policecar* Pcar;     //�p�g�J�[
	
	Item* item[10];

	int max, min;
	
	int count;          //�U�O�񐔂���
	int timer;          //count���U�O�ɂȂ�����P������
	int ptimer;
	int ptimer2;

	int time;//�A�N�V�����N�������̎��Ԃ�n���p
	bool flg;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();

	//�����蔻��
	//bool IsHitCheck(Player* p, Enemy* e);
	bool IsHitCheckPlayer(Player* p, Player* p2);
	bool IsHitCheckP1(Player* p,Policecar* car);
	bool IsHitCheckP2(Player* p2,Policecar* car);

	// �h�A�̓����蔻��
	bool IsHitDoorR(Player* p1,Player* p2);
	bool IsHitDoorL(Player* p1,Player* p2);

	// �h�A�̓����蔻��i�v���C���[�Q�j
	bool IsHitDoorR2(Player* p1, Player* p2);
	bool IsHitDoorL2(Player* p1, Player* p2);

	//�A�C�e���̓����蔻��
	bool IsHitCheckItem(Player* p, Item* i);
	bool IsHitItem(Player* p2, Item* i);

};