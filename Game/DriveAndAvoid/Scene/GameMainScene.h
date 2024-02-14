#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Object/Policecar.h"
#include "../Item.h"


class GameMainScene : public SceneBase
{
private:
	bool startflg;		// ゲーム開始フラグ
	int starttimer;		// ゲーム開始時のカウントダウン用
	int number_img[3];
	int startnum;

	int high_score;     //ハイスコア
	int back_ground;    //背景画像
	int audience_img;	//観客画像

	int mileage;        //背景画像を動かすよう
	int mileage2;        //観客画像動かす用
	int enemy_image[3]; //敵画像
	int enemy_count[3]; //通り過ぎた敵カウント
	Player* player;     //プレイヤー
	Player* player2;     //プレイヤー2
	Player* player3;     //プレイヤー3
	Enemy** enemy;       //敵
	Policecar* Pcar;     //パトカー
	
	Item* item[10];

	int max, min;
	
	int count;          //６０回数える
	int timer;          //countが６０になったら１数える
	int ptimer;
	int ptimer2;
	int ptimer3;

	int time;//アクション起きた時の時間を渡す用
	bool flg;
	int alpha;
	int blackimg;//
	int p1win;//勝ったら＋１
	int p2win;
	int p3win;
	int starimg;

	bool winflg;
	int whowin;//どっちが勝ったか


public:
	int static Wineer;

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
	bool IsHitCheckP3(Player* p3,Policecar* car);

	// ドアの当たり判定
	bool IsHitDoorR(Player* p1,Player* p2);
	bool IsHitDoorL(Player* p1,Player* p2);

	// ドアの当たり判定（プレイヤー２）
	bool IsHitDoorR2(Player* p1, Player* p2);
	bool IsHitDoorL2(Player* p1, Player* p2);

	// ドアの当たり判定（プレイヤー３）
	bool IsHitDoorR2(Player* p1, Player* p2);
	bool IsHitDoorL2(Player* p1, Player* p2);


	//アイテムの当たり判定
	bool IsHitCheckItem(Player* p, Item* i);
	bool IsHitItem(Player* p2, Item* i);

	//勝敗処理
	void win();

};