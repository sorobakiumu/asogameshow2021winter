#pragma once
#include <vector>
#include "Geometry.h"

class WorldSoccer
{
public:
	void Ran();
	void Draw();
	void Init();
private:
	void IsHit(std::shared_ptr<Boll>& boll);
	const float pinsize = 2.5f;
	const int startnum = 7;
	const int ynum = 5;
	const float xoffset = 200;
	const float xgameScreen = 400;
	std::vector<Vector2> pinPositions;

	float gravity = 0.5f;
	float bollR = 20;
};

