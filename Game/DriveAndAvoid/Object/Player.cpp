#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include<math.h>

int ax=0;

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
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
	ax = x;
	is_active = true;
	location = Vector2D(x, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
	playernum = pnum;
	playerd = 0;

	Acount = 0;
	Bflg = false;
	Xflg = false;
	Attackflg = false;
	DoorRangle = 0.0f;
	DoorLangle = 0.0f;
	Door2Rangle = 0.0f;
	Door2Langle = 0.0f;

	// �v���C���[�P�̃h�A�i�E�j
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(18.0f, 15.0f);

	// �v���C���[�P�̃h�A�i���j
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(35.0f, 15.0f);

	alpha = 0;

	//�摜�̓ǂݍ���
	if (pnum == 0)
	{
		image = LoadGraph("Resource/images/car2.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor_L.png");
		doorRimg = LoadGraph("Resource/images/Door_R.png");
		doorLimg = LoadGraph("Resource/images/Door_L.png");
	}
	else if(pnum==1)
	{
		//player2�摜�̓ǂݍ���
		image = LoadGraph("Resource/images/car3.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor2_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor2_L.png");
		doorRimg = LoadGraph("Resource/images/Door2_R.png");
		doorLimg = LoadGraph("Resource/images/Door2_L.png");


	}

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
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		Attackflg = false;
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

	//�R���̏���
	fuel -= speed;

	//������
	alpha++;
	

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
		DoorRlocation.x = location.x + 25;
		DoorRlocation.y = location.y + 2;
		Attackflg = true;
		Bflg = true;
		Acount = 0;
	}

	//�U�������i���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X, playernum) && Attackflg == false)
	{
		DoorLlocation.x = location.x - 55;
		DoorLlocation.y = location.y + 2;
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


	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//�`�揈��
void Player::Draw()
{

	DrawCircle(DoorRlocation.x, DoorRlocation.y, 3, GetColor(255, 255, 0), TRUE);

	if (Attackflg == false)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);


		//�ϐ��A���t�@��̗͂��ƂɔZ�䂳�ς��ă}�b�N�X�܂ŔZ�䂭�Ȃ����������x�H�������
		//����
		//�U�����������HP����֐���HP�̕ϐ������

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

	}
	else if (Attackflg == true && Xflg == true)
	{
		//�v���C���[�摜�̕`��i�U�����j
		DrawRotaGraphF(location.x, location.y, 1.0, angle, carLimg, TRUE);
		// �h�A�`��
		DrawRotaGraphF(location.x - 39, location.y - 2, 1.0, -5.2, doorLimg, TRUE);
	}

	switch (playerd)
	{
	case 0:
		//����
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "�E");
		break;
	case 1:
		//�E��
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "���I");
		break;
	case 2:
		//����
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "���I");

		break;
	case 3:
		//�E��
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "��I");
		break;
	case 4:
		//�E��
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "�E��");
		break;
	default:
		break;
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
	this->hp += value;
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

	location += direction;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1280.0f - 180.0f) || 
		(location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
	{
		location -= direction;
	}

	if (location.x > 1280 || location.x < 0)
	{
		location.x = 100;
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

	

}
