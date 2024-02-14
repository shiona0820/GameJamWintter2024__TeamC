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

	enemy = new Enemy* [10];
	Pcar = new Policecar;

	//�I�u�W�F�N�g�̏�����
	player->Initialize(0,400);
	player2->Initialize(1,200);

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
	p2win = 0;
	whowin = 0;
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
		if (player->GetDeathFlg() == true || player2->GetDeathFlg() == true)
		{
			win();
		}

		//�v���C���[�̍X�V
		player->Update();
		//�v���C���[�Q�̍X�V
		player2->Update();


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


		for (int i = 0; i < 10; i++)
		{

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
				if (item[i]->GetLocation().y > 700)
				{
					item[i]->ResetY(0);
				}
			}
			if (item[i] == nullptr)
			{
				item[i] = new Item;
				item[i]->Initialize(GetRand(10));
			}
		}

		//�v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
/*	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}*/
	}

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


	if (p2win > 2 || p1win > 2)
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

	//�p�g�J�[�̕`��
	Pcar->Draw();


	if (winflg == true)
	{
		//�摜�𓧂���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, blackimg, FALSE);
		//�摜�������I���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(40);
		DrawString(800, 300, "player1", GetColor(255, 255, 255));
		DrawString(280, 300, "player2", GetColor(255, 255, 255));

		if (whowin == 2)
		{
			DrawString(300, 340, "Win!!", GetColor(255, 255, 255));
		}
		else if (whowin == 1)
		{
			DrawString(800, 340, "Win!!", GetColor(255, 255, 255));
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


	Pcar->Finalize();
	delete Pcar;
}


void GameMainScene::win()
{
	if (winflg == false)
	{
		//�O�񕪂̏����������L�^����
		//�v���C���[�P�����񂾏ꍇ
		if (player->GetDeathFlg() == true)
		{
			p2win++;
			whowin = 2;
		}

		//�v���C���[�Q�����񂾏ꍇ
		if (player2->GetDeathFlg() == true)
		{
			p1win++;
			whowin = 1;
		}
	}

	winflg = true;

	if (winflg == true)
	{
		alpha+=2;
	}

	if (p2win < 2 || p1win < 2)
	{
		if (alpha > 400) {

			//�I�u�W�F�N�g�̏�����
			player->Initialize(0, 400);
			player2->Initialize(1, 200);

			Pcar->Initialize();

			for (int i = 0; i < 10; i++)
			{
				item[i] = new Item;
				item[i]->Initialize(GetRand(10));
			}
			count = 0;
			timer = 0;

			startflg = false;
			starttimer = 0;
			startnum = 3;
			alpha = 0;
			winflg = false;
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

	if (player2->GetBflg() == true)
	{

		//�ʒu���̍������擾
		Vector2D diff_location = p2->GetDoorLLocation() - p1->GetLocation();

		//�����蔻��T�C�Y�̑傫�����擾
		Vector2D box_ex = p2->GetDoorLSize() + p1->GetBoxSize();

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
