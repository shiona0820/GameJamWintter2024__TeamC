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
	Vector2D box_size;   //当たり判定の大きさ
	float angle;         //角度
	float speed;         //速さ
	float hp;            //体力
	float fuel;          //燃料
	int barrier_count;   //バリアの枚数
	Barrier* barrier;    //バリア
	int playernum;//プレイヤーの番号
	int playerd;//どこに当たったかの格納
	
	//反発用
	int time2;//経過時間得る用
	double t;//経過時間を計算して中に取り込むよう
	int y;//計算結果代入用	

	float v0;//反発係数計算用

public:
	Player();
	~Player();

	void Initialize(int pnum);        //初期化処理
	void Update();            //更新処理
	void Draw();              //描画処理
	void Finalize();          //終了時処理

public:
	void SetActive(bool flg);          //有効フラグ設定
	void DecreaseHp(float value);       //体力減少処理
	Vector2D GetLocation() const;   //位置情報取得
	Vector2D GetBoxSize() const;    //当たり判定の大きさ取得
	float GetSpeed() const;         //速さ取得処理
	float GetFuel() const;          //燃料取得
	float GetHp() const;            //体力取得
	int GetBarriarCount() const;         //バリアの枚数取得
	bool IsBarrier() const;         //バリア有効かを取得

	void direction(Vector2D xy);			//どこに当たったか調べる
	void Repulsion(int time);//ぶつかったら反発起こす用

private:
	void Movement();      //移動処理
	void Acceleration();    //加速処理
};