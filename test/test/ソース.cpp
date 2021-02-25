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
	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

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
				DrawFormatString(0, 50, 0xffffff, L"coins = %d��", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d�~��", Coins::GetInstance().kinken);
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
				DrawFormatString(0, 50, 0xffffff, L"coins = %d��", Coins::GetInstance().coins);
				DrawFormatString(0, 70, 0xffffff, L"ticket = %d�~��", Coins::GetInstance().kinken);
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
			DrawFormatString(0, 50, 0xffffff, L"coins = %d��", Coins::GetInstance().coins);
			DrawFormatString(0, 70, 0xffffff, L"ticket = %d�~��", Coins::GetInstance().kinken);
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




