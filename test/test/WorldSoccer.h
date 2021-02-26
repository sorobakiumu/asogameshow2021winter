#pragma once
#include <vector>
#include "Geometry.h"
#include "BaseGame.h"

class WorldSoccer :
	public BaseGame
{
public:
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
private:
	void PinInit();
	void IsHit(std::shared_ptr<Boll>& boll);
	void hollIsHit(std::shared_ptr<Boll>& boll);
	const float pinsize = 2.5f;
	const int startnum = 4;
	const int ynum = 4;
	const float xoffset = 200;
	const float xgameScreen = 400;
	std::vector<Vector2> pinPositions;
	std::vector<std::shared_ptr<Boll>> bolls;
	Vector2 holl;
	float downpt = 400;
	int flame = 0;
	float gravity = 0.5f;
	float bollR = 20;
	float hollR = bollR + 15;
	const int hollmin_x = 200 + hollR;
	const int hollmax_x = 600 - hollR;
	const int hollmin_y = 400;
	const int hollmax_y = 600 - hollR;
	bool gamestart = false;
	int score = 0;
	int life = 5;
	bool initflag;
	int tcon_;
};

