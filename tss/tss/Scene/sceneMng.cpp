#include<DxLib.h>
#include "sceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "../PadMng.h"
#include "../ImgMnj.h"
#include "../objmnj.h"
#include "../SoundMnj.h"

SceneMng* SceneMng::sInstance = nullptr;


SceneMng::SceneMng() :ScreenSize{1920,1080}
{
	SetWindowText("LineBattleoftheShip");
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	SetDrawScreen(DX_SCREEN_BACK);
	SetCreate3DSoundFlag(true);
	SetFontSize(60);
	SetBackgroundColor(100, 255, 255);
	SetUseZBufferFlag(TRUE);
	SetCameraNearFar(100.0f, 40000.0f);
	SetMouseDispFlag(false);	//マウスを非表示に
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));


	/*  */

	//ChangeLightTypeDir(VGet(0.0f, 1.0f, 0.0f));
	lightHandle_ = CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f));
	//lightHandle_ = CreatePointLightHandle(VGet(320.0f, 1000.0f, 600.0f), 10000.0f,0.0f,0.002f,0.0f);
	lightHandle2_ = CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));
	//lightHandle3_ = CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f));
	//lightHandle3_ = CreatePointLightHandle(VGet(0.0f, 2000.0f, 15000.0f), 2000.0f, 0.0f, 0.002f, 0.0f);
	//lightHandle3_ = CreateSpotLightHandle(VGet(0.0f, 2000.0f, 15000.0f),VGet(0.0f, -1.0f, 0.0f),DX_PI_F / 10.0f,DX_PI_F / 14.0f,2000.0f,0.0f,0.002f,0.0f);
	lightHandle3_ = CreatePointLightHandle(VGet(0.0f, 100000.0f, 0.0f), 200000.0f, 0.0f, 0.00002f, 0.0f);

	systemEnd = false;
	fcon_ = 0;
	campos_ = VGet(0.0f, 0.0f, 0.0f);
	lightC_ = 0;
	LpPadMng;
	lpImglMng;
	lpobjlMng;
	lpSudlMng;

	SetFogEnable(TRUE); 
	SetFogStartEnd(1500.0f, 40000.0f);
}

SceneMng::~SceneMng()
{
}

//
//void SceneMng::AddImgDrawQue(int que,Vector2 pos)
//{
//	//描画用のQueを追加
//	std::pair<int, Vector2> tp = {que,pos};
//	drawListImg_.emplace_back(tp);
//}
//
//void SceneMng::AddDrawQue(int que)
//{
//	//描画用のQueを追加
//	_drawList.emplace_back(que);
//}
//
//void SceneMng::AddDrawQuenex(int que)
//{
//	//描画用のQueを追加
//	_drawListnex.emplace_back(que);
//}

void SceneMng::GameEnd(void)
{
	systemEnd = true;
}

void SceneMng::SetLight(int num)
{
	int tm = 255 - num;
	if (tm > 255)
	{
		tm = 255;
	}
	if (tm < 0)
	{
		tm = 0;
	}
	lightC_ = tm;
}

void SceneMng::Draw(void)
{
	DxLib::ClsDrawScreen();

	DxLib::DrawRotaGraph(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0f, 0.0f, lpImglMng.GetGH(std::string("img/sous3.png")), true);


	activeScene_->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, lightC_);

	DxLib::DrawBox(0, 0, ScreenSize.x, ScreenSize.y, 0x000000, true);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
	DxLib::ScreenFlip();
	//DrawSphere3D(VGet(0.0f, 0.0f, 0.0f), 100.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);	
	//// カプセルの描画
	//DrawCapsule3D(VGet(0.0f, 0.0f, 1050.0f), VGet(0.0f, 0.0f + 200, 1050.0f), 100.0f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);

}

void SceneMng::Run(void)
{
	activeScene_ = std::make_unique<TitleScene>();

	fcon_ = NULL;
	lpSudlMng.AddBGM(std::string("sound/bgm_49.ogg"));
	while (ProcessMessage() == 0 && systemEnd == false)
	{
		//for (int i = 0; i < 2; i++)
		{
			//SetLightDirectionHandle(lightHandle_, campos_);
			SetLightPositionHandle(lightHandle_, campos_);
			lpobjlMng.ReSetD();
			lpImglMng.ResetD();
			bulletList_.clear();
			lpSudlMng.ResetD();

			LpPadMng.Run();
			activeScene_ = (*activeScene_).Update(std::move(activeScene_));
		}

		lpSudlMng.Run();
		Draw();
		fcon_++;
	}
}

bool SceneMng::SysInit(void)
{
	return true;
}

