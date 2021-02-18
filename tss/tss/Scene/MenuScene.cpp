#include "MenuScene.h"
#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "../ImgMnj.h"
#include "../objMnj.h"

MenuScene::MenuScene(UNBS oscn):lightMax_(255),lightMin_(0)
{
	holdScn_.swap(oscn);

	yn = false;
	rlF_ = { false,false };
	llF_ = { false,false };
	pbF_ = { false,false };
	backF_ = false;
	backCon_ = 0;
	mode_ = MenuMode::MnM_DEFF;
	lightcon_ = lightMax_;
}

MenuScene::~MenuScene()
{
	if (holdScn_ != nullptr)
	{
		holdScn_->~BaseScene();
		holdScn_.release();
	}
}

UNBS MenuScene::Update(UNBS nsn)
{

	auto pad1 = GetJoypadInputState(DX_INPUT_PAD1);
	rlF_.second = rlF_.first;
	llF_.second = llF_.first;
	pbF_.second = pbF_.first;

	if (CheckHitKey(KEY_INPUT_SPACE) || (pad1 & PAD_INPUT_1) != 0)
	{
		pbF_.first = true;
	}
	else
	{
		pbF_.first = false;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) || (pad1 & PAD_INPUT_RIGHT) != 0)
	{
		rlF_.first = true;
	}
	else
	{
		rlF_.first = false;
	}

	if (CheckHitKey(KEY_INPUT_LEFT) || (pad1 & PAD_INPUT_LEFT) != 0)
	{
		llF_.first = true;
	}
	else
	{
		llF_.first = false;
	}

	if (mode_ == MenuMode::MnM_DEFF)
	{
		if (pbF_.first && !pbF_.second)
		{
;			if (yn == 1)
			{
				mode_ = MenuMode::MnM_BACK;
			}
			else if(yn == 0)
			{
				mode_ = MenuMode::MnM_LIGHT;
			}
			else if (yn == 2)
			{
				mode_ = MenuMode::MnM_TITLE;
			}
			else if (yn == 3)
			{
				mode_ = MenuMode::MnM_END;
			}
			yn = 0;
		}
	}
	else
	if (mode_ == MenuMode::MnM_BACK)
	{
		if (backF_)
		{
			if (backCon_ / 120 == 3)
			{
				lpSceneMng.SetLight(lightcon_);
				return std::move(holdScn_);
			}
			backCon_++;
		}
		if (pbF_.first && !pbF_.second)
		{
			if (yn == 1)
			{
				if (holdScn_->GetSCNID_() != SCN_GAME)
				{
					lpSceneMng.SetLight(lightcon_);
					return std::move(holdScn_);
				}
				backF_ = true;
				backCon_ = 1;
			}
			else
			{
				mode_ = MenuMode::MnM_DEFF;
			}
		}
	}
	else if(mode_ == MenuMode::MnM_LIGHT)
	{
		lpSceneMng.SetLight(lightcon_);
		if (pbF_.first && !pbF_.second)
		{
			yn = 0;
			mode_ = MenuMode::MnM_DEFF;
		}
	}
	else if (mode_ == MenuMode::MnM_TITLE)
	{
		if (pbF_.first && !pbF_.second)
		{
			if (yn == 1)
			{
				lpSceneMng.SetLight(lightcon_);
				if (holdScn_->GetSCNID_() == SCN_TITLE)
				{
					return std::move(holdScn_);
				}
				return std::make_unique<TitleScene>();
			}
			else
			{
				yn = 0;
				mode_ = MenuMode::MnM_DEFF;
			}
		}
	}
	else if (mode_ == MenuMode::MnM_END)
	{

		if (pbF_.first && !pbF_.second)
		{
			if (yn == 1)
			{
				lpSceneMng.GameEnd();
				return nsn;
			}
			else
			{
				yn = 0;
				mode_ = MenuMode::MnM_DEFF;
			}
		}
	}

	if (mode_ != MenuMode::MnM_LIGHT&& mode_ != MenuMode::MnM_DEFF)
	{
		if (rlF_.first && !rlF_.second)
		{
			yn = 1;
		}

		if (llF_.first && !llF_.second)
		{
			yn = 0;
		}
	}
	else if(mode_ == MenuMode::MnM_LIGHT)
	{
		if (rlF_.first)
		{
			lightcon_++;
			if (lightMax_ < lightcon_)
			{
				lightcon_ = lightMax_;
			}
		}
		if (llF_.first)
		{
			lightcon_--;
			if (lightMin_ > lightcon_)
			{
				lightcon_ = lightMin_;
			}
		}
	}
	else
	{
		if (rlF_.first && !rlF_.second)
		{
			yn++;
			if (yn >= static_cast<int>(MenuMode::MnM_END))
			{
				yn = static_cast<int>(MenuMode::MnM_DEFF);
			}
		}

		if (llF_.first && !llF_.second)
		{
			yn--;
			if (yn < static_cast<int>(MenuMode::MnM_DEFF))
			{
				yn = static_cast<int>(MenuMode::MnM_END) - 1;
			}
		}
	}

	return nsn;
}

