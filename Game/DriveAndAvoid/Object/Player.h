#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"


//プレイヤーがどこに当たったか？
enum direction
{
	RGIHT,//右
	LEFT,//左
	UP,//上
	UNDER,//下

};

class Player
{
private:
	bool is_active;      //有効状態か
	int image;           //画像データ
	Vector2D location;   //位置座標
	Vector2D direction;   //sinnkoiu
	Vector2D box_size;   //当たり判定の大きさ
	float angle;         //角度
	float speed;         //速さ
	float hp;            //体力
	float fuel;          //燃料
	int barrier_count;   //バリアの枚数
	Barrier* barrier;    //バリア
	int playernum;//プレイヤーの番号
	int playerd;//どこに当たったかの格納
	Vector2D dire;//計算用

public:
	Player();
	~Player();

	void Initialize(int pnum,float x);        //初期化処理
	void Update();            //更新処理
	void Draw();              //描画処理
	void Finalize();          //終了時処理

public:
	void SetActive(bool flg);          //有効フラグ設定
	void DecreaseHp(float value);       //体力減少処理
	Vector2D GetLocation() const;   //位置情報取得
	Vector2D GetDirection() const;   //向き情報取得
	Vector2D GetBoxSize() const;    //当たり判定の大きさ取得
	float GetSpeed() const;         //速さ取得処理
	float GetFuel() const;          //燃料取得
	float GetHp() const;            //体力取得
	int GetBarriarCount() const;         //バリアの枚数取得
	bool IsBarrier() const;         //バリア有効かを取得

	//void direction(Vector2D xy);			//どこに当たったか調べる
	void RepulsionX(Vector2D xy,Vector2D d);//ぶつかったら反発起こす用左右
	void RepulsionY(Vector2D xy,Vector2D d);//ぶつかったら反発起こす用上下
	//相手のロケーションと向きをもらう

	//自分の車に侵入できなくする
	void Exclusion(Vector2D loce);

private:
	void Movement();      //移動処理
	void Acceleration();    //加速処理
};