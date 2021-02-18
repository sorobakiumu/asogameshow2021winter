#pragma once
#include <vector>
#include "obj.h"


//#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
//#define CHARA_ENUM_DEFAULT_SIZE		3000.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
//#define CHARA_HIT_WIDTH				3000.0f		// 当たり判定カプセルの半径
//#define CHARA_HIT_HEIGHT			1000.0f		// 当たり判定カプセルの高さ
//#define CHARA_HIT_PUSH_POWER		40.0f		// キャラクター同士で当たったときの押し出される力

#define lpobjlMng Objmnj::GetInstance()


//モデル管理マネージャ
class Objmnj
{
public:
	static Objmnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Objmnj();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	void DrawNaw(void);

	void ReSetD(void);	//毎フレーム最初に呼ぶ

	void Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num);	//位置情報をセット idで、判別

	int Getobjpos(VECTOR pos, UNIT_ID id, int num);					//位置情報を返す。

	UNIT_ID CheckHit(UNIT_ID id, int num);							//あったってるか確認用**現在使用不可**								

	void ObjDraw(UNIT_ID id, int num);								//これを呼ぶと、描画要求を、sceneマネージャにします

	void ObjRotation(UNIT_ID id,float moveangle, int num);			//回転情報（見た目）をセット


private:
	static Objmnj* sInstance;


	std::vector<int> _drawList;						//描画するものを溜めておくキュー
	std::vector<int> _drawListnex;					//描画するものを溜めておくキュー（すける）

	int		issobj;					//壁格納用
	int		playerobj;				//ﾌﾟﾚｲﾔモデル格納用
	int		phitobj;				//ﾌﾟﾚｲﾔ当たり判定モデル格納用
	int		skyobj;					//空
	int		mapmodel;				//海モデル格納用
	VECTOR	pvec;					//プレイヤ移動ベクトル
	VECTOR	ppos;					//プレイヤー座標

	UNIT_ID	player;					//ﾌﾟﾚｲﾔモデル格納用

	Objmnj();
	~Objmnj();
};

