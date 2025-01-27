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

//初期化処理
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

	survival_flg = true;

	blinkingcun = 0;
	blinking_flg = false;

	Acount = 0;
	Bflg = false;
	Xflg = false;
	Attackflg = false;
	hit_flg = false;
	DoorRangle = 0.0f;
	DoorLangle = 0.0f;
	Door2Rangle = 0.0f;
	Door2Langle = 0.0f;

	// プレイヤー１のドア（右）
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(10.0f, 15.0f);

	// プレイヤー１のドア（左）
	DoorRlocation = Vector2D(x, 380.0f);
	DoorR_size = Vector2D(35.0f, 15.0f);

	alpha = 0;
	hpcheck = 0;

	death_flg = false;

	// 爆発アニメーション用カウント
	explosion_count = 0;
	exNum = 0;

	sliponce = false;

	//SE,BGM
	explosion_sound = LoadSoundMem("Resource/sound/explosion.mp3");
	blow_sound = LoadSoundMem("Resource/sound/blow.mp3");
	taiatari_sound = LoadSoundMem("Resource/sound/taiatari.mp3");
	slip_sound = LoadSoundMem("Resource/sound/slip.mp3");
	//音量設定
	ChangeVolumeSoundMem(255, explosion_sound);
	ChangeVolumeSoundMem(255, blow_sound);
	ChangeVolumeSoundMem(255, taiatari_sound);
	ChangeVolumeSoundMem(255, taiatari_sound);

	//画像の読み込み
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
		//player2画像の読み込み
		image = LoadGraph("Resource/images/car3.bmp");
		carRimg = LoadGraph("Resource/images/OpenDoor2_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor2_L.png");
		doorRimg = LoadGraph("Resource/images/Door2_R.png");
		doorLimg = LoadGraph("Resource/images/Door2_L.png");
		break;
	case 2:
		//player3画像の読み込み
		image = LoadGraph("Resource/images/car1.png");
		carRimg = LoadGraph("Resource/images/OpenDoor3_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor3_L.png");
		doorRimg = LoadGraph("Resource/images/Door3_R.png");
		doorLimg = LoadGraph("Resource/images/Door3_L.png");
		break;
	case 3:
		//player4画像の読み込み
		image = LoadGraph("Resource/images/car4.png");
		carRimg = LoadGraph("Resource/images/OpenDoor4_R.png");
		carLimg = LoadGraph("Resource/images/OpenDoor4_L.png");
		doorRimg = LoadGraph("Resource/images/Door4_R.png");
		doorLimg = LoadGraph("Resource/images/Door4_L.png");
		break;
	default:
		break;

		StopSoundMem(serif_sound);
	}

	serif = LoadGraph("Resource/images/serif.png");
	serif2 = LoadGraph("Resource/images/serif2.png");
	serif_sound= LoadSoundMem("Resource/sound/黄色い悲鳴.mp3");

	serifFlg = false;
	serifcount = 0;

	LoadDivGraph("Resource/images/explosion.png", 3, 3, 1, 200, 200, explosion_img);

	crackimg = LoadGraph("Resource/images/crack.png");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{

	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y, playernum))
	{
		hp = -1;
	}
	

	if (survival_flg == true)
	{




		//hpの値をもらう
		hpcheck = hp;

		if (hp <= 0)
		{
			serifFlg = false;
			death_flg = true;
		}

		//操作不可状態であれば、自身を回転させる
		if (!is_active && exNum <= 2)
		{
			if (sliponce == false)
			{
					//スリップの音
					PlaySoundMem(slip_sound, DX_PLAYTYPE_BACK, TRUE);
					sliponce = true;
				
			}

			location.y++;

			//Attackflg = false;
			Bflg = false;
			Xflg = false;
			angle += DX_PI_F / 24.0f;
			speed = 1.0f;
			if (hit_flg == true)
			{
				blinkingcun++;
				switch (blinkingcun)
				{
				case(1):
					blinking_flg = true;
					break;
				case(3):
					blinking_flg = false;
					break;
				case(6):
					blinkingcun = 0;
					break;
				default:
					break;
				}
			}
			if (angle >= DX_PI_F * 4.0f)
			{
				is_active = true;
			}
			return;
		}

		if (CheckSoundMem(slip_sound) == false)
		{
			sliponce = false;
		}

		////燃料の消費
		//fuel -= speed;


		//移動処理
		Movement();

		//加減速処理
		Acceleration();

		if (InputControl::GetButtonDown(XINPUT_BUTTON_START, playernum))
		{
			is_active = false;
		}

		//攻撃処理（右）
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B, playernum) && Attackflg == false)
		{
			PlaySoundMem(blow_sound, DX_PLAYTYPE_BACK, TRUE);
			//DoorRlocation.y = location.y + 4;
			Attackflg = true;
			Bflg = true;
			Acount = 0;
		}

		//攻撃処理（左）
		if (InputControl::GetButtonDown(XINPUT_BUTTON_X, playernum) && Attackflg == false)
		{
			PlaySoundMem(blow_sound, DX_PLAYTYPE_BACK, TRUE);
			//DoorLlocation.x = location.x - 55;
			//DoorLlocation.y = location.y + 4;
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
				//StopSoundMem(blow_sound);
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


		if (hit_flg == true)
		{
			blinkingcun++;
			switch (blinkingcun)
			{
			case(1):
				blinking_flg = true;
				break;
			case(3):
				blinking_flg = false;
				break;
			case(6):
				blinkingcun = 0;
				break;
			default:
				break;
			}
		}
		else
		{
			blinkingcun = 0;
			blinking_flg = false;
		}

	}
}

