#include "GameSel.h"
#include <DxLib.h>
#include "WorldSoccer.h"
#include "CarRace.h"
#include "JankenPon.h"

void GameSel::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (CheckHitKey(KEY_INPUT_1)) {
		baseGame = std::make_shared<WorldSoccer>();
		baseGame->Init();
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		baseGame = std::make_shared<CarRace>();
		baseGame->Init();
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		baseGame = std::make_shared<JankenPon>();
		baseGame->Init();
	}
}

void GameSel::Draw()
{
	DrawFormatString(0, 0, 0xffffff, L"gameSel");
	//ÉQÅ[ÉÄÉGÉäÉAÇÃï`âÊ
	DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
}

void GameSel::Init()
{
}

GameSel::GameSel()
{
}

GameSel::~GameSel()
{
}
