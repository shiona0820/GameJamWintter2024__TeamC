#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() : high_score(0), back_ground(NULL),ptimer(0),
audience_img(NULL), mileage(0),mileage2(0), player(nullptr),player2(nullptr), enemy(nullptr),time(0),flg(false)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back1.bmp");
	audience_img = LoadGraph("Resource/images/audience.png");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���?n");
	}

	/*if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}*/

	if (audience_img == -1)
	{
		throw("Resource/images/audience.png������܂���?");
	}

	//�I�u�W�F�N�g�̐���
	player = new Player;
	player2 = new Player;

	enemy = new Enemy* [10];
	Pcar = new Policecar;

	//�I�u�W�F�N�g�̏�����
	player->Initialize(0,400);
	player2->Initialize(1,200);

	Pcar->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	//������
	count = 0;
	timer = 0;

}

//�X�V����
eSceneType GameMainScene::Update()
{


	//�v���C���[�̍X�V
	player->Update();
	//�v���C���[�Q�̍X�V
	player2->Update();

	//�ړ������̍X�V
	mileage += 15;
	mileage2 += 2;

	/**
	�G��������
	count��60�s������Atimer���P�����ăp�g�J�[�̂����P������
	**/
	count++;
	if (count > 60)
	{
		count = 0;
		timer++;
		ptimer++;
		Pcar->Update();
	}
	if (timer == 180)
	{
		timer = 0;
	}

	//�v���C���[���_���[�W�H��������G����
	if (ptimer > 3)
	{
		player2->Hitflg(false);
		ptimer= 0;
	}


			//�����蔻��̊m�F
		//�����蔻��̊m�F�i�v���C���[�ƃp�g�J�[�j
			if (IsHitCheckPlayer(player,player2))
			{

				if (flg == false)
				{
					flg = true;
				}

				player->Exclusion(player2->GetLocation());
				player2->Exclusion(player->GetLocation());

				//�����������A���肪�ǂ��ɓ����������Ƒ��肪�ǂ������Ă���̂��n��
				player->RepulsionX(player->GetLocation() - player2->GetLocation(),player2->GetDirection());
				player2->RepulsionX(player2->GetLocation() - player->GetLocation(),player->GetDirection());


			}

			//�v���C���[�P�ƃp�g�J�[�̓����蔻��
			if (IsHitCheckP1(player,Pcar))
			{
				player->SetActive(false);
				player->DecreaseHp(-1000.0f);
			}

			if (IsHitCheckP2(player2, Pcar))
			{
				player2->SetActive(false);
				player2->DecreaseHp(-1000.0f);

			}

			// HP���O�ɂȂ����甚������
			if (player->GetHp() <= 0)
			{
				player->Explosion();

			}
			if (player2->GetHp() <= 0)
			{
				player2->Explosion();

			}

			//�U���̓��͉������Ƃ���������ɂ��遫
			if (player->GetAttackflg() == TRUE)
			{
				//�v���C���[�P�̍U��
				// �h�A�ɓ�����Ɖ�]����(�v���C���[�Q)
				if (player2->GetHitflg() == false) {
					if (IsHitDoorR(player, player2))
					{
						if (player2->GetHitflg() == false)
						{
							ptimer = 0;
							player2->DecreaseHp(-100);
							player2->SetActive(false);
						}
					}

					if (IsHitDoorL(player, player2))
					{
						if (player2->GetHitflg() == false)
						{
							ptimer = 0;
							player2->DecreaseHp(-100);
							player2->SetActive(false);
						}
					}
				}

			}

			if (player2->GetAttackflg() == TRUE)
			{
				//�v���C���[�Q�̍U��
				// �h�A�ɓ�����Ɖ�]����i�v���C���[�P�j
				if (player->GetHitflg() == false) {
					if (IsHitDoorR2(player, player2))
					{
						ptimer = 0;
						player->DecreaseHp(-100);
						player->SetActive(false);
					}

					if (IsHitDoorL2(player, player2))
					{
						ptimer = 0;
						player->DecreaseHp(-100);
						player->SetActive(false);
					}
				}
			}



				//�v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
		/*	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
			{
				return eSceneType::E_RESULT;
			}*/
			return GetNowScene();

}


			////�����蔻��̊m�F
			//if (IsHitCheck(player,enemy[i]))
			//{
			//	player -> SetActive(false);
			//		player -> DecreaseHp(-50.0f);
			//		enemy[i] -> Finalize();
			//		delete enemy[i];
			//		enemy[i] = nullptr;
			//}
			


//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//�ϋq�̕`��
	DrawGraph(1160, mileage2%720-720, audience_img, TRUE);
	DrawGraph(1160, mileage2%720, audience_img, TRUE);
	DrawTurnGraph(-80, mileage2%720-720, audience_img, TRUE);
	DrawTurnGraph(-80, mileage2%720, audience_img, TRUE);

	//�G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//�v���C���[�̕`��
	player->Draw();
	//PAD2�v���C���[�̕`��
	player2->Draw();

	//�p�g�J�[�̕`��
	Pcar->Draw();

}

//�I��������
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Rsource/dat/result_data.csv���J���܂���\n");
	}

	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	//�������a�l���_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;
	
	player2->Finalize();
	delete player2;


	Pcar->Finalize();
	delete Pcar;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

////�����蔻�菈���i�v���C���[�ƓG�j
//bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
//{
//	////�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
//	//if (p->IsBarrier())
//	//{
//	//	return false;
//	//}
//
//	//�G��񂪖�����΁A�����蔻��𖳎�����
//	if (e == nullptr)
//	{
//		return false;
//	}
//
//	//�ʒu���̍������擾
//	Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//�����蔻��T�C�Y�̑傫�����擾
//	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
//	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}


//�����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheckP1(Player* p, Policecar* car)
{

	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (car == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - car->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + car->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

bool GameMainScene::IsHitCheckP2(Player* p2, Policecar* car)
{

	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (car == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p2->GetLocation() - car->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p2->GetBoxSize() + car->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

bool GameMainScene::IsHitCheckPlayer(Player* p, Player* p2)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - p2->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize()+p2->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// �v���C���[�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR(Player* p1, Player* p2)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p1->GetDoorRLocation() - p2->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p1->GetDoorRSize() + p2->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// �v���C���[�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL(Player* p1, Player* p2)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p1->GetDoorLLocation() - p2->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p1->GetDoorLSize() + p2->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// �v���C���[2�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR2(Player* p1, Player* p2)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p2->GetDoorRLocation() - p1->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p2->GetDoorRSize() + p1->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// �v���C���[2�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL2(Player* p1, Player* p2)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p2->GetDoorLLocation() - p1->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p2->GetDoorLSize() + p1->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}