//描画処理
void Player::Draw()
{
	if (survival_flg == true)
	{

		//DrawCircle(DoorRlocation.x, DoorRlocation.y, 3, GetColor(255, 255, 0), TRUE);
		////プレイヤー画像の描画
		if (blinking_flg == true)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
		else
		{
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

		}

		if (Attackflg == false/* && exNum < 2*/)
		{
			
			// 無敵時間中
			if (blinking_flg == true)
			{
				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				//点滅
				DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				//体力表示 : ひび割れ
				DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}
			else
			{
				//プレイヤー画像の描画
				DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				//体力表示 : ひび割れ
				DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}

		}
		else if (Attackflg == true && Bflg == true)
		{

			// 無敵時間中
			if (blinking_flg == true)
			{

				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				//プレイヤー画像の描画（攻撃時）
				DrawRotaGraphF(location.x, location.y, 1.0, angle, carRimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				
			}
			else
			{
				//プレイヤー画像の描画（攻撃時）
				DrawRotaGraphF(location.x, location.y, 1.0, angle, carRimg, TRUE);
				// ドア描画
				DrawRotaGraphF(location.x + 39, location.y - 2, 1.0, 5.2, doorRimg, TRUE);
				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				//体力表示 : ひび割れ
				DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}


		}
		else if (Attackflg == true && Xflg == true)
		{

			if (blinking_flg == true)
			{
				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				//プレイヤー画像の描画（攻撃時）
				DrawRotaGraphF(location.x, location.y, 1.0, angle, carLimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				//プレイヤー画像の描画（攻撃時）
				DrawRotaGraphF(location.x, location.y, 1.0, angle, carLimg, TRUE);
				// ドア描画
				DrawRotaGraphF(location.x - 39, location.y - 2, 1.0, -5.2, doorLimg, TRUE);
				//画像を透かす
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				//体力表示 : ひび割れ
				DrawRotaGraphF(location.x, location.y, 1.0, angle, crackimg, TRUE);
				//画像透かし終わり
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

	}

	if (serifFlg==true)
	{

		PlaySoundMem(serif_sound,DX_PLAYTYPE_LOOP, FALSE);

		//悲鳴つける
		if (serifcount < 50)
		{
			DrawGraph(location.x - 200, location.y - 200, serif, TRUE);
		}
		
		if (serifcount >= 50)
		{
			DrawGraph(location.x - 200, location.y - 200, serif2, TRUE);
			if (serifcount > 100)
			{
				serifcount = 0;
			}
		}
		serifcount++;

	

	
		
	}
	else if(serifFlg==false)
	{
		StopSoundMem(serif_sound);
	}
		// 爆発アニメーションの描画
		if (hp <= 0 && exNum <= 2)
		{
			DrawGraph(location.x - 100, location.y - 100, explosion_img[exNum], TRUE);
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

	DeleteSoundMem(serif_sound);
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

void Player::deathset(float x)
{
	this->location.x = x;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	//if (CheckSoundMem(slip_sound) == false)
	//{
	//	PlaySoundMem(slip_sound, DX_PLAYTYPE_BACK, TRUE);
	//}
		hit_flg = true;
		this->hp += value;
		alpha += 42.5;
	
}

bool Player::GetHitflg() const
{
	return this->hit_flg;
}

bool Player::GetSurvival_flg() const
{
	return this->survival_flg;
}

bool Player::GetDeathFlg() const
{
	return this->death_flg;
}

void Player::Hitflg(bool flg)
{
	hit_flg = flg;
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


//プレイヤー１のドア当たり判定の大きさ取得処理（左）
int Player::GetAttackflg() const
{
	return this->Attackflg;
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

// ボタンフラグを取得
int Player::GetBflg() const
{
	return this->Bflg;
}

int Player::GetXflg() const
{
	return this->Xflg;
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


		//観客のところに入ったらスピードが減る右
	if ((location.x < 120) || (location.x >= 1160.0f))
	{
		location += direction/2;
		serifFlg = true;
	}
	else
	{
		serifcount = 0;
		location += direction * 2;

		serifFlg = false;
	}


	if (location.x >= 1280)
	{
		location.x = 1280;
	}



	//画面外に出ないように
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
	if (CheckSoundMem(taiatari_sound) == false)
	{
		//車がぶつかるSE
		PlaySoundMem(taiatari_sound, DX_PLAYTYPE_BACK, TRUE);
	}

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

	if (dire.x == 0 && dire.y == 0)
	{
		dire = d * 40;
		location += dire;

	}

}

// 爆発アニメーション
void Player::Explosion()
{
	explosion_count++;
	if (CheckSoundMem(explosion_sound) == false)
	{
		if (death_flg == false)
		{
			PlaySoundMem(explosion_sound, DX_PLAYTYPE_BACK, TRUE);
		}
	}
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
		survival_flg = false;
		break;
	case(80):
		exNum = 1;
	case(100):
		exNum = 3;
		StopSoundMem(explosion_sound);
		break;
	default:
		break;
	}

}