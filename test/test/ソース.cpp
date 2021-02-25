#include <DxLib.h>
#include <memory>
#include "Geometry.h"
#include <cmath>
#include <random>
#include <vector>
#include "CarRace.h"
#include "JankenPon.h"
#include "WorldSoccer.h"
#include "Title.h"
#include <EffekseerForDXLib.h>
#include "mnj/ImgMnj.h"
#include "Coins.h"
#include "mnj/SoundMnj.h"

namespace {
	std::shared_ptr<BaseGame> game_;
	std::shared_ptr<BaseGame> oldgame_;

	std::shared_ptr<BaseGame> screen_;
	bool trans=false;
	int transflame = 0;
	const int maxtrans = 128;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR, int) 
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// DXライブラリを初期化する。
	if (DxLib_Init() == -1)
		return -1;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(800, 600);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	game_ = std::make_shared<Title>();
	game_->Init();
	oldgame_ = game_;

	int transSE = LoadSoundMem(L"Resource/music/trans.mp3");
	//ChangeVolumeSoundMem(100, transSE);
	while (ProcessMessage() != -1)
	{
		if (trans) {
			transflame++;
			if (transflame < maxtrans / 2) {
				ClsDrawScreen();
				screen_->Draw();
				lpImglMng.Draw();
				lpImglMng.ResetD();
				DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
				DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, transflame*4);
				DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				ScreenFlip();
			}
			else if (transflame >= maxtrans / 2) {
				ClsDrawScreen();
				game_->Draw();
				lpImglMng.Draw();
				lpImglMng.ResetD();
				DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
				DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-(transflame-maxtrans/2)*4);
				DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				ScreenFlip();
			}
			if (transflame > maxtrans) {
				trans = false;
			}
		}
		else {
			auto tmpGame = game_;
			game_->Run(game_);
			ClsDrawScreen();
			if (game_ != tmpGame) {
				tmpGame->Draw();
				PlaySoundMem(transSE,DX_PLAYTYPE_BACK);
			}
			else {
				game_->Draw();
			}
			lpImglMng.Draw();
			lpImglMng.ResetD();
			DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
			DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
			ScreenFlip();
		}
		if (oldgame_ != game_) {
			trans = true;
			transflame = 0;
			screen_ = oldgame_;
		}
		oldgame_ = game_;
	}
}




