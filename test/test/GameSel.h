#pragma once
#include "BaseGame.h"
#include"Geometry.h"

enum thisGameis
{
	NOSELGAME,
	CarraceGame,
	RSPGame,
	SoccerGame,
};

class GameSel :
    public BaseGame
{
public:
	void Run(std::shared_ptr<BaseGame>& baseGame) override;
	void Draw() override;
	void Init() override;
	GameSel();
	~GameSel();
private:
	void CheckMousePosHit(void);
	bool initflag;

	bool onforMouseLef_;
	bool onforMouseLefOld_;

	Vector2 mousePos_;

	thisGameis nowMowsGame_;
};