void MenuScene::Draw(void)
{
	lpobjlMng.DrawNaw();
	if (mode_ != MenuMode::MnM_LIGHT)
	{
		if (backF_)
		{
			lpImglMng.AddImg(std::string("img/sous3.png"), lpSceneMng.ScreenSize / 2);
		}
		else
		{
			lpImglMng.AddImg(std::string("img/sous.png"), lpSceneMng.ScreenSize / 2);
		}
	}
	else
	{
		lpImglMng.AddImg(std::string("img/sous2.png"), lpSceneMng.ScreenSize / 2);
	}

	lpImglMng.Draw();

	if (mode_ != MenuMode::MnM_LIGHT)
	{
		lpSceneMng.SetLight(255);
		if (!backF_)
		{
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DxLib::DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x000000, true);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 180);
		}
	}
	if (mode_ == MenuMode::MnM_BACK)
	{
		if (backF_)
		{
			
			DxLib::DrawFormatString(0, 0, 0x000000, "あと[ %d ]秒で始まるよ", (3 - backCon_ / 120));
		}
		else
		{
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 150, lpSceneMng.ScreenSize.y / 2 - 100, 0xffffff, "メニューから");
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2-100, lpSceneMng.ScreenSize.y / 2 + 10, 0xffffff, "もどる?");
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "いいえ");
			DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "もどる");
			Vector2 pos;
			if (yn == 0)
			{
				pos = { lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300 };
			}
			else
			{
				pos = { lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300 };
			}
			DxLib::DrawBox(pos.x, pos.y, pos.x + 180, pos.y + 70, 0xffff00, false);

		}
	}
	else if (mode_ == MenuMode::MnM_DEFF)
	{
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 150, lpSceneMng.ScreenSize.y / 2 - 100, 0xffffff, "メニュー");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 100, lpSceneMng.ScreenSize.y / 2 + 10, 0xffffff, "どっち");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 350, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "明るさ");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 120, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "もどる");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 + 90, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "タイトル");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 + 350, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "おしまい");

		Vector2 pos;
		if (yn == 0)
		{
			pos = { lpSceneMng.ScreenSize.x / 2 - 350, lpSceneMng.ScreenSize.y / 2 + 300 };
			DxLib::DrawBox(pos.x, pos.y, pos.x + 180, pos.y + 70, 0xffff00, false);
		}
		else if (yn == 1)
		{
			pos = { lpSceneMng.ScreenSize.x / 2 - 120, lpSceneMng.ScreenSize.y / 2 + 300 };

			DxLib::DrawBox(pos.x, pos.y, pos.x + 180, pos.y + 70, 0xffff00, false);
		}
		else if (yn == 2)
		{
			pos = { lpSceneMng.ScreenSize.x / 2 + 90, lpSceneMng.ScreenSize.y / 2 + 300 };

			DxLib::DrawBox(pos.x, pos.y, pos.x + 240, pos.y + 70, 0xffff00, false);
		}
		else
		{
			pos = { lpSceneMng.ScreenSize.x / 2 + 350, lpSceneMng.ScreenSize.y / 2 + 300 };

			DxLib::DrawBox(pos.x, pos.y, pos.x + 240, pos.y + 70, 0xffff00, false);
		}
	}
	else if(mode_ == MenuMode::MnM_LIGHT)
	{
		DxLib::DrawBox(lpSceneMng.ScreenSize.x / 2 - lightMax_ / 2-20, lpSceneMng.ScreenSize.y / 2 - 20, lpSceneMng.ScreenSize.x / 2 + lightMax_ / 2+20, lpSceneMng.ScreenSize.y / 2 + 20, 0x000000, true);

		DxLib::DrawBox(lpSceneMng.ScreenSize.x / 2 - lightMax_ / 2, lpSceneMng.ScreenSize.y / 2 - 10, lpSceneMng.ScreenSize.x / 2 + lightMax_ / 2, lpSceneMng.ScreenSize.y / 2 + 10, 0xffffff, true);
		DxLib::DrawBox(lpSceneMng.ScreenSize.x / 2 - lightMax_ / 2+2, lpSceneMng.ScreenSize.y / 2 - 8, (lpSceneMng.ScreenSize.x / 2 - lightMax_ / 2-2)+lightcon_, lpSceneMng.ScreenSize.y / 2 + 8, 0x00ffff, true);
	}
	else if (mode_ == MenuMode::MnM_TITLE)
	{
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 - 100, 0xffffff, "メニューから");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 -250, lpSceneMng.ScreenSize.y / 2 + 10, 0xffffff, "タイトルに行く?");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "いいえ");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "いく");
		Vector2 pos;
		if (yn == 0)
		{
			pos = { lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300 };
			DxLib::DrawBox(pos.x, pos.y, pos.x + 180, pos.y + 70, 0xffff00, false);
		}	
		else
		{
			pos = { lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300 };
			DxLib::DrawBox(pos.x, pos.y, pos.x + 120, pos.y + 70, 0xffff00, false);
		}
	}
	else if (mode_ == MenuMode::MnM_END)
	{
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 - 100, 0xffffff, "このゲームを");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2-170, lpSceneMng.ScreenSize.y / 2 + 10, 0xffffff, "終了する?");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "いいえ");
		DxLib::DrawFormatString(lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300, 0xffffff, "終了");
		Vector2 pos;
		if (yn == 0)
		{
			pos = { lpSceneMng.ScreenSize.x / 2 - 200, lpSceneMng.ScreenSize.y / 2 + 300 };
			DxLib::DrawBox(pos.x, pos.y, pos.x + 180, pos.y + 70, 0xffff00, false);
		}
		else
		{
			pos = { lpSceneMng.ScreenSize.x / 2 + 200, lpSceneMng.ScreenSize.y / 2 + 300};
			DxLib::DrawBox(pos.x, pos.y, pos.x + 120, pos.y + 70, 0xffff00, false);
		}
	}
}

void MenuScene::Init(void)
{
}
