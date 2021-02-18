#include "Title.h"
#include "WorldSoccer.h"
#include "CarRace.h"
#include "JankenPon.h"
#include <DxLib.h>

void Title::Run(std::shared_ptr<BaseGame>& baseGame)
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

void Title::Draw()
{
	DrawFormatString(0, 0, 0xffffff, L"title");
}

void Title::Init()
{
}
