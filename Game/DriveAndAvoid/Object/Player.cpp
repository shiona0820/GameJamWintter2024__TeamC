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

//初期化処理
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

	// プレイヤー１のドア（右）
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(18.0f, 15.0f);

	// プレイヤー１のドア（左）
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(35.0f, 15.0f);

	//画像の読み込み
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
		//player2画像の読み込み
		image = LoadGraph("Resource/images/car3.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor2_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor2_L.png");
		doorRimg = LoadGraph("Resource/images/Door2_R.png");
		doorLimg = LoadGraph("Resource/images/Door2_L.png");


	}


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

	//攻撃処理（右）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B, playernum) && Attackflg == false)
	{
		DoorRlocation.x = location.x + 25;
		DoorRlocation.y = location.y + 2;
		Attackflg = true;
		Bflg = true;
		Acount = 0;
	}

	//攻撃処理（左）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X, playernum) && Attackflg == false)
	{
		DoorLlocation.x = location.x - 55;
		DoorLlocation.y = location.y + 2;
		Attackflg = true;
		Xflg = true;
		Acount = 0;
	}

	// 少ししたらドアを閉じる
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

	DrawCircle(DoorRlocation.x, DoorRlocation.y, 3, GetColor(255, 255, 0), TRUE);

	if (Attackflg == false)
	{
		//プレイヤー画像の描画
		DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	}
	else if (Attackflg == true && Bflg == true)
	{

		//プレイヤー画像の描画（攻撃時）
		DrawRotaGraphF(location.x, location.y, 1.0, angle, carRimg, TRUE);
		// ドア描画
		DrawRotaGraphF(location.x + 39, location.y - 2, 1.0, 5.2, doorRimg, TRUE);

	}
	else if (Attackflg == true && Xflg == true)
	{
		//プレイヤー画像の描画（攻撃時）
		DrawRotaGraphF(location.x, location.y, 1.0, angle, carLimg, TRUE);
		// ドア描画
		DrawRotaGraphF(location.x - 39, location.y - 2, 1.0, -5.2, doorLimg, TRUE);
	}

	switch (playerd)
	{
	case 0:
		//左下
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "右");
		break;
	case 1:
		//右下
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "左！");
		break;
	case 2:
		//左上
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "下！");

		break;
	case 3:
		//右上
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "上！");
		break;
	case 4:
		//右上
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "右上");
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

//プレイヤー１のドア位置情報取得処理（右）
Vector2D Player::GetDoorRLocation() const
{
	return this->DoorRlocation;
}

//プレイヤー１のドア当たり判定の大きさ取得処理（右）
Vector2D Player::GetDoorRSize() const
{
	return this->DoorR_size;
}

//プレイヤー１のドア位置情報取得処理（左）
Vector2D Player::GetDoorLLocation() const
{
	return this->DoorLlocation;
}

//プレイヤー１のドア当たり判定の大きさ取得処理（左）
Vector2D Player::GetDoorLSize() const
{
	return this->DoorL_size;
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
	direction = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
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

	//画面外に行かないように制限する
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
	//車に入らないように制限する
	if ((location.x < box_size.x) || (location.x >= loce.x) ||
		(location.y < box_size.y) || (location.y >= loce.y-box_size.y))
	{
		location -= direction;
	}


}

//向きを取得
Vector2D Player::GetDirection() const
{
	return this->direction;
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

//ぶつかられた時の処理
void Player::RepulsionX(Vector2D xy, Vector2D d)
{
	dire = direction;

	//左右の判定
	if (dire.x != 0)
	{
		if (xy.x < 0)
		{
			playerd = 0;

			//相手は右
			//もし自分のdirectionが右を向いていたなら
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

			//相手は左
			//もし自分のdirectionが左を向いていたなら
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

	//上下の判定
	if (dire.y != 0 && dire.x == 0)
	{
		if (xy.y < 0)
		{
			playerd = 2;

			//相手は下
			//もし自分のdirectionが下を向いていたなら
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

			//相手は上
			//もし自分のdirectionが上を向いていたなら
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
