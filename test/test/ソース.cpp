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
#include "resource.h"

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
	SetDXArchiveKeyString(L"36agemeronpan");
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib::SetMainWindowText(L"�ʉَq�������߂��");
	DxLib::SetWindowIconID(IDI_ICON1);

	// DX���C�u����������������B
	if (DxLib_Init() == -1)
		return -1;

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(800, 600);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	game_ = std::make_shared<Title>();
	game_->Init();
	oldgame_ = game_;
	//SetBackgroundColor(255, 255, 255);

	int transSE = LoadSoundMem(L"Resource\\music/trans.mp3");

	//ChangeVolumeSoundMem(100, transSE);
	ChangeVolumeSoundMem(255*70/100, transSE);
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
				lpImglMng.AddImg(L"Resource\\image/stbs.png", Vector2(800 / 2, 600 / 2));
				lpImglMng.AddImg(L"Resource\\image/coins.png", Vector2(25, 50));
				lpImglMng.AddImg(L"Resource\\image/goldc.png", Vector2(25, 100));
				LpMastMng.Draw();
				DrawFormatString(25, 50, 0xffffff, L"    = %d��", Coins::GetInstance().coins);
				DrawFormatString(25, 100, 0xffffff, L"    = %d�~��", Coins::GetInstance().kinken);
				//DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, transflame*4);
				DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (transflame >= maxtrans / 2) {
				LpMastMng.Run();
				game_->Draw();
				lpImglMng.AddImg(L"Resource\\image/stbs.png", Vector2(800 / 2, 600 / 2));
				lpImglMng.AddImg(L"Resource\\image/coins.png", Vector2(25, 50));
				lpImglMng.AddImg(L"Resource\\image/goldc.png", Vector2(25, 100));
				LpMastMng.Draw();
				DrawFormatString(25, 50, 0xffffff, L"    = %d��", Coins::GetInstance().coins);
				DrawFormatString(25, 100, 0xffffff, L"    = %d�~��", Coins::GetInstance().kinken);
				//DrawFormatString(0, 100, 0xffffff, L"flame = %d", transflame);
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
			if (LpMastMng.resultF_)
			{
				reseF = true;
			}
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
								gFcon = 1;
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
				else if (gFcon > 30)
					lpImglMng.AddImg(L"Resource\\image/bat.png", Vector2(800 - 32, 32));

				lpImglMng.AddImg(L"Resource\\image/car.png", Vector2(px + 16, py + 16));
				lpImglMng.AddImg(L"Resource\\image/stbs.png", Vector2(800/2, 600/2));
				lpImglMng.AddImg(L"Resource\\image/coins.png", Vector2(25, 50));
				lpImglMng.AddImg(L"Resource\\image/goldc.png", Vector2(25, 100));
			}
			LpMastMng.Draw();
			if (gFcon != 0)
			{
				DrawFormatString(25, 50, 0xffffff, L"    = %d��", Coins::GetInstance().coins);
				DrawFormatString(25, 100, 0xffffff, L"    = %d�~��", Coins::GetInstance().kinken);
			}
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




