#include <DxLib.h>
#include <cmath>
#include <random>
#include "Geometry.h"
#include "JankenPon.h"

JankenPon::JankenPon()
{
	init();	//初期化！
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

void JankenPon::RunGame(void)
{
	switch (nowmode_)
	{
	case STAY:
		StayMove();
		break;
	case JANK:
		GameMove();
		break;
	case RESER:
		ResultMove();
		break;
	case FIN:
		Finmove();
		break;
	default:
		break;
	}
}

void JankenPon::DrawGame(void)
{
	int x=50, y=50;
	switch (nowmode_)
	{
	case STAY:
		if (jcon_ < 3)
		{
			DrawFormatString(x, y, 0xFFFFFF, L"さんかい練習するよ　Zぐー　Xちょき　Cぱー");
			DrawFormatString(x, y+20, 0xFFFFFF, L"%d回目いってみよー", jcon_ + 1);
			DrawFormatString(x, y+40, 0xFFFFFF, L"じゃんけん", jcon_ + 1);
		}
		else
		{
			DrawFormatString(x, y, 0xFFFFFF, L"Zぐー　Xちょき　Cぱー");
			DrawFormatString(x, y + 20, 0xFFFFFF, L"%d回目いってみよー", jcon_ + 1);
			DrawFormatString(x, y + 40, 0xFFFFFF, L"じゃんけん", jcon_ + 1);
		}
		break;
	case JANK:
		DrawFormatString(x, y, 0xFFFFFF, L"ぽん！");
		if (gameflag_ == JGameFlag::DRAW_GF)
			DrawFormatString(x, y + 20, 0xFFFFFF, L"ひきわけだね！");
		if (gameflag_ == JGameFlag::WINCPU_GF)
			DrawFormatString(x, y + 20, 0xFF0000, L"ボクのかちだね！");
		if (gameflag_ == JGameFlag::WINYOU_GF)
			DrawFormatString(x, y + 20, 0x0000FF, L"キミのかちだね！");
		break;
	case RESER:
		if (!resconF_)
		{
			if (gameflag_ == JGameFlag::WINYOU_GF)
			{
				DrawFormatString(x, y, 0xFFFFFF, L"ルーレット！");
				DrawFormatString(x + 20, y + 20, 0xFFFFFF, L"%d　ポイント", res_);
			}
		}
		else
		{
			if (gameflag_ == JGameFlag::WINYOU_GF)
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
		DrawFormatString(x, y, 0xFF0000, L"ボクは　グー");
	}
	else if (myflg_ == JANKENACTION::TYOKI) 
	{
		DrawFormatString(x, y, 0xFF0000, L"ボクは　チョキ");
	}
	else if(myflg_ == JANKENACTION::PA)
	{
		DrawFormatString(x, y, 0xFF0000, L"ボクは　パー");
	}

	if (youact_ == JANKENACTION::GU) 
	{
		DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　グー");
	}
	else if (youact_ == JANKENACTION::TYOKI) 
	{
		DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　チョキ");
	}
	else if (youact_ == JANKENACTION::PA) 
	{
		DrawFormatString(x + 20, y + 20, 0x0000FF, L"キミは　パー");
	}


}

void JankenPon::init(void)
{
	std::ifstream tfile("data/jank.gdf");

	gameflag_ = JGameFlag::no_Gf;
	nowmode_ = JNOWMODE::STAY;
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
		if (jankenData_[otout_-1][nextfindMove_] < jankenData_[otout_-1][1]) nextfindMove_ = 1;
		if (jankenData_[otout_-1][nextfindMove_] < jankenData_[otout_-1][2]) nextfindMove_ = 2;
		//ぐー　ちょき　ぱー　えらんだものの2つさきが、勝てる手だから、たす2をする
		myflg_ = JANKENACTION(((nextfindMove_+2 ) % 3)+1);

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
		gconf_ = true;
		nowmode_ = JNOWMODE::JANK;
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
		gameflag_ = JGameFlag::no_Gf;
		nowmode_ = JNOWMODE::STAY;
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
			nowmode_ = JNOWMODE::RESER;
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
	if (gameflag_ != JGameFlag::WINYOU_GF)
	{
		resconF_ = true;
	}
	if (!resconF_)
	{
		res_++;
		if (res_ > 10)
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
			nowmode_ = JNOWMODE::FIN;
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
			gameflag_ = JGameFlag::DRAW_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = JGameFlag::WINYOU_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = JGameFlag::WINCPU_GF;
		}
	}
	if (youact_ == JANKENACTION::TYOKI)
	{
		if (myflg_ == JANKENACTION::GU)
		{
			gameflag_ = JGameFlag::WINCPU_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = JGameFlag::DRAW_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = JGameFlag::WINYOU_GF;
		}
	}
	if (youact_ == JANKENACTION::PA)
	{
		if (myflg_ == JANKENACTION::GU)
		{
			gameflag_ = JGameFlag::WINYOU_GF;
		}
		if (myflg_ == JANKENACTION::TYOKI)
		{
			gameflag_ = JGameFlag::WINCPU_GF;
		}
		if (myflg_ == JANKENACTION::PA)
		{
			gameflag_ = JGameFlag::DRAW_GF;
		}
	}
}
