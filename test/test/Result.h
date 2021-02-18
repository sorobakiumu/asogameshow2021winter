#pragma once
#include "BaseGame.h"
class Result :
    public BaseGame
{
public:
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
};

