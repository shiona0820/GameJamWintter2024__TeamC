#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Object/Policecar.h"
#include "../Item.h"


class GameMainScene : public SceneBase
{
private:
	int high_score;     //ハイスコア
	int back_ground;    //背景画像
	int barrier_image;  //バリア画像
	int mileage;        //走行距離
	int enemy_image[3]; //敵画像
	int enemy_count[3]; //通り過ぎた敵カウント
	Player* player;     //プレイヤー
	Player* player2;     //プレイヤー2
	Enemy** enemy;       //敵
	Policecar* Pcar;     //パトカー
	Item* item;
	int count;          //６０回数える
	int timer;          //countが６０になったら１数える

	int time;//アクション起きた時の時間を渡す用
	bool flg;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();

	//当たり判定
	//bool IsHitCheck(Player* p, Enemy* e);
	bool IsHitCheckPlayer(Player* p, Player* p2);
	bool IsHitCheckP1(Player* p,Policecar* car);
	bool IsHitCheckP2(Player* p2,Policecar* car);

	// ドアの当たり判定
	bool IsHitDoorR(Player* p1,Player* p2);
	bool IsHitDoorL(Player* p1,Player* p2);

	// ドアの当たり判定（プレイヤー２）
	bool IsHitDoorR2(Player* p1, Player* p2);
	bool IsHitDoorL2(Player* p1, Player* p2);
};