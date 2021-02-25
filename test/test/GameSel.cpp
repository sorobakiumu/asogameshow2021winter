#include "GameSel.h"
#include <DxLib.h>
#include "WorldSoccer.h"
#include "CarRace.h"
#include "JankenPon.h"

int gameselbgm;

void GameSel::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (initflag) {
		PlaySoundMem(gameselbgm, DX_PLAYTYPE_LOOP);
		initflag = false;
	}
	auto tmp = baseGame;
	if (CheckHitKey(KEY_INPUT_1)) {
		baseGame = std::make_shared<WorldSoccer>();
		baseGame->Init();
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		baseGame = std::make_shared<CarRace>();
		baseGame->Init();
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		baseGame = std::make_shared<JankenPon>();
		baseGame->Init();
	}
	if (tmp != baseGame) {

		StopSoundFile();
		StopSoundMem(gameselbgm);
	}
}

void GameSel::Draw()
{
	DrawFormatString(0, 0, 0xffffff, L"gameSel");
	//ÉQÅ[ÉÄÉGÉäÉAÇÃï`âÊ
	DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
}

void GameSel::Init()
{
	if (!CheckSoundFile()) {
		gameselbgm = LoadSoundMem(L"Resource\\music/title.mp3");
	}

	//lpSudlMng.AddBGM(L"Resource/music/title.mp3");

	initflag = true;
}

GameSel::GameSel()
{
}

GameSel::~GameSel()
{
}
