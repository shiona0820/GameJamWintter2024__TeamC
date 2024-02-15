#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include<math.h>


Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr),alpha(0)
{
	playerd = 0;
	playernum = 0;
}

Player::~Player()
{

}

//����������
void Player::Initialize(int pnum,float x)
{
	is_active = true;
	location = Vector2D(x, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 600;
	fuel = 20000;
	barrier_count = 3;
	playernum = pnum;
	playerd = 0;

	Acount = 0;
	Bflg = false;
	Xflg = false;
	Attackflg = false;
	hit_flg = false;
	DoorRangle = 0.0f;
	DoorLangle = 0.0f;
	Door2Rangle = 0.0f;
	Door2Langle = 0.0f;

	// �v���C���[�P�̃h�A�i�E�j
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(10.0f, 15.0f);

	// �v���C���[�P�̃h�A�i���j
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(35.0f, 15.0f);

	alpha = 0;
	hpcheck = 0;

	death_flg = false;

	// �����A�j���[�V�����p�J�E���g
	explosion_count = 0;
	exNum = 0;

	//�摜�̓ǂݍ���
	switch (pnum)
	{
	case 0:
		image = LoadGraph("Resource/images/car2.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor_L.png");
		doorRimg = LoadGraph("Resource/images/Door_R.png");
		doorLimg = LoadGraph("Resource/images/Door_L.png");
		break;
	case 1:
		//player2�摜�̓ǂݍ���
		image = LoadGraph("Resource/images/car3.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor2_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor2_L.png");
		doorRimg = LoadGraph("Resource/images/Door2_R.png");
		doorLimg = LoadGraph("Resource/images/Door2_L.png");
		break;
	case 2:
		//player3�摜�̓ǂݍ���
		image = LoadGraph("Resource/images/car1.png");
		carRimg = LoadGraph("Resource/images/OpenDoor3_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor3_L.png");
		doorRimg = LoadGraph("Resource/images/Door3_R.png");
		doorLimg = LoadGraph("Resource/images/Door3_L.png");
		break;
	case 3:
		//player4�摜�̓ǂݍ���
		image = LoadGraph("Resource/images/car4.png");
		carRimg = LoadGraph("Resource/images/OpenDoor4_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor4_L.png");
		doorRimg = LoadGraph("Resource/images/Door4_R.png");
		doorLimg = LoadGraph("Resource/images/Door4_L.png");
		break;
	default:
		break;
	}



	LoadDivGraph("Resource/images/explosion.png", 3, 3, 1, 200, 200, explosion_img);

	crackimg = LoadGraph("Resource/images/crack.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	//hp�̒l�����炤
	hpcheck = hp;

	if (hp <= 0)
	{
		death_flg = true;
	}

	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		location.y++;
		//Attackflg = false;
		Bflg = false;
		Xflg = false;
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	////�R���̏���
	//fuel -= speed;
	

	//�ړ�����
	Movement();
	
	//����������
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START,playernum))
	{
		is_active = false;
	}

	//�U�������i�E�j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B, playernum) && Attackflg == false)
	{
		//DoorRlocation.x = location.x + 25;
		//DoorRlocation.y = location.y + 4;
		Attackflg = true;
		Bflg = true;
		Acount = 0;
	}

	//�U�������i���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X, playernum) && Attackflg == false)
	{
		//DoorLlocation.x = location.x - 55;
		//DoorLlocation.y = location.y + 4;
		Attackflg = true;
		Xflg = true;
		Acount = 0;
	}

	// ����������h�A�����
	if (Attackflg == true)
	{
		Acount++;
		if (Acount >= 20)
		{
			Acount = 0;
			Attackflg = false;
			Bflg = false;
			Xflg = false;

		}
	}


	DoorRlocation.x = location.x + 25;
	DoorRlocation.y = location.y + 4;
	DoorLlocation.x = location.x - 55;
	DoorLlocation.y = location.y + 4;


	//��������
	//�ϐ��A���t�@��̗͂��ƂɔZ�䂳�ς��ă}�b�N�X�܂ŔZ�䂭�Ȃ����������x�H�������
	//����
	//�U�����������HP����֐���HP�̕ϐ������


}

