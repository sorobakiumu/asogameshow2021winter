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
	//ƒQ[ƒ€ƒGƒŠƒA‚Ì•`‰æ
	DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
}

void Title::Init()
{
}
