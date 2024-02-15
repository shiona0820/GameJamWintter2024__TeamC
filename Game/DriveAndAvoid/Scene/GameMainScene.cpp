#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

int GameMainScene::Wineer=0;

GameMainScene::GameMainScene() : high_score(0), back_ground(NULL),ptimer(0),ptimer2(0),
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
	blackimg = LoadGraph("Resource/images/black.png");
	starimg = LoadGraph("Resource/images/star.png");
	LoadDivGraph("Resource/images/123.png", 3, 3, 1, 128, 128, number_img);

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
	player3 = new Player;
	player4 = new Player;

	enemy = new Enemy* [10];
	Pcar = new Policecar;

	//�I�u�W�F�N�g�̏�����
	player->Initialize(0,800);
	player2->Initialize(1,400);
	player3->Initialize(2,650);
	player4->Initialize(3,900);

	Pcar->Initialize();

	

	min = 1;
	max = 4;

	for (int i = 0; i < 10; i++)
	{
		item[i] = new Item;
		item[i]->Initialize(GetRand(10));
	}
	
//		cone[i].x=1+(int)(rand()*(4-1+1));

	
	alpha = 0;

	//������
	count = 0;
	timer = 0;

	startflg = false;
	starttimer = 0;
	startnum = 3;

	p1win = 0;
	p2win = 0;
	p3win = 0;
	p4win = 0;
	whowin = 0;
	wFlg = false;
}

