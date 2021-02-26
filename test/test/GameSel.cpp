#include <DxLib.h>
#include "WorldSoccer.h"
#include "CarRace.h"
#include "JankenPon.h"
#include "Result.h"
#include "mnj/ImgMnj.h"
#include "GameSel.h"

int gameselbgm;

void GameSel::Run(std::shared_ptr<BaseGame>& baseGame)
{
	CheckMousePosHit();
	if (initflag) {
		PlaySoundMem(gameselbgm, DX_PLAYTYPE_LOOP);
		initflag = false;
	}
	auto tmp = baseGame;

	if (onforMouseLefOld_ && !onforMouseLef_)
	{
		if (nowMowsGame_ == thisGameis::CarraceGame) 
		{
			baseGame = std::make_shared<CarRace>();
			baseGame->Init();
		}
		if (nowMowsGame_ == thisGameis::RSPGame)
		{
			baseGame = std::make_shared<JankenPon>();
			baseGame->Init();
		}
		if (nowMowsGame_ == thisGameis::SoccerGame) 
		{
			baseGame = std::make_shared<WorldSoccer>();
			baseGame->Init();
		}
		if (nowMowsGame_ == thisGameis::NOSELGAME)
		{
			baseGame = std::make_shared<Result>();
			baseGame->Init();
		}

		//if (CheckHitKey(KEY_INPUT_1)) {
		//	baseGame = std::make_shared<WorldSoccer>();
		//	baseGame->Init();
		//}
		//if (CheckHitKey(KEY_INPUT_2)) {
		//	baseGame = std::make_shared<CarRace>();
		//	baseGame->Init();
		//}
		//if (CheckHitKey(KEY_INPUT_3)) {
		//	baseGame = std::make_shared<JankenPon>();
		//	baseGame->Init();
		//}
		//if (CheckHitKey(KEY_INPUT_RETURN))
		//{
		//	baseGame = std::make_shared<Result>();
		//	baseGame->Init();
		//}
		if (tmp != baseGame) {
			StopSoundFile();
			StopSoundMem(gameselbgm);
		}
	}
}

void GameSel::Draw()
{
	//DrawFormatString(0, 0, 0xffffff, L"gameSel");	
	lpImglMng.AddImg(L"Resource\\image/selsel.png", Vector2(800 / 2, 600 / 2));

	if (nowMowsGame_ != thisGameis::NOSELGAME)
	{
		auto tmpPos = mousePos_;
		tmpPos.x += 88;
		tmpPos.y += 110;
		if (nowMowsGame_ == thisGameis::CarraceGame)
			lpImglMng.AddImg(L"Resource\\image/minset.png", tmpPos);
		if (nowMowsGame_ == thisGameis::RSPGame)
			lpImglMng.AddImg(L"Resource\\image/minset2.png", tmpPos);
		if (nowMowsGame_ == thisGameis::SoccerGame)
			lpImglMng.AddImg(L"Resource\\image/minset3.png", tmpPos);
	}
	lpImglMng.AddImg(L"Resource\\image/car.png", Vector2(mousePos_.x + 16, mousePos_.y + 16));

	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(70,138));
	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(240,439));


	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(310, 138));
	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(480, 439));


	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(577, 138));
	//lpImglMng.AddImg(L"Resource\\image/b.png", Vector2(746, 439));


	//ƒQ[ƒ€ƒGƒŠƒA‚Ì•`‰æ
	//DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
}

void GameSel::Init()
{
	if (!CheckSoundFile()) {
		gameselbgm = LoadSoundMem(L"Resource\\music/title.mp3");
	}
	initflag = true;
	mousePos_ = {0,0};
	nowMowsGame_ = thisGameis::NOSELGAME;
	SetMouseDispFlag(false);
	onforMouseLef_ = false;
	onforMouseLefOld_ = onforMouseLef_;
}

GameSel::GameSel()
{
}

GameSel::~GameSel()
{
}

void GameSel::CheckMousePosHit(void)
{
	onforMouseLefOld_ = onforMouseLef_;
	int px, py;
	DxLib::GetMousePoint(&px, &py);
	mousePos_.x = px;
	mousePos_.y = py;

	if (px >= 70 && px <= 240 && py >= 138 && py <= 439)
		nowMowsGame_ = thisGameis::CarraceGame;
	else if(px >= 310 && px <= 480 && py >= 138 && py <= 439)
		nowMowsGame_ = thisGameis::RSPGame;
	else if (px >= 577 && px <= 746 && py >= 138 && py <= 439)
		nowMowsGame_ = thisGameis::SoccerGame;
	else
		nowMowsGame_ = thisGameis::NOSELGAME;

	int Mouse = GetMouseInput();
	if (Mouse & MOUSE_INPUT_LEFT)
	{
		onforMouseLef_ = true;
	}
	else
	{
		onforMouseLef_ = false;
	}
}
