#pragma once
#include<memory>
class BaseGame
{
public:
	virtual void Run(std::shared_ptr<BaseGame>& baseGame) = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
};

