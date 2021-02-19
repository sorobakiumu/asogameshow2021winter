#include "Title.h"
#include <DxLib.h>
#include "GameSel.h"

void Title::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		baseGame = std::make_shared<GameSel>();
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