//�X�V����
eSceneType GameMainScene::Update()
{

	if (startflg == false)
	{

		// �J�E���g�_�E����ɃQ�[���J�n
		starttimer++;
		switch (starttimer)
		{
		case(1):
			startnum = 2;
			break;
		case(60):
			startnum = 1;
			break;
		case(120):
			startnum = 0;
			break;
		case(180):
			startflg = true;
			startnum = 0;

			break;
		default:
			break;
		}

	}
	else
	{

		//�O�񕪂̏����������L�^����
		//�v���C���[�P���Q�����񂾏ꍇ
		if (wFlg==true)
		{
			win();
		}
		else
		{
			checkhum();
		}

		//�v���C���[�̍X�V
		player->Update();
		//�v���C���[�Q�̍X�V
		player2->Update();
		//�v���C���[�R�̍X�V
		player3->Update();
		//�v���C���[4�̍X�V
		player4->Update();

		//�A�C�e���̍X�V
		for (int i = 0; i < 10; i++)
		{
			if (item[i] != nullptr)
			{
				item[i]->Update();
			}
		}

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
			ptimer2++;
			ptimer3++;
			ptimer4++;
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
			ptimer = 0;
		}

		//�v���C���[���_���[�W�H��������G����
		if (ptimer2 > 3)
		{
			player->Hitflg(false);
			ptimer2 = 0;
		}

		//�v���C���[���_���[�W�H��������G����
		if (ptimer3 > 3)
		{
			player3->Hitflg(false);
			ptimer3 = 0;
		}

		//�v���C���[���_���[�W�H��������G����
		if (ptimer4 > 3)
		{
			player4->Hitflg(false);
			ptimer4 = 0;
		}


		//�����蔻��̊m�F
	//�����蔻��̊m�F�i�v���C���[�ƃp�g�J�[�j
		if (IsHitCheckPlayer(player, player2))
		{

			if (flg == false)
			{
				flg = true;
			}

			player->Exclusion(player2->GetLocation());
			player2->Exclusion(player->GetLocation());

			//�����������A���肪�ǂ��ɓ����������Ƒ��肪�ǂ������Ă���̂��n��
			player->RepulsionX(player->GetLocation() - player2->GetLocation(), player2->GetDirection());
			player2->RepulsionX(player2->GetLocation() - player->GetLocation(), player->GetDirection());

		}

		if (IsHitCheckPlayer3(player, player3))
		{
			player->Exclusion(player->GetLocation());
			player3->Exclusion(player3->GetLocation());

			player->RepulsionX(player->GetLocation() - player3->GetLocation(), player3->GetDirection());
			player3->RepulsionX(player3->GetLocation() - player->GetLocation(), player->GetDirection());

		}

		if (IsHitCheckPlayer(player, player4))
		{
			player->Exclusion(player->GetLocation());
			player4->Exclusion(player4->GetLocation());

			player->RepulsionX(player->GetLocation() - player4->GetLocation(), player4->GetDirection());
			player4->RepulsionX(player4->GetLocation() - player->GetLocation(), player->GetDirection());

		}

		if (IsHitCheckPlayer2(player2, player3))
		{
			player2->Exclusion(player3->GetLocation());
			player3->Exclusion(player2->GetLocation());

			player2->RepulsionX(player2->GetLocation() - player3->GetLocation(), player3->GetDirection());
			player3->RepulsionX(player3->GetLocation() - player2->GetLocation(), player2->GetDirection());

		}

		if (IsHitCheckPlayer2(player2, player4))
		{
			player2->Exclusion(player4->GetLocation());
			player4->Exclusion(player2->GetLocation());

			player2->RepulsionX(player2->GetLocation() - player4->GetLocation(), player4->GetDirection());
			player4->RepulsionX(player4->GetLocation() - player2->GetLocation(), player2->GetDirection());

		}

		if (IsHitCheckPlayer3(player3, player4))
		{
			player3->Exclusion(player4->GetLocation());
			player4->Exclusion(player3->GetLocation());

			player3->RepulsionX(player3->GetLocation() - player4->GetLocation(), player4->GetDirection());
			player4->RepulsionX(player4->GetLocation() - player3->GetLocation(), player3->GetDirection());

		}


		//�v���C���[�P�ƃp�g�J�[�̓����蔻��
		if (IsHitCheckP1(player, Pcar))
		{
			player->SetActive(false);
			player->DecreaseHp(-1000.0f);
		}

		if (IsHitCheckP2(player2, Pcar))
		{
			player2->SetActive(false);
			player2->DecreaseHp(-1000.0f);

		}

		if (IsHitCheckP3(player3, Pcar))
		{
			player3->SetActive(false);
			player3->DecreaseHp(-1000.0f);

		}

		if (IsHitCheckP3(player4, Pcar))
		{
			player4->SetActive(false);
			player4->DecreaseHp(-1000.0f);

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
		if (player3->GetHp() <= 0)
		{
			player3->Explosion();

		}
		if (player4->GetHp() <= 0)
		{
			player4->Explosion();

		}

		//�v���C���[�P�̍U��
		//�U���̓��͉������Ƃ���������ɂ��遫
		if (player->GetAttackflg() == TRUE)
		{
			// �h�A�ɓ�����Ɖ�]����(�v���C���[�Q)
			if (player2->GetHitflg() == false) {
				if (IsHitDoorR(player, player2))
				{
					if (player2->GetHitflg() == false)
					{
						ptimer2 = 0;
						player2->DecreaseHp(-100);
						player2->SetActive(false);
					}
				}

				if (IsHitDoorL(player, player2))
				{
					if (player2->GetHitflg() == false)
					{
						ptimer2 = 0;
						player2->DecreaseHp(-100);
						player2->SetActive(false);
					}
				}
			}


			// �h�A�ɓ�����Ɖ�]����(�v���C���[3)
			if (player3->GetHitflg() == false) {
				if (IsHitDoorR(player, player3))
				{
					if (player3->GetHitflg() == false)
					{
						ptimer3 = 0;
						player3->DecreaseHp(-100);
						player3->SetActive(false);
					}
				}

				if (IsHitDoorL(player, player3))
				{
					if (player3->GetHitflg() == false)
					{
						ptimer3 = 0;
						player3->DecreaseHp(-100);
						player3->SetActive(false);
					}
				}
			}

			// �h�A�ɓ�����Ɖ�]����(�v���C���[4)
			if (player4->GetHitflg() == false) {
				if (IsHitDoorR(player, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}

				if (IsHitDoorL(player, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}
			}

		}

		//�v���C���[�Q�̍U��
		if (player2->GetAttackflg() == TRUE)
		{
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


			// �h�A�ɓ�����Ɖ�]����i�v���C���[3�j
			if (player3->GetHitflg() == false) {
				if (IsHitDoorR2(player3, player2))
				{
					ptimer3 = 0;
					player3->DecreaseHp(-100);
					player3->SetActive(false);
				}

				if (IsHitDoorL2(player3, player2))
				{
					ptimer3 = 0;
					player3->DecreaseHp(-100);
					player3->SetActive(false);
				}
			}

			// �h�A�ɓ�����Ɖ�]����(�v���C���[4)
			if (player4->GetHitflg() == false) {
				if (IsHitDoorR2(player2, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}

				if (IsHitDoorL2(player2, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}
			}

		
		}

		//�v���C���[�R�̍U��
		if (player3->GetAttackflg() == TRUE)
		{
			// �h�A�ɓ�����Ɖ�]����i�v���C���[�P�j
			if (player->GetHitflg() == false) {
				if (IsHitDoorR3(player3, player))
				{
					ptimer = 0;
					player->DecreaseHp(-100);
					player->SetActive(false);
				}

				if (IsHitDoorL3(player3, player))
				{
					ptimer = 0;
					player->DecreaseHp(-100);
					player->SetActive(false);
				}
			}


			// �h�A�ɓ�����Ɖ�]����i�v���C���[3�j
			if (player2->GetHitflg() == false) {
				if (IsHitDoorR3(player3, player2))
				{
					ptimer2 = 0;
					player2->DecreaseHp(-100);
					player2->SetActive(false);
				}

				if (IsHitDoorL3(player3, player2))
				{
					ptimer2 = 0;
					player2->DecreaseHp(-100);
					player2->SetActive(false);
				}
			}


			// �h�A�ɓ�����Ɖ�]����(�v���C���[4)
			if (player4->GetHitflg() == false) {
				if (IsHitDoorR3(player3, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}

				if (IsHitDoorL3(player3, player4))
				{
					if (player4->GetHitflg() == false)
					{
						ptimer4 = 0;
						player4->DecreaseHp(-100);
						player4->SetActive(false);
					}
				}
			}


		}

		//�v���C���[4�̍U��
		if (player4->GetAttackflg() == TRUE)
		{
			// �h�A�ɓ�����Ɖ�]����i�v���C���[�P�j
			if (player->GetHitflg() == false) {
				if (IsHitDoorR4(player4, player))
				{
					ptimer = 0;
					player->DecreaseHp(-100);
					player->SetActive(false);
				}

				if (IsHitDoorL4(player4, player))
				{
					ptimer = 0;
					player->DecreaseHp(-100);
					player->SetActive(false);
				}
			}


			// �h�A�ɓ�����Ɖ�]����i�v���C���[2�j
			if (player2->GetHitflg() == false) {
				if (IsHitDoorR4(player4, player2))
				{
					ptimer2 = 0;
					player2->DecreaseHp(-100);
					player2->SetActive(false);
				}

				if (IsHitDoorL4(player4, player2))
				{
					ptimer2 = 0;
					player2->DecreaseHp(-100);
					player2->SetActive(false);
				}
			}


			// �h�A�ɓ�����Ɖ�]����(�v���C���[3)
			if (player3->GetHitflg() == false) {
				if (IsHitDoorR4(player4, player3))
				{
					if (player3->GetHitflg() == false)
					{
						ptimer3 = 0;
						player3->DecreaseHp(-100);
						player3->SetActive(false);
					}
				}

				if (IsHitDoorL4(player4, player3))
				{
					if (player3->GetHitflg() == false)
					{
						ptimer3 = 0;
						player3->DecreaseHp(-100);
						player3->SetActive(false);
					}
				}
			}


		}

		}

		for (int i = 0; i < 10; i++)
		{

			if ((item[i]->GetLocation().x < 200 || item[i]->GetLocation().x > 1160.0f) && item[i]->GetLocation().y <= 5)
			{
				item[i]->ResetY(0);
				item[i]->Initialize(GetRand(10));
				item[i]->Hitflg(false);
			}



			if (item[i] != nullptr)
			{
				if (IsHitCheckItem(player, item[i]))
				{
					player->SetActive(false);
					item[i] = nullptr;
				}
			}
			if (item[i] != nullptr)
			{
				if (IsHitItem(player2, item[i]))
				{
					player2->SetActive(false);
					item[i] = nullptr;
				}
			}

			if (item[i] != nullptr)
			{
				if (IsHitItem(player3, item[i]))
				{
					player3->SetActive(false);
					item[i] = nullptr;
				}
			}

			if (item[i] != nullptr)
			{
				if (IsHitItem(player4, item[i]))
				{
					player4->SetActive(false);
					item[i] = nullptr;
				}
			}


			if (item[i] != nullptr)
			{
				if (item[i]->GetLocation().y > 700)
				{
					item[i]->ResetY(0);
					item[i]->Initialize(GetRand(10));
				}
			}
			if (item[i] == nullptr)
			{
				item[i] = new Item;
				item[i]->Initialize(GetRand(10));
			}

			if (IsHitItem_Police(item[i], Pcar))
			{
				item[i]->Hitflg(true);
			}
		}

		//�v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
/*	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}*/

	if (p1win > 2)
	{
		Wineer = 1;
	}
	if (p2win > 2)
	{
		Wineer = 2;
	}
	if (p3win > 2)
	{
		Wineer = 3;
	}

	if (p4win > 2)
	{
		Wineer = 4;
	}

	if (p2win > 2 || p1win > 2||p3win>2||p4win>2)
	{
		//���U���g��ʂɍs��
		return eSceneType::E_RESULT;

	}
	else
	{
		return GetNowScene();

	}

}

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

		if (item[i] != nullptr)
		{
			item[i]->Draw();
		}
	}


	// �J�E���g�_�E���`��
	if (startflg == false)
	{
		DrawGraph(576, 296, number_img[startnum], TRUE);
	}
	

	//�v���C���[�̕`��
	player->Draw();
	//PAD2�v���C���[�̕`��
	player2->Draw();
	//PAD3 �v���C���[�̕`��
	player3->Draw();
	//PAD4 �v���C���[�̕`��
	player4->Draw();

	//�p�g�J�[�̕`��
	Pcar->Draw();

	//�v���C��[�O���̉�����܂��Ȃɂ����ĂȂ�
	if (winflg == true)
	{
		//�摜�𓧂���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, blackimg, FALSE);
		//�摜�������I���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(40);

		if (whowin == 2)
		{
			DrawString(300, 340, "Win!!", GetColor(255, 255, 255));
		}
		else if (whowin == 1)
		{
			DrawString(800, 340, "Win!!", GetColor(255, 255, 255));
		}

		switch (whowin)
		{
		case 1:
			DrawString(800, 300, "player1", GetColor(255, 255, 255));
			break;
		case 2:
			DrawString(280, 300, "player2", GetColor(255, 255, 255));
			break;
		case 3:
			DrawString(280, 300, "player3", GetColor(255, 255, 255));
			break;
		default:
			break;
		}

		for (int i = 0; i < p1win; i++)
		{
			DrawGraph(800+50*i, 400, starimg, TRUE);
		}

		for (int i = 0; i < p2win; i++)
		{
			DrawGraph(300+50*i , 400, starimg, TRUE);
		}

	}


}

//�I��������
void GameMainScene::Finalize()
{

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;
	
	player2->Finalize();
	delete player2;

	player3->Finalize();
	delete player3;

	player4->Finalize();
	delete player4;

	Pcar->Finalize();
	delete Pcar;
}


void GameMainScene::win()
{
	if (winflg == false)
	{
		//�O�񕪂̏����������L�^����
		//�v���C���[�P�����񂾏ꍇ
		//if (player->GetDeathFlg() == true)
		//{
		//	p2win++;
		//	whowin = 2;
		//}
		////�v���C���[�Q�����񂾏ꍇ
		//if (player2->GetDeathFlg() == true)
		//{
		//	p1win++;
		//	whowin = 1;
		//}

		//�Ō�܂ŏ����c�����l�Ƀv���X�P�_����
		for (int i = 0; i <= 3; i++)
		{
			if (whoLose[i] == 0)
			{
				switch (i)
				{
				case 0:
					p1win++;
					whowin = 1;
					break;
				case 1:
					p2win++;
					whowin = 2;
					break;
				case 2:
					p3win++;
					whowin = 3;
					break;
				case 3:
					p4win++;
					whowin = 4;
					break;
				default:
					break;
				}
			}
		}

		
	}

	winflg = true;

	if (winflg == true)
	{
		alpha+=2;
	}

	if (p1win < 2 || p2win < 2||p3win<2 || p4win<2)
	{
		if (alpha > 400) {

			//�I�u�W�F�N�g�̏�����
			player->Initialize(0, 400);
			player2->Initialize(1, 200);
			player3->Initialize(2, 650);
			player4->Initialize(3, 900);

			Pcar->Initialize();

			for (int i = 0; i < 10; i++)
			{
				item[i] = new Item;
				item[i]->Initialize(GetRand(10));
			}

			for (int i = 0; i <= 3; i++)
			{
				whoLose[i] = 0;
			}

			count = 0;
			timer = 0;

			startflg = false;
			starttimer = 0;
			startnum = 3;
			alpha = 0;
			winflg = false;
			wFlg = false;
		}
	}


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

bool GameMainScene::IsHitCheckP3(Player* p3, Policecar* car)
{

	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (car == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p3->GetLocation() - car->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p3->GetBoxSize() + car->GetBoxSize();

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


bool GameMainScene::IsHitCheckPlayer2(Player* p2, Player* p3)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p2->GetLocation() - p3->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p2->GetBoxSize() + p3->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}


bool GameMainScene::IsHitCheckPlayer3(Player* p, Player* p3)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - p3->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + p3->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}



// �v���C���[�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR(Player* p1, Player* p2)
{
	if (player->GetBflg() == true)
	{
		//�ʒu���̍������擾
		Vector2D diff_location = p1->GetDoorRLocation() - p2->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p1->GetDoorRSize() + p2->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	}
	

}
// �v���C���[�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL(Player* p1, Player* p2)
{
	if (player->GetXflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p1->GetDoorLLocation() - p2->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p1->GetDoorLSize() + p2->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}


// �v���C���[2�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR2(Player* p1, Player* p2)
{

	if (player2->GetBflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p2->GetDoorRLocation() - p1->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p2->GetDoorRSize() + p1->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}
// �v���C���[2�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL2(Player* p1, Player* p2)
{

	if (player2->GetXflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p2->GetDoorLLocation() - p1->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p2->GetDoorLSize() + p1->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}


// �v���C���[3�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR3(Player* p3, Player* p)
{

	if (player3->GetBflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p3->GetDoorRLocation() - p->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p3->GetDoorRSize() + p->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}
// �v���C���[2�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL3(Player* p3, Player* p)
{

	if (player3->GetXflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p3->GetDoorLLocation() - p->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p3->GetDoorLSize() + p->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}

// �v���C���[4�̃h�A�̓����蔻��i�E�j
bool GameMainScene::IsHitDoorR4(Player* p4, Player* p)
{

	if (player4->GetBflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p4->GetDoorRLocation() - p->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p4->GetDoorRSize() + p->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}
// �v���C���[2�̃h�A�̓����蔻��i���j
bool GameMainScene::IsHitDoorL4(Player* p4, Player* p)
{

	if (player4->GetXflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p4->GetDoorLLocation() - p->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p4->GetDoorLSize() + p->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}



bool GameMainScene::IsHitCheckItem(Player* p, Item* i)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - i->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + i->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

bool GameMainScene::IsHitItem(Player* p2, Item* i)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p2->GetLocation() - i->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p2->GetBoxSize() + i->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}


bool GameMainScene::IsHitItem_Police(Item* i, Policecar* p)
{
	//�ʒu���̍������擾
	Vector2D diff_location = i->GetLocation() - p->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = i->GetBoxSize() + p->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	

}

void GameMainScene::checkhum()
{
	howmany = 0;
	if (player->GetDeathFlg() == true)
	{
		whoLose[0] = 1;
	}
	if (player2->GetDeathFlg() == true)
	{
		whoLose[1] = 1;
	}
	if (player3->GetDeathFlg() == true)
	{
		whoLose[2] = 1;
	}
	if (player4->GetDeathFlg() == true)
	{
		whoLose[3] = 1;
	}

	//������ł�l���𐔂���
	for (int i = 0; i <= 3; i++)
	{
		if (whoLose[i] == 1)
		{
			howmany++;
		}
	}

	if (howmany >= 3)
	{
		wFlg = true;
	}

}