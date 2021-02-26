#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <memory>
#include <tuple>
#include "Geometry.h"
#include <cmath>
#include <random>
#include <time.h>
#include "JankenPon.h"
#include "Result.h"
#include "mnj/ImgMnj.h"
#include "Coins.h"

JankenPon::JankenPon()
{
}

JankenPon::~JankenPon()
{
	std::ofstream tfileo("data/jank.gdf");//ゲームデータファイル読み込み
	if (!tfileo)
	{
		//もしもないなら何もしない
	}
	else
	{
		//あるなら書き込んでセーブ！
		int tx = 0;
		do
		{
			std::string ts = std::to_string(jankenData_[tx / 3][tx % 3]);
			tfileo << ts;
			tfileo << std::endl;
			tx++;
		} while (tx < JankenMAX * JankenMove);
		tfileo.close();
	}
}

void JankenPon::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (initflag) {
		PlaySoundMem(gcpsound,DX_PLAYTYPE_LOOP);
		initflag = false;
	}
	switch (nowmode_)
	{
	case STAY:
		printf_s("STAY\n");
		StayMove();
		break;
	case JANK:
		printf_s("JANK\n");
		GameMove();
		break;
	case RESER:
		printf_s("RESER\n");
		ResultMove();
		break;
	case FIN:
		printf_s("FIN\n");
		Finmove();
		break;
	default:
		break;
	}
	if (CheckHitKey(KEY_INPUT_5)) {
		baseGame = std::make_shared<Result>();
		baseGame->Init();
		StopSoundMem(gcpsound);
	}
}

