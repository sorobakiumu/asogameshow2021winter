#pragma once
class BaseGame
{
public:
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
};

