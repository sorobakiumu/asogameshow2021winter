#pragma once
#include <vector>
#include <map>
#include <string>
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

	/// <summary>
	/// 位置情報をセット idで、判別
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="vec"></param>
	/// <param name="id">名前</param>
	/// <param name="num"></param>
	void Setobjpos(VECTOR pos, VECTOR vec, std::string id, int num);
	
	/// <summary>
	/// 位置情報を返す。
	/// </summary>
	/// <param name="id">ファイル</param>
	/// <param name="num"></param>
	/// <returns></returns>
	VECTOR Getobjpos(std::string id);

	/// <summary>
	/// //これを呼ぶと、描画要求を、sceneマネージャにします
	/// </summary>
	/// <param name="id"></param>
	/// <param name="num"></param>
	void ObjDraw(std::string id, int num);								

	/// <summary>
	/// オブジェクトを回転させる！//回転情報（見た目）をセット
	/// </summary>
	/// <param name="id">ファイル名</param>
	/// <param name="moveangle">あんぐる</param>
	void ObjRotation(std::string id,float moveangle);			

	/// <summary>
	/// オブジェクトを追加！例のごとくファイル名はタグになるぞ！
	/// </summary>
	/// <param name="que"></param>
	/// <param name="num"></param>
	void AddObj(std::string que, int num = 0);

	/// <summary>
	/// てんきゅう
	/// </summary>
	/// <param name=""></param>
	void update(void);
private:
	static Objmnj* sInstance;


	std::vector<int> _drawList;						//描画するものを溜めておくキュー
	std::vector<int> _drawListnex;					//描画するものを溜めておくキュー（すける）

	std::map<std::string, int> objHMap_;
	//int		issobj;					//壁格納用
	//int		playerobj;				//ﾌﾟﾚｲﾔモデル格納用
	//int		phitobj;				//ﾌﾟﾚｲﾔ当たり判定モデル格納用
	int		skyobj;					//空
	//int		mapmodel;				//海モデル格納用
	//VECTOR	pvec;					//プレイヤ移動ベクトル
	//VECTOR	ppos;					//プレイヤー座標

	UNIT_ID	player;					//ﾌﾟﾚｲﾔモデル格納用

	Objmnj();
	~Objmnj();
};