//�`�揈��
void Player::Draw()
{

	DrawCircle(DoorRlocation.x, DoorRlocation.y, 3, GetColor(255, 255, 0), TRUE);
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	if (Attackflg == false && exNum < 2)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

		//�摜�𓧂���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//�̗͕\�� : �Ђъ���
		DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
		//�摜�������I���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else if (Attackflg == true && Bflg == true)
	{

		//�v���C���[�摜�̕`��i�U�����j
		DrawRotaGraphF(location.x, location.y, 1.0, angle, carRimg, TRUE);
		// �h�A�`��
		DrawRotaGraphF(location.x + 39, location.y - 2, 1.0, 5.2, doorRimg, TRUE);
		//�摜�𓧂���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//�̗͕\�� : �Ђъ���
		DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
		//�摜�������I���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else if (Attackflg == true && Xflg == true)
	{
		//�v���C���[�摜�̕`��i�U�����j
		DrawRotaGraphF(location.x, location.y, 1.0, angle, carLimg, TRUE);
		// �h�A�`��
		DrawRotaGraphF(location.x - 39, location.y - 2, 1.0, -5.2, doorLimg, TRUE);
		//�摜�𓧂���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//�̗͕\�� : �Ђъ���
		DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
		//�摜�������I���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �����A�j���[�V�����̕`��
	if (hp <= 0)
	{
		DrawGraph(location.x - 100, location.y - 100, explosion_img[exNum], TRUE);
	}

}

//�I������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{

		hit_flg = true;
		this->hp += value;
		alpha += 42.5;
	
}

bool Player::GetHitflg() const
{
	return this->hit_flg;
}

bool Player::GetDeathFlg() const
{
	return this->death_flg;
}

void Player::Hitflg(bool flg)
{
	hit_flg = flg;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�v���C���[�P�̃h�A�ʒu���擾�����i�E�j
Vector2D Player::GetDoorRLocation() const
{
	return this->DoorRlocation;
}

//�v���C���[�P�̃h�A�����蔻��̑傫���擾�����i�E�j
Vector2D Player::GetDoorRSize() const
{
	return this->DoorR_size;
}

//�v���C���[�P�̃h�A�ʒu���擾�����i���j
Vector2D Player::GetDoorLLocation() const
{
	return this->DoorLlocation;
}

//�v���C���[�P�̃h�A�����蔻��̑傫���擾�����i���j
Vector2D Player::GetDoorLSize() const
{
	return this->DoorL_size;
}


//�v���C���[�P�̃h�A�����蔻��̑傫���擾�����i���j
int Player::GetAttackflg() const
{
	return this->Attackflg;
}

//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

//�o�C�A�����擾����
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

//�o���A�͗L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);

}

// �{�^���t���O���擾
int Player::GetBflg() const
{
	return this->Bflg;
}
int Player::GetXflg() const
{
	return this->Xflg;
}


//�ړ�����
void Player::Movement()
{
	direction = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT,playernum))
	{
		direction = Vector2D(-1.0f, 0.0f);
			angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT, playernum))
	{
		direction = Vector2D(1.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP, playernum))
	{
		direction = Vector2D(0.0f, -1.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN, playernum))
	{
		direction = Vector2D(0.0f, 1.0f);
	}

	location += direction*2;


	if (location.x >= 1280)
	{
		location.x = 1280;
	}

	//�ϋq�̂Ƃ���ɓ�������X�s�[�h������E
	if ((location.x < 120) || (location.x >= 1160.0f))
	{
		location -= direction;

	}

	//��ʊO�ɏo�Ȃ��悤��
	if (location.x < 0)
	{
		location.x = 100;
	}
	if (location.x > 1280)
	{
		location.x = 1000;
	}
	if (location.y < 0)
	{
		location.y = 100;
	}

}

//
void Player::Exclusion(Vector2D loce)
{
	//�Ԃɓ���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= loce.x) ||
		(location.y < box_size.y) || (location.y >= loce.y-box_size.y))
	{
		location -= direction;
	}


}

//�������擾
Vector2D Player::GetDirection() const
{
	return this->direction;
}

//����������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER, playernum) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER, playernum) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}

//�Ԃ���ꂽ���̏���
void Player::RepulsionX(Vector2D xy, Vector2D d)
{
	dire = direction;

	//���E�̔���
	if (dire.x != 0)
	{
		if (xy.x < 0)
		{
			playerd = 0;

			//����͉E
			//����������direction���E�������Ă����Ȃ�
			if (dire.x == 1 && dire.y == 0)
			{
				dire = dire * (-1.0f * 50);
				location += dire;
			}
			else
			{
				dire = d * 50;
				location += dire;
				angle = DX_PI_F / 18;
			}
		}
		else if (xy.x > 0)
		{
			playerd = 1;

			//����͍�
			//����������direction�����������Ă����Ȃ�
			if (dire.x == -1 && dire.y == 0)
			{
				dire = dire * (-1.0f * 50);
				location += dire;
			}
			else
			{
				dire = d * 50;
				location += dire;
				
			}

		}
	}

	//�㉺�̔���
	if (dire.y != 0 && dire.x == 0)
	{
		if (xy.y < 0)
		{
			playerd = 2;

			//����͉�
			//����������direction�����������Ă����Ȃ�
			if (dire.x == 0 && dire.y == 1)
			{
				dire = dire * (-1.0f * 50);
				location += dire;
			}
			else
			{
				dire = d * 40;
				location += dire;
			}

		}
		else if (xy.y > 0)
		{
			playerd = 3;

			//����͏�
			//����������direction����������Ă����Ȃ�
			if (dire.x == 0 && dire.y == -1)
			{
				dire = dire * (-1.0f * 40);
				location += dire;
			}
			else
			{
				dire = d * 40;
				location += dire;
			}


		}
	}

	if (dire.x == 0 && dire.y == 0)
	{
		dire = d * 40;
		location += dire;

	}

}

// �����A�j���[�V����
void Player::Explosion()
{
	explosion_count++;
	switch (explosion_count)
	{
	case(0):
		exNum = 0;
		break;
	case(10):
		exNum = 1;
		break;
	case(20):
		exNum = 2;
		break;
	default:
		break;
	}

}