void JankenPon::Draw(void)
{

	lpImglMng.AddImg(L"Resource\\image/tile3.png", Vector2(800 / 2, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/setumei2.png", Vector2(800 / 2+300, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/jan.png", Vector2(800 / 2, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/ruru.png", Vector2(800 / 2, 600 / 2));
	if (res_ == 0)
		lpImglMng.AddImg(L"Resource\\image/rubac.png", Vector2(800 / 2, 600 / 2));
	int x = 50, y = 50;
	switch (nowmode_)
	{
	case STAY:
		if (jcon_ < 3)
		{
			printf_s("さんかい練習するよ　Zぐー　Xちょき　Cぱー\n");
			printf_s("%d回目いってみよー\n", jcon_ + 1);
			printf_s("じゃんけん\n");
			//DrawFormatString(x, y, 0xFFFFFF, L"さんかい練習するよ　Zぐー　Xちょき　Cぱー");
			//DrawFormatString(x, y + 20, 0xFFFFFF, L"%d回目いってみよー", jcon_ + 1);
			//DrawFormatString(x, y + 40, 0xFFFFFF, L"じゃんけん", jcon_ + 1);
		}
		else
		{
			printf_s("Zぐー　Xちょき　Cぱー\n");
			printf_s("%d回目いってみよー\n", jcon_ + 1);
			printf_s("じゃんけん\n");
			//DrawFormatString(x, y, 0xFFFFFF, L"Zぐー　Xちょき　Cぱー");
			//DrawFormatString(x, y + 20, 0xFFFFFF, L"%d回目いってみよー", jcon_ + 1);
			//DrawFormatString(x, y + 40, 0xFFFFFF, L"じゃんけん", jcon_ + 1);
		}
		break;
	case JANK:
		DrawFormatString(x, y, 0xFFFFFF, L"ぽん！");
		if (gameflag_ == GameFlag::DRAW_GF)
			DrawFormatString(x, y + 20, 0xFFFFFF, L"ひきわけだね！");
		if (gameflag_ == GameFlag::WINCPU_GF)
			DrawFormatString(x, y + 20, 0xFF0000, L"ボクのかちだね！");
		if (gameflag_ == GameFlag::WINYOU_GF)
			DrawFormatString(x, y + 20, 0x0000FF, L"キミのかちだね！");
		break;
	case RESER:
		if (!resconF_)
		{
			if (gameflag_ == GameFlag::WINYOU_GF)
			{
				DrawFormatString(x, y, 0xFFFFFF, L"ルーレット！");
				DrawFormatString(x + 20, y + 20, 0xFFFFFF, L"%d　ポイント", res_);
			}
		}
		else
		{
			if (gameflag_ == GameFlag::WINYOU_GF)
			{
				DrawFormatString(x, y, 0xFFFFFF, L"やったね！");
				DrawFormatString(x + 20, y + 20, 0xFFFFFF, L"%d　ポイント", res_);
			}
			DrawFormatString(x, y + 40, 0xFFFFFF, L"スペースキーを押してね");
		}
		break;
	case FIN:
		break;
	default:
		break;
	}

	y += 40;
	x += 200;
	if (myflg_ == JANKENACTION::GU)
	{
		lpImglMng.AddImg(L"Resource\\image/fir.png", Vector2(800 / 2, 600 / 2));
		//DrawFormatString(x, y, 0xFF0000, L"ボクは　グー");
	}
	else if (myflg_ == JANKENACTION::TYOKI)
	{
		lpImglMng.AddImg(L"Resource\\image/ref.png", Vector2(800 / 2, 600 / 2));
		//DrawFormatString(x, y, 0xFF0000, L"ボクは　チョキ");
	}
	else if (myflg_ == JANKENACTION::PA)
	{
		lpImglMng.AddImg(L"Resource\\image/acu.png", Vector2(800 / 2, 600 / 2));
		//DrawFormatString(x, y, 0xFF0000, L"ボクは　パー");
	}

	if (youact_ == JANKENACTION::GU)
	{
		lpImglMng.AddImg(L"Resource\\image/fir.png", Vector2(800 / 2, 500));
		//DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　グー");
	}
	else if (youact_ == JANKENACTION::TYOKI)
	{
		lpImglMng.AddImg(L"Resource\\image/ref.png", Vector2(800 / 2, 500));
		//DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　チョキ");
	}
	else if (youact_ == JANKENACTION::PA)
	{
		lpImglMng.AddImg(L"Resource\\image/acu.png", Vector2(800 / 2, 500));
		//DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　パー");
	}


}

void JankenPon::Init(void)
{
	std::ifstream tfile("data/jank.gdf");

	gameflag_ = GameFlag::no_Gf;
	nowmode_ = NOWMODE::STAY;
	youact_ = JANKENACTION::NO;
	myflg_ = JANKENACTION::NO;
	resconNum_ = 0;
	resconF_ = false;
	jcon_ = 0;
	res_ = 0;
	nextfindMove_ = 0;
	otout_ = 0;
	gconf_ = false;
	gcon_ = 0;
	if (!tfile)
	{
		for (int x = 0; x < JankenMove; x++)
		{
			for (int y = 0; y < JankenMAX; y++)
			{
				jankenData_[x][y] = 0;
			}
		}
	}
	else
	{
		int tcon = 0;
		std::string tmpS;
		int tx = 0;
		do
		{
			std::getline(tfile, tmpS);
			if (tfile.eof())
			{
				if (tcon == 0)
				{
					for (int x = 0; x < JankenMove; x++)
					{
						for (int y = 0; y < JankenMAX; y++)
						{
							jankenData_[x][y] = 0;
						}
					}
				}
				break;
			}
			jankenData_[tx / 3][tx % 3] = atoi(tmpS.c_str());
			tx++;
			tcon++;
		} while (!tfile.eof());
		tfile.close();
	}
	initflag = true;
	LoadSoundMem(L"Resource\\music/gcp.mp3");
}

void JankenPon::SetAct(void)
{
	srand((unsigned)time(NULL));
	nextfindMove_ = 0;
	if (jcon_ < 3)
	{
		myflg_ = JANKENACTION((rand() % 3) + 1);
	}
	else {
		//もし、前回が　まるまる　のとき、ちょきを出すのが多いならちょきと推察する
		//もし、前回が　まるまる　のとき、ぱー　をだすのがおおいならぱーと推察する
		//もし、すべて否であれば、						そのままぐーとすいさつする
		if (jankenData_[otout_ - 1][nextfindMove_] < jankenData_[otout_ - 1][1]) nextfindMove_ = 1;
		if (jankenData_[otout_ - 1][nextfindMove_] < jankenData_[otout_ - 1][2]) nextfindMove_ = 2;
		//ぐー　ちょき　ぱー　えらんだものの2つさきが、勝てる手だから、たす2をする
		myflg_ = JANKENACTION(((nextfindMove_ + 2) % 3) + 1);

		if (rand() % 10 == 0)
		{
			myflg_ = JANKENACTION((rand() % 3) + 1);
		}
	}
}

void JankenPon::StayMove(void)
{
	if (CheckHitKey(KEY_INPUT_Z))
	{
		youact_ = JANKENACTION::GU;
	}
	if (CheckHitKey(KEY_INPUT_X))
	{
		youact_ = JANKENACTION::TYOKI;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		youact_ = JANKENACTION::PA;
	}
	if (youact_ != JANKENACTION::NO)
	{
		Coins::GetInstance().coins--;
		gconf_ = true;
		nowmode_ = NOWMODE::JANK;
	}
}

void JankenPon::Finmove(void)
{
	youact_ = JANKENACTION::NO;
	myflg_ = JANKENACTION::NO;

	//if (CheckHitKey(KEY_INPUT_SPACE))
	{
		resconNum_ = 0;
		resconF_ = false;
		res_ = 0;
		nextfindMove_ = 0;
		gconf_ = false;
		gcon_ = 0;
		gameflag_ = GameFlag::no_Gf;
		nowmode_ = NOWMODE::STAY;
	}
}

void JankenPon::GameMove(void)
{
	if (gconf_)
	{
		jcon_++;
		SetAct();
		if (otout_ - 1 >= 0 && youact_ - 1 >= 0)
		{
			jankenData_[otout_ - 1][youact_ - 1]++;
		}
		otout_ = youact_;
		gconf_ = false;
		gcon_ = 0;

		WinCheck();
	}
	else
	{
		if (gcon_ / 60 > 2)
		{
			nowmode_ = NOWMODE::RESER;
			resconNum_ = rand() % 3;
			gcon_ = 0;
			res_ = rand() % 11;
			return;
		}
		//else
		gcon_++;
	}
}

void JankenPon::ResultMove(void)
{
	if (gameflag_ != GameFlag::WINYOU_GF)
	{
		resconF_ = true;
	}
	if (!resconF_)
	{
		res_++;
		if (res_ > 12)
			res_ = 1;

		if (gcon_ > 60 * 3 + resconNum_)
		{
			if (rand() % 5 == 0)
			{
				gcon_ = 0;
				resconF_ = true;
			}
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (gameflag_ == GameFlag::WINYOU_GF)
			{
				auto dat = static_cast<OUTPUTDAT>(res_);
				if (dat == OUTPUTDAT::GOLD)
				{
					if (rand() % 100 != 0)
					{
						res_ = 2;
						dat = OUTPUTDAT::Three1P;
					}
				}
				if (dat == OUTPUTDAT::ElevenP)
				{
					if (rand() % 50 != 0)
					{
						res_ = 8;
						dat = OUTPUTDAT::Three2P;
					}
				}
				switch (dat)
				{
				case OUTPUTDAT::GOLD:
					Coins::GetInstance().kinken++;
					break;
				case OUTPUTDAT::Three1P:
					Coins::GetInstance().coins += 3;
					break;
				case OUTPUTDAT::Seven1P:
					Coins::GetInstance().coins += 7;
					break;
				case OUTPUTDAT::One1P:
					Coins::GetInstance().coins += 1;
					break;
				case OUTPUTDAT::Five1P:
					Coins::GetInstance().coins += 5;
					break;
				case OUTPUTDAT::Two1P:
					Coins::GetInstance().coins += 2;
					break;
				case OUTPUTDAT::ElevenP:
					Coins::GetInstance().coins += 11;
					break;
				case OUTPUTDAT::Three2P:
					Coins::GetInstance().coins += 3;
					break;
				case OUTPUTDAT::Seven2P:
					Coins::GetInstance().coins += 7;
					break;
				case OUTPUTDAT::One2P:
					Coins::GetInstance().coins += 1;
					break;
				case OUTPUTDAT::Five2P:
					Coins::GetInstance().coins += 5;
					break;
				case OUTPUTDAT::Two2P:
					Coins::GetInstance().coins += 2;
					break;
				default:
					break;
				}
			}
			nowmode_ = NOWMODE::FIN;
			gcon_ = 0;
			return;
		}
	}
	gcon_++;
}

void JankenPon::WinCheck(void)
{
	if (youact_ == JANKENACTION::GU)
	{
		if (myflg_ == JANKENACTION::GU)
		{
			gameflag_ = GameFlag::DRAW_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = GameFlag::WINYOU_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = GameFlag::WINCPU_GF;
		}
	}
	if (youact_ == JANKENACTION::TYOKI)
	{
		if (myflg_ == JANKENACTION::GU)
		{
			gameflag_ = GameFlag::WINCPU_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = GameFlag::DRAW_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = GameFlag::WINYOU_GF;
		}
	}
	if (youact_ == JANKENACTION::PA)
	{
		if (myflg_ == JANKENACTION::GU)
		{
			gameflag_ = GameFlag::WINYOU_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = GameFlag::WINCPU_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = GameFlag::DRAW_GF;
		}
	}
}
