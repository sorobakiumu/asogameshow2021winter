#include "EndScene.h"
#include "../ImgMnj.h"
#include "../objMnj.h"
#include "MenuScene.h"
#include "sceneMng.h"
#include "TitleScene.h"
#include "../PadMng.h"

UNBS EndScene::Update(UNBS own)
{
	sps_.second = sps_.first;
	if (LpPadMng.GetPad().Buttons[7])
	{
		return std::make_unique<MenuScene>(std::move(own));
	}

	if (CheckHitKey(KEY_INPUT_SPACE) || LpPadMng.GetPad().Buttons[0])
	{
		sps_.first = true;
	}
	else
	{
		sps_.first = false;
	}
	if (sps_.first && !sps_.second)
	{
		return std::make_unique<TitleScene>();
	}

	lpobjlMng.ObjRotation(UNIT_ID::PLAYER, 90, 0);
	lpobjlMng.Setobjpos(VGet(500.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::PLAYER, 0);
	lpobjlMng.Setobjpos(VGet(500.0f, cpy_ - 200, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::NON, 0);

	//•`‰æ‚É“Š‚°‚é
	lpobjlMng.ObjDraw(UNIT_ID::PLAYER, 0);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, cpy_, -1000.0f), VGet(0.0f, cpy_ + 100, 0.0f));

	if (lpSceneMng.GetFcon() / 60 % 2 == 0)
	{
		cpy_ -= 0.2f;
	}
	else
	{
		cpy_ += 0.2f;
	}

	lpImglMng.AddImg(std::string("img/end.png"), Vector2(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2 - 300));
	lpImglMng.AddImg(std::string("img/space.png"), Vector2(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2 + 400));
	return own;
}

EndScene::EndScene()
{
	lpImglMng.AddImg(std::string("img/end.png"), lpSceneMng.ScreenSize / 2);
	SetFogColor(50, 50, 50);
	cpy_ = 200;
	sps_ = { true,true };
}

EndScene::~EndScene()
{
}

void EndScene::Draw(void)
{
	lpobjlMng.DrawNaw();
	lpImglMng.Draw();
}

SCN_ID EndScene::GetSCNID_(void)
{
	return scnID_;
}
