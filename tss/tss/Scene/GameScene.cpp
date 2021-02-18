#include <time.h>
#include "../objmnj.h"
#include "../Player.h"
#include "sceneMng.h"
#include "../Obj.h"
#include "GameScene.h"
#include "../ImgMnj.h"
#include "MenuScene.h"
#include "../PadMng.h"
#include "../SoundMnj.h"
#include "EndScene.h"

GameScene::GameScene()
{
	SetWindowText("LineBattleoftheShip::ゲーム");
	_objList.emplace_back(new(Player),UNIT_ID::PLAYER);
	ppos = VGet(0.0f, 0.0f, 0.0f); 
	srand((unsigned)time(NULL));								//時間を使ってランダムに数字を入れ替える
	gcon_ = 0;
	scnID_ = SCN_GAME;
	lpSudlMng.CheckSEList(std::string("sound/bann.wav"));
	cpy_ = 200;
	lrSF_ = 0;

	if (rand() % 2 == 0)
	{
		SetFogColor(255, 150, 0);
	}
	else
	{
		SetFogColor(100, 100, 100);
	}
	pHp_ = 255;
	plwlF_ = false;
	plwlFCon_ = 60 * 60;
}

UNBS GameScene::Update(UNBS own)
{
	if (LpPadMng.GetPad().Buttons[7])
	{
		return std::make_unique<MenuScene>(std::move(own));
	}
	if (pHp_ <= 0)
	{
		return std::make_unique<EndScene>();
	}
	else
	{
		for (auto data : _objList)
		{
			if (data.second == UNIT_ID::CPU)
			{
				(*data.first).Updata(ppos);	//更新処理
				if ((*data.first).GetPos().z <= -4950)
				{
					pHp_ -= 2;
				}
			}
			(*data.first).Updata();	//更新処理
			if (data.second == UNIT_ID::PLAYER)
			{
				cam.CameraRun((*data.first).GetPos());
				ppos = (*data.first).GetPos();
				lrSF_ = (*data.first).GetSLR() ^ 1;
			}
		}

		if (ppos.z > 10000)
		{
			plwlF_ = true;
		}
		else if (ppos.z < -5000)
		{
			plwlF_ = true;
		}
		else if (ppos.x>10000)
		{
			plwlF_ = true;
		}
		else if (ppos.x < -10000)
		{
			plwlF_ = true;
		}
		else
		{
			plwlFCon_ = 60 * 60;
			plwlF_ = false;
		}


		if (lpSceneMng.GetFcon() / 60 % 2 == 0)
		{
			cpy_ -= 0.2f;
		}
		else
		{
			cpy_ += 0.2f;
		}
		if (gcon_ <= 60 * 6)
		{
			lpImglMng.AddImg(std::string("img/sous3.png"), lpSceneMng.ScreenSize / 2);
		}
		else
		{
			VECTOR tp = ppos;
			tp.y = 0;
			lpobjlMng.Setobjpos(VAdd(tp, VGet(0.0f, cpy_ - 220, 0.0f)), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::NON, 0);
			lpImglMng.AddImg(std::string("img/lr.png"), lpSceneMng.ScreenSize / 2, lrSF_);
		}

		if (plwlFCon_ == 0)
		{
			return std::make_unique<EndScene>();
		}
		//(ppos.z > 10000)(ppos.z < -5000) (ppos.x > 10000)(ppos.x < -10000);
		//DrawLine3D(VGet(-10000.0f, 10.0f, 10000.0f), VGet(10000.0f, 10.0f, 10000.0f), 0xff0000);
		//DrawLine3D(VGet(-10000.0f, 10000.0f, 10000.0f), VGet(10000.0f, 10000.0f, 10000.0f), 0xff0000);

		//DrawLine3D(VGet(-10000.0f, 10.0f, 0.0f), VGet(10000.0f, 10.0f, 0.0f), 0xff0000);
		//DrawLine3D(VGet(-10000.0f, 10000.0f, 0.0f), VGet(10000.0f, 10000.0f, 0.0f), 0xff0000);

		//DrawLine3D(VGet(10000.0f, 10.0f, -10000.0f), VGet(10000.0f, 10.0f, 10000.0f), 0xff0000);
		//DrawLine3D(VGet(0.0f, 10000.0f, -10000.0f), VGet(0.0f, 10000.0f, 10000.0f), 0xff0000);

		//DrawLine3D(VGet(10000.0f, 10000.0f, -10000.0f), VGet(10000.0f, 10000.0f, 10000.0f), 0xff0000);
		//DrawLine3D(VGet(0.0f, 10.0f, -10000.0f), VGet(0.0f, 10.0f, 10000.0f), 0xff0000);
		gcon_++;
	}
	return std::move(own);
}


GameScene::~GameScene()
{
	lpobjlMng.Destroy();
}

void GameScene::Draw(void)
{
	lpobjlMng.DrawNaw();
	lpImglMng.Draw(); 
	if (gcon_ <= 60 * 6)
	{
		DxLib::DrawFormatString(0, 0, 0x000000, "あと[ %d ]秒で始まるよ", (3 - gcon_ / 120));
	}
	else
	{
		DxLib::DrawBox(lpSceneMng.ScreenSize.x/2 -300, 0, lpSceneMng.ScreenSize.x/2 - 300+ 255, 30, 0xffffff, true);
		DxLib::DrawBox(lpSceneMng.ScreenSize.x/2 - 300, 0, lpSceneMng.ScreenSize.x/2 - 300+ 255, 30, 0x000000, false);

		int c = 0;
		if (pHp_ > 100)
		{
			c = GetColor(255 - pHp_, 150, pHp_);
		}
		else if (pHp_ > 40)
		{
			c = GetColor(255 - pHp_, 80, 0);
		}
		else
		{
			c = GetColor(255 - pHp_, 0, 0);
		}
		DxLib::DrawBox(lpSceneMng.ScreenSize.x/2 - 299, 1, lpSceneMng.ScreenSize.x/2 - 300 + 255 -(255-pHp_)-1, 29, c, true);
		//DxLib::DrawFormatString(1000, 20, 0x000000, "%d", pHp_);

		if (plwlF_ == true)
		{
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2-200+2, lpSceneMng.ScreenSize.y / 2-300,0x000000, "引き返してください。\n　あと%d秒", plwlFCon_/60);
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2-200, lpSceneMng.ScreenSize.y / 2-300,0xff0000, "引き返してください。\n　あと%d秒", plwlFCon_/60);

			plwlFCon_--;
		}
	}
}

SCN_ID GameScene::GetSCNID_(void)
{
	return scnID_;
}

