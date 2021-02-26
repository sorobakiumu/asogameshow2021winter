#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "BaseGame.h"

#define JankenMAX 3
#define JankenMove 3

/// <summary>
/// じゃんけんの手の種類！
/// 出してない！
/// ぐー
/// ちょき
/// ぱー
/// </summary>
enum JANKENACTION
{
	NO,
	GU,
	TYOKI,
	PA,
	MAX
};

/// <summary>
/// いまのゲームステータス
/// 待機中
/// じゃんけん中
/// リザルト中
/// しゅーりょー
/// </summary>
enum NOWMODE
{
	STAY,
	JANK,
	RESER,
	FIN
};

enum GameFlag
{
	no_Gf,
	DRAW_GF,
	WINYOU_GF,
	WINCPU_GF
};

enum class OUTPUTDAT
{
	GOLD = 1,
	Three1P,
	Seven1P,
	One1P,
	Five1P,
	Two1P,
	ElevenP,
	Three2P,
	Seven2P,
	One2P,
	Five2P,
	Two2P,
};

class JankenPon :
	public BaseGame
{
public:
	JankenPon();
	~JankenPon();

	/// <summary>
	/// げーむるーぷ
	/// </summary>
	/// <param name=""></param>
	void Run(std::shared_ptr<BaseGame>& baseGame) override;

	/// <summary>
	/// びょうが
	/// </summary>
	/// <param name=""></param>
	void Draw(void) override;
	/// <summary>
	/// 最初だけの初期化
	/// </summary>
	/// <param name=""></param>
	void Init(void) override;
private:

	/// <summary>
	/// どの手を出すか考え（数が多いのを探す）て選ぶ　10かいにいっかいランダム！運あり！
	/// </summary>
	/// <param name=""></param>
	void SetAct(void);

	/// <summary>
	/// だしまち
	/// </summary>
	/// <param name=""></param>
	void StayMove(void);

	/// <summary>
	/// 終了時の初期化
	/// </summary>
	/// <param name=""></param>
	void Finmove(void);

	/// <summary>
	/// ゲーム処理（じゃんけん部分）
	/// </summary>
	/// <param name=""></param>
	void GameMove(void);

	/// <summary>
	/// るーれっと
	/// </summary>
	/// <param name=""></param>
	void ResultMove(void);

	/// <summary>
	/// 勝者判定
	/// </summary>
	/// <param name=""></param>
	void WinCheck(void);

	NOWMODE nowmode_;		//いまのこのミニゲームでの状態
	JANKENACTION youact_;	//プレイヤーが選んだ手
	JANKENACTION myflg_;	//CPUくんが選んだ手
	int nextfindMove_;		//CPU君が予想()したプレイヤーの次の手
	int jankenData_[JankenMove][JankenMAX];//これまでのじゃんけんげーむ
	int otout_;				//一回前のプレイヤーの手
	int jcon_;				//じゃんけんかうんたー
	bool gconf_;			//げーむカウント用のフラグ
	int gcon_;				//げーむカウント
	GameFlag gameflag_;		//勝者判定結果の変数

	int resconNum_;			//リザルトの秒数決定後の秒数格納変数
	bool resconF_;			//リザルトで、ルーレット終わったか（しないかどうか）

	int res_;				//ルーレット結果（めだる報酬用）

	int initflag;
	int gcpsound;
	int tcon_;

	int pMoney_;	//1　pr 3 or 5
	bool SetFlg_;
	
	bool af_;
	bool aof_;
	bool sf_;
	bool sof_;
	bool df_;
	bool dof_;

	bool gameEndF_;
};

