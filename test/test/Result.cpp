#include "Result.h"
#include <DxLib.h>
#include "Title.h"
void Result::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (CheckHitKey(KEY_INPUT_0)) {
		baseGame = std::make_shared<Title>();
		baseGame->Init();
	}
}

void Result::Draw()
{
	DrawFormatString(0, 0, 0xffffff, L"result");
}

void Result::Init()
{
}
