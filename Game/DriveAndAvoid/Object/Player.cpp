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

//初期化処理
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

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//操作不可状態であれば、自身を回転させる
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

	//燃料の消費
	fuel -= speed;

	//移動処理
	Movement();
	
	//加減速処理
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START,playernum))
	{
		is_active = false;
	}

	//バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,playernum) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y-y, 1.0, angle, image, TRUE);

	DrawCircle(location.x, location.y, 3, GetColor(255,0,0), TRUE);

	DrawFormatString(700, 700, GetColor(255, 255, 255), "y=%d",y);


	//バリアが生成されたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	switch (playerd)
	{
	case 0:
		//左下
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "左");
		break;
	case 1:
		//右下
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "右！");
		break;
	case 2:
		//左上
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "上！");

		break;
	case 3:
		//右上
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "下！");
		break;
	default:
		break;
	}

}

//終了処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

//バイア枚数取得処理
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

//バリアは有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
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

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 1280.0f - 180.0f) || 
		(location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	//LBボタンが押されたら、減速する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER, playernum) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RBボタンが押されたら、加速する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER, playernum) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}

//
void Player::direction(Vector2D xy)
{
	//左からぶつかった場合
	if (location.x > xy.x) {
			playerd	=	direction::LEFT;
	}

	//右からぶつかった場合
	if (location.x<xy.x) 
	{
		playerd = direction::RGIHT;
	}

	////上からぶつかった場合
	//if (location.y > xy.y)
	//{
	//	playerd = direction::UP;
	//}

	////下からぶつかった場合
	//if (location.y < xy.y)
	//{
	//	playerd = direction::UNDER;
	//}
	
}

void Player::Repulsion(int time)
{
	//time2 = GetNowCount();
	//t = (double)(time2 - time) / 10000.000;
	//v0 = sqrt(2.000 * g * y_max);//初速度を計算
	//v0 *= e;
	//y = (int)((v0 * t - 0.500 * g * t * t) * 480.000 / y_max);
	Vector2D move = Vector2D(0.0f);
	
	move = Vector2D(-10.0f,0.0f);



	switch (playerd)
	{
	case 0:
		//左からあたった場合
		angle = -DX_PI_F / 18;
		for (int i = 0; i < 10; i++)
		{
			location.x += 2;
		}
		break;
	case 1:
		//右から当たった場合
		angle = DX_PI_F / 18;
		for (int i = 0; i < 10; i++)
		{
			location.x -= 2;
		}
		break;
	case 2:
		//上からあたった場合
		for (int i = 0; i < 10; i++)
		{
			location.y -= 2;
		}

		break;
	case 3:
		//下
		for (int i = 0; i < 10; i++)
		{
			location.y += 2;
		}

		break;
	default:
		break;
	}


}