#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include<math.h>

#define e 0.800
#define g 9.807
#define y_max 2.000


Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{

}

Player::~Player()
{

}

//����������
void Player::Initialize(int pnum)
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
	playernum = pnum;
	playerd = 0;

	y = 0;
	t = 0;
	time2 = 0;
	v0 = 0;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1pol.bmp");

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

	//�ړ�����
	Movement();
	
	//����������
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START,playernum))
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,playernum) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
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
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y-y, 1.0, angle, image, TRUE);

	DrawCircle(location.x, location.y, 3, GetColor(255,0,0), TRUE);

	DrawFormatString(700, 700, GetColor(255, 255, 255), "y=%d",y);


	//�o���A���������ꂽ��A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	switch (playerd)
	{
	case 0:
		//����
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "��");
		break;
	case 1:
		//�E��
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "�E�I");
		break;
	case 2:
		//����
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "��I");

		break;
	case 3:
		//�E��
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "���I");
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
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT,playernum))
	{
		move += Vector2D(-1.0f, 0.0f);
			angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT, playernum))
	{
		move += Vector2D(1.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP, playernum))
	{
		move += Vector2D(0.0f, -1.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN, playernum))
	{
		move += Vector2D(0.0f, 1.0f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1280.0f - 180.0f) || 
		(location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
	{
		location -= move;
	}
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

//
void Player::direction(Vector2D xy)
{
	//������Ԃ������ꍇ
	if (location.x > xy.x) {
			playerd	=	direction::LEFT;
	}

	//�E����Ԃ������ꍇ
	if (location.x<xy.x) 
	{
		playerd = direction::RGIHT;
	}

	////�ォ��Ԃ������ꍇ
	//if (location.y > xy.y)
	//{
	//	playerd = direction::UP;
	//}

	////������Ԃ������ꍇ
	//if (location.y < xy.y)
	//{
	//	playerd = direction::UNDER;
	//}
	
}

void Player::Repulsion(int time)
{
	//time2 = GetNowCount();
	//t = (double)(time2 - time) / 10000.000;
	//v0 = sqrt(2.000 * g * y_max);//�����x���v�Z
	//v0 *= e;
	//y = (int)((v0 * t - 0.500 * g * t * t) * 480.000 / y_max);
	Vector2D move = Vector2D(0.0f);
	
	move = Vector2D(-10.0f,0.0f);



	switch (playerd)
	{
	case 0:
		//�����炠�������ꍇ
		angle = -DX_PI_F / 18;
		for (int i = 0; i < 10; i++)
		{
			location.x += 2;
		}
		break;
	case 1:
		//�E���瓖�������ꍇ
		angle = DX_PI_F / 18;
		for (int i = 0; i < 10; i++)
		{
			location.x -= 2;
		}
		break;
	case 2:
		//�ォ�炠�������ꍇ
		for (int i = 0; i < 10; i++)
		{
			location.y -= 2;
		}

		break;
	case 3:
		//��
		for (int i = 0; i < 10; i++)
		{
			location.y += 2;
		}

		break;
	default:
		break;
	}


}