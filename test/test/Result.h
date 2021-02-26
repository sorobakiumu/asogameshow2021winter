#pragma once
#include "BaseGame.h"
#include"Geometry.h"
#include <vector>
#include <tuple>
#include <string>

class Result :
    public BaseGame
{
public:
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
private:
	std::vector<Vector2> button;
	int valueTable[4];
	int okasi[4];
	int flame;
	int value(int& okasivalue,int& val);
	std::vector<std::wstring> okasiList_;
};

