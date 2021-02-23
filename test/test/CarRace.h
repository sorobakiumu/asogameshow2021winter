#pragma once
#include <memory>
#include "Geometry.h"
#include <vector>
#include "BaseGame.h"

class CarRace :
	public BaseGame
{
public:
	CarRace();
	~CarRace();
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
private:
	void IsHit(std::shared_ptr<Boll>& boll, bool& balF);
	void HillIsHit(std::shared_ptr<Boll>& boll);

	void hollIsHit(std::shared_ptr<Boll>& boll, bool& balF);

	void wallIsHit(std::shared_ptr<Boll>& boll);

	void GoalIsHit(std::shared_ptr<Boll>& boll);

	void gPosChange(std::shared_ptr<Boll>& boll, std::pair<Vector2, Vector2> hillPos);
	std::vector<std::pair<Vector2, Vector2>> HillPositions;
	std::vector<Vector2> hollPosition;
	std::vector< std::pair<Vector2, Vector2>> wallPositions;
	std::vector<std::shared_ptr<Boll>> bolls;
	const float xoffset = 200;
	const float xgameScreen = 400;
	bool zff = false;			//球つきフラグ
	Vector2 neuVec = { 0,0 };	//フレーム毎の移動量
	int neuCon = 0;				//玉つき用のカウント
	float powP = 40;			//たまつきのパワー変数

	/// <summary>
	/// 球をつくための関数
	/// </summary>
	/// <param name="pow">パワー値</param>
	void bam(int pow);

	float gravity = 0.5f;
	float bollR = 20;

	float hollR = bollR + 5;
	bool oldkey = false;
	bool key = false;
	const float downpt = 600 - bollR * 3;

	bool balF = false;
};