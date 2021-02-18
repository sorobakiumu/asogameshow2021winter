#pragma once
#include "Dxlib.h"
#include<memory>

enum class UNIT_ID			//それぞれの立場
{
	PLAYER,	//プレイヤーキャラ
	CPU,	//プレイヤー操作じゃないキャラ
	BULLET,	//弾
	NON,	//未割当
	MAX,	
};

// 移動速度
#define MOVESPEED					10.0f

// 操作軸のﾌﾟﾚｲﾔ本体とのの距離
#define MOVE_DISTANCE		1.0f

// 角度変化速度
#define PLAYER_ANGLE_SPEED			0.2f	

class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual UNIT_ID GetUnitID(void)	//ユニットIDを返す
	{
		return unitID_;
	}
	virtual VECTOR GetPos(void)	//位置情報を返す
	{
		return pos_;
	}

	virtual void Updata(void) = 0;	//OBJ系の更新用

	virtual void Updata(VECTOR pos)	//OBJ系の更新用2ほかのOBJ系の座標などがいる場合
	{
		return;
	}

	void SetUnitID(UNIT_ID unitID) { unitID_ = unitID; }
	virtual	int GetSLR(void)
	{
		return 0;
	}
protected:
	VECTOR pos_;	//座標格納
	UNIT_ID unitID_;	//ユニットID格納
};

