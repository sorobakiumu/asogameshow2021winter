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

namespace {
	std::shared_ptr<BaseGame> game_;
}

int main()
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

	while (ProcessMessage() != -1)
	{
		game_->Run(game_);
		ClsDrawScreen();
		game_->Draw();
		lpImglMng.Draw();
		lpImglMng.ResetD();
		DrawFormatString(0, 50, 0xffffff, L"coins = %d枚", Coins::GetInstance().coins);
		DrawFormatString(0, 70, 0xffffff, L"ticket = %d円分", Coins::GetInstance().kinken);
		ScreenFlip();
	}

}




