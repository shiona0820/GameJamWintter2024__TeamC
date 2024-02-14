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

//初期化処理
void GameMainScene::Initialize()
{
	//高得点を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back1.bmp");
	audience_img = LoadGraph("Resource/images/audience.png");
	blackimg = LoadGraph("Resource/images/black.png");
	starimg = LoadGraph("Resource/images/star.png");
	LoadDivGraph("Resource/images/123.png", 3, 3, 1, 128, 128, number_img);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません?n");
	}

	/*if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}*/

	if (audience_img == -1)
	{
		throw("Resource/images/audience.pngがありません?");
	}

	//オブジェクトの生成
	player = new Player;
	player2 = new Player;

	enemy = new Enemy* [10];
	Pcar = new Policecar;

	//オブジェクトの初期化
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

	//初期化
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

//更新処理
eSceneType GameMainScene::Update()
{

	if (startflg == false)
	{
		// カウントダウン後にゲーム開始
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
		//三回分の勝ち負けを記録する
		//プレイヤー１か２が死んだ場合
		if (player->GetDeathFlg() == true || player2->GetDeathFlg() == true)
		{
			win();
		}

		//プレイヤーの更新
		player->Update();
		//プレイヤー２の更新
		player2->Update();


		//アイテムの更新
		for (int i = 0; i < 10; i++)
		{
			if (item[i] != nullptr)
			{
				item[i]->Update();
			}
		}

		//移動距離の更新
		mileage += 15;
		mileage2 += 2;

		/**
		敵生成処理
		countが60行ったら、timerが１増えてパトカーのｙが１増える
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

		//プレイヤーがダメージ食らった無敵時間
		if (ptimer > 3)
		{
			player2->Hitflg(false);
			ptimer = 0;
		}

		//プレイヤーがダメージ食らった無敵時間
		if (ptimer2 > 3)
		{
			player->Hitflg(false);
			ptimer2 = 0;
		}

		//当たり判定の確認
	//当たり判定の確認（プレイヤーとパトカー）
		if (IsHitCheckPlayer(player, player2))
		{

			if (flg == false)
			{
				flg = true;
			}

			player->Exclusion(player2->GetLocation());
			player2->Exclusion(player->GetLocation());

			//当たった時、相手がどこに当たったかと相手がどこ向いているのか渡す
			player->RepulsionX(player->GetLocation() - player2->GetLocation(), player2->GetDirection());
			player2->RepulsionX(player2->GetLocation() - player->GetLocation(), player->GetDirection());


		}

		//プレイヤー１とパトカーの当たり判定
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

		// HPが０になったら爆発する
		if (player->GetHp() <= 0)
		{
			player->Explosion();

		}
		if (player2->GetHp() <= 0)
		{
			player2->Explosion();

		}

		//攻撃の入力押したときだけ判定にする↓
		if (player->GetAttackflg() == TRUE)
		{
			//プレイヤー１の攻撃
			// ドアに当たると回転する(プレイヤー２)
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
			//プレイヤー２の攻撃
			// ドアに当たると回転する（プレイヤー１）
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

		//プレイヤーの燃料か体力が０未満なら、リザルトに遷移する
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
		//リザルト画面に行く
		return eSceneType::E_RESULT;

	}
	else
	{
		return GetNowScene();

	}

}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//観客の描画
	DrawGraph(1160, mileage2%720-720, audience_img, TRUE);
	DrawGraph(1160, mileage2%720, audience_img, TRUE);
	DrawTurnGraph(-80, mileage2%720-720, audience_img, TRUE);
	DrawTurnGraph(-80, mileage2%720, audience_img, TRUE);

	//敵の描画

	for (int i = 0; i < 10; i++)
	{

		if (item[i] != nullptr)
		{
			item[i]->Draw();
		}
	}


	// カウントダウン描画
	if (startflg == false)
	{
		DrawGraph(576, 296, number_img[startnum], TRUE);
	}
	

	//プレイヤーの描画
	player->Draw();
	//PAD2プレイヤーの描画
	player2->Draw();

	//パトカーの描画
	Pcar->Draw();


	if (winflg == true)
	{
		//画像を透かす
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, blackimg, FALSE);
		//画像透かし終わり
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

//終了時処理
void GameMainScene::Finalize()
{

	//動的確保したオブジェクトを削除する
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
		//三回分の勝ち負けを記録する
		//プレイヤー１が死んだ場合
		if (player->GetDeathFlg() == true)
		{
			p2win++;
			whowin = 2;
		}

		//プレイヤー２が死んだ場合
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

			//オブジェクトの初期化
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

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}


//当たり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheckP1(Player* p, Policecar* car)
{

	//敵情報が無ければ、当たり判定を無視する
	if (car == nullptr)
	{
		return false;
	}

	//位置情報の差分を取得
	Vector2D diff_location = p->GetLocation() - car->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + car->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

bool GameMainScene::IsHitCheckP2(Player* p2, Policecar* car)
{

	//敵情報が無ければ、当たり判定を無視する
	if (car == nullptr)
	{
		return false;
	}

	//位置情報の差分を取得
	Vector2D diff_location = p2->GetLocation() - car->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p2->GetBoxSize() + car->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

bool GameMainScene::IsHitCheckPlayer(Player* p, Player* p2)
{
	//位置情報の差分を取得
	Vector2D diff_location = p->GetLocation() - p2->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize()+p2->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// プレイヤーのドアの当たり判定（右）
bool GameMainScene::IsHitDoorR(Player* p1, Player* p2)
{
	if (player->GetBflg() == true)
	{
		//位置情報の差分を取得
		Vector2D diff_location = p1->GetDoorRLocation() - p2->GetLocation();

		//当たり判定サイズの大きさを取得
		Vector2D box_ex = p1->GetDoorRSize() + p2->GetBoxSize();

		//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	}
	

}

// プレイヤーのドアの当たり判定（左）
bool GameMainScene::IsHitDoorL(Player* p1, Player* p2)
{
	if (player->GetXflg() == true)
	{

		//位置情報の差分を取得
		Vector2D diff_location = p1->GetDoorLLocation() - p2->GetLocation();

		//当たり判定サイズの大きさを取得
		Vector2D box_ex = p1->GetDoorLSize() + p2->GetBoxSize();

		//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}

// プレイヤー2のドアの当たり判定（右）
bool GameMainScene::IsHitDoorR2(Player* p1, Player* p2)
{

	if (player2->GetBflg() == true)
	{

		//位置情報の差分を取得
		Vector2D diff_location = p2->GetDoorRLocation() - p1->GetLocation();

		//当たり判定サイズの大きさを取得
		Vector2D box_ex = p2->GetDoorRSize() + p1->GetBoxSize();

		//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}

// プレイヤー2のドアの当たり判定（左）
bool GameMainScene::IsHitDoorL2(Player* p1, Player* p2)
{

	if (player2->GetBflg() == true)
	{

		//位置情報の差分を取得
		Vector2D diff_location = p2->GetDoorLLocation() - p1->GetLocation();

		//当たり判定サイズの大きさを取得
		Vector2D box_ex = p2->GetDoorLSize() + p1->GetBoxSize();

		//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	}

}

bool GameMainScene::IsHitCheckItem(Player* p, Item* i)
{
	//位置情報の差分を取得
	Vector2D diff_location = p->GetLocation() - i->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + i->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

bool GameMainScene::IsHitItem(Player* p2, Item* i)
{
	//位置情報の差分を取得
	Vector2D diff_location = p2->GetLocation() - i->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p2->GetBoxSize() + i->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}
