#pragma once
#include "BaseGame.h"

class Title :
    public BaseGame
{
	int tcon_;
public:
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
};

