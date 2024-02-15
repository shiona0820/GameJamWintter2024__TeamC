#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"

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

	int crackimg;//車のひび画像用
	int alpha;//ひびを透かす用
	int hpcheck;

	bool hit_flg;//攻撃があたったら
	bool death_flg;//負けフラグ

	bool survival_flg;	// 生存フラグ

	int blinkingcun;
	bool blinking_flg;

	// 攻撃時の画像
	int carRimg, carLimg, doorRimg, doorLimg;

	int Attackflg;		// 攻撃フラグ
	int Bflg, Xflg;		// 攻撃ボタンの判定用フラグ
	//ドアの角度
	float DoorRangle, DoorLangle, Door2Rangle, Door2Langle;
	int Acount;		// ドアの描画用
	Vector2D DoorRlocation;		//ドアの位置座標（右）
	Vector2D DoorR_size;		//ドアの当たり判定の大きさ（右）
	Vector2D DoorLlocation;		//ドアの位置座標（左）
	Vector2D DoorL_size;		//ドアの当たり判定の大きさ（左）


	int explosion_img[3];	// 爆発画像
	int exNum;				// 爆発アニメーション描画用
	int explosion_count;	// 爆発アニメーションカウント用

	int explosion_sound;   //爆発SE
	int blow_sound;        //打撃SE
	int taiatari_sound;    //車同士のぶつかる時のSE
	int slip_sound;        //物体にぶつかった時のSE

	bool sliponce;

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
	void Hitflg(bool flg);//攻撃が当たってない状態かをもらう
	Vector2D GetLocation() const;   //位置情報取得
	Vector2D GetDirection() const;   //向き情報取得
	Vector2D GetBoxSize() const;    //当たり判定の大きさ取得
	float GetSpeed() const;         //速さ取得処理
	float GetFuel() const;          //燃料取得
	float GetHp() const;            //体力取得
	int GetBarriarCount() const;         //バリアの枚数取得
	bool IsBarrier() const;         //バリア有効かを取得
	bool GetHitflg() const;//HPを減らすのを一回だけにする用

	bool GetSurvival_flg() const;	// 爆発した後用フラグ（爆発後falseになる）

	bool GetDeathFlg() const;//敗北取得

	// ボタンフラグを返す
	int GetBflg() const;
	int GetXflg() const;

	int GetAttackflg() const;//アタックフラグを返す

	//void direction(Vector2D xy);			//どこに当たったか調べる
	void RepulsionX(Vector2D xy,Vector2D d);//ぶつかったら反発起こす用左右
	void RepulsionY(Vector2D xy,Vector2D d);//ぶつかったら反発起こす用上下
	//相手のロケーションと向きをもらう

	//自分の車に侵入できなくする
	void Exclusion(Vector2D loce);

	// 爆発アニメーション
	void Explosion();

	Vector2D GetDoorRLocation() const;   //ドアの位置情報取得（右）
	Vector2D GetDoorRSize() const;		 //ドアの当たり判定の大きさ取得（右）

	Vector2D GetDoorLLocation() const;   //ドアの位置情報取得（左）
	Vector2D GetDoorLSize() const;		 //ドアの当たり判定の大きさ取得（左）

private:
	void Movement();      //移動処理
	void Acceleration();    //加速処理
};