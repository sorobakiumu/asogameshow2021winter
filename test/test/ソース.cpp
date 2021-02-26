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
#include "mnj/masterMnj.h"
#include "mnj/ImgMnj.h"
#include "Result.h"

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
	SetDrawScreen(DX_SCREEN_BACK);
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
	//SetBackgroundColor(255, 255, 255);

	SetDXArchiveKeyString(L"36agemeronpan");
	int transSE = LoadSoundMem(L"Resource\\music/trans.mp3");
	//ChangeVolumeSoundMem(100, transSE);
	LpMastMng;

	bool resbotom = false;
	double deltime = GetNowCount();
	bool onforMouseLefOld =false , onforMouseLef = false;
	bool reseF = false;
	bool finF = false;
	int gFcon = 0; 
	int px = 0, py = 0;
	while (ProcessMessage() != -1 && !finF)
	{
		ScreenFlip();
		ClsDrawScreen();

		deltime += 16.66;
		if (deltime > GetNowCount())
			WaitTimer(static_cast<int>(deltime) - GetNowCount());

		if (trans) {
			transflame++;
			if (transflame < maxtrans / 2) {
				LpMastMng.Run();
				screen_->Draw();
				LpMastMng.Draw();
				DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
				DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, transflame*4);
				DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (transflame >= maxtrans / 2) {
				LpMastMng.Run();
				game_->Draw();
				LpMastMng.Draw();
				DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
				DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-(transflame-maxtrans/2)*4);
				DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (transflame > maxtrans) {
				trans = false;
			}
		}
		else {
			auto tmpGame = game_;
			LpMastMng.Run();
			game_->Run(game_);


			int tx, ty;

			DxLib::GetMousePoint(&tx, &ty);
			if (tx < 800)
				if (tx > 0)
					if (ty > 0)
						if (ty < 600)
						{
							px = tx;
							py = ty;
						} 
			{
			
				onforMouseLefOld = onforMouseLef;
				int Mouse = GetMouseInput();
				if (Mouse & MOUSE_INPUT_LEFT)
				{
					onforMouseLef = true;
				}
				else
				{
					onforMouseLef = false;
				}
				if (gFcon != 0)
				{
					if (px >= 800 - 64 && px <= 800 && py >= 0 && py <= 64)
					{


						if (onforMouseLefOld && !onforMouseLef)
						{
							resbotom = true;
						}
						if (resbotom)
						{
							if (!reseF)
							{
								resbotom = false;
								reseF = true;
								auto baseGame = std::make_shared<Result>();
								baseGame->Init();
								game_ = baseGame;
								StopSoundFile();
								StopSound();
							}
							else
							{
								finF = true;
							}
						}
					}
				}
			}

			if (game_ != tmpGame) {
				tmpGame->Draw();
				PlaySoundMem(transSE,DX_PLAYTYPE_BACK);
			}
			else {
				game_->Draw();
			}
			if (gFcon != 0)
			{
				if (!reseF)
					lpImglMng.AddImg(L"Resource\\image/koukan.png", Vector2(800 - 32, 32));
				else
					lpImglMng.AddImg(L"Resource\\image/bat.png", Vector2(800 - 32, 32));

				lpImglMng.AddImg(L"Resource\\image/car.png", Vector2(px + 16, py + 16));
			}
			LpMastMng.Draw();
			DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
			DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
		}
		if (oldgame_ != game_) {
			trans = true;
			transflame = 0;
			screen_ = oldgame_;
			if (gFcon == 0)
				gFcon++;
		}
		oldgame_ = game_;
		if (gFcon != 0)
			gFcon++;
	}
	DxLib_End();
	return 0;
}




