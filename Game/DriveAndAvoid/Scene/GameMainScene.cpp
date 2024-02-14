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

//初期化処理
void GameMainScene::Initialize()
{
	//高得点を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back1.bmp");
	audience_img = LoadGraph("Resource/images/audience.png");

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

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	//初期化
	count = 0;
	timer = 0;

}

//更新処理
eSceneType GameMainScene::Update()
{


	//プレイヤーの更新
	player->Update();
	//プレイヤー２の更新
	player2->Update();

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
		ptimer= 0;
	}


			//当たり判定の確認
		//当たり判定の確認（プレイヤーとパトカー）
			if (IsHitCheckPlayer(player,player2))
			{

				if (flg == false)
				{
					flg = true;
				}

				player->Exclusion(player2->GetLocation());
				player2->Exclusion(player->GetLocation());

				//当たった時、相手がどこに当たったかと相手がどこ向いているのか渡す
				player->RepulsionX(player->GetLocation() - player2->GetLocation(),player2->GetDirection());
				player2->RepulsionX(player2->GetLocation() - player->GetLocation(),player->GetDirection());


			}

			//プレイヤー１とパトカーの当たり判定
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



				//プレイヤーの燃料か体力が０未満なら、リザルトに遷移する
		/*	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
			{
				return eSceneType::E_RESULT;
			}*/
			return GetNowScene();

}


			////当たり判定の確認
			//if (IsHitCheck(player,enemy[i]))
			//{
			//	player -> SetActive(false);
			//		player -> DecreaseHp(-50.0f);
			//		enemy[i] -> Finalize();
			//		delete enemy[i];
			//		enemy[i] = nullptr;
			//}
			


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
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//プレイヤーの描画
	player->Draw();
	//PAD2プレイヤーの描画
	player2->Draw();

	//パトカーの描画
	Pcar->Draw();

}

//終了時処理
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	//リザルトデータの書き込み
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Rsource/dat/result_data.csvが開けません\n");
	}

	//スコアを保存
	fprintf(fp, "%d,\n", score);

	//避けた和人得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
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

////当たり判定処理（プレイヤーと敵）
//bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
//{
//	////プレイヤーがバリアを貼っていたら、当たり判定を無視する
//	//if (p->IsBarrier())
//	//{
//	//	return false;
//	//}
//
//	//敵情報が無ければ、当たり判定を無視する
//	if (e == nullptr)
//	{
//		return false;
//	}
//
//	//位置情報の差分を取得
//	Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//当たり判定サイズの大きさを取得
//	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
//	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}


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
	//位置情報の差分を取得
	Vector2D diff_location = p1->GetDoorRLocation() - p2->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p1->GetDoorRSize() + p2->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// プレイヤーのドアの当たり判定（左）
bool GameMainScene::IsHitDoorL(Player* p1, Player* p2)
{
	//位置情報の差分を取得
	Vector2D diff_location = p1->GetDoorLLocation() - p2->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p1->GetDoorLSize() + p2->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// プレイヤー2のドアの当たり判定（右）
bool GameMainScene::IsHitDoorR2(Player* p1, Player* p2)
{
	//位置情報の差分を取得
	Vector2D diff_location = p2->GetDoorRLocation() - p1->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p2->GetDoorRSize() + p1->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

// プレイヤー2のドアの当たり判定（左）
bool GameMainScene::IsHitDoorL2(Player* p1, Player* p2)
{
	//位置情報の差分を取得
	Vector2D diff_location = p2->GetDoorLLocation() - p1->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p2->GetDoorLSize() + p1->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}