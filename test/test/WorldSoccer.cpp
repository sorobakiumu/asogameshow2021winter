#include "WorldSoccer.h"
#include "Result.h"
#include <DxLib.h>
#include<random>
#include"GameSel.h"
#include "Coins.h"
#include "mnj/ImgMnj.h"

int soccerbgm;

void WorldSoccer::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (initflag) {
		PlaySoundMem(soccerbgm,DX_PLAYTYPE_LOOP);
		initflag = false;
	}

	downpt = std::rand() % 200+300;
	int x, y;
	GetMousePoint(&x, &y);
	holl.x = max(min(x, hollmax_x), hollmin_x);
	if (gamestart) {
		if (flame % 60 == 0) {
			bolls.emplace_back(new Boll({ downpt,1.0f }));
		}
		flame++;
		printf("射出場所＝[%f]\n", downpt);

		//当たり判定
		for (auto boll : bolls) {
			boll->vec_.y += gravity;
			IsHit(boll);
		}
		for (auto b : bolls) {
			b->updata();
			if (b->pos_.x - bollR < xoffset) {
				b->pos_.x = xoffset + bollR;
			}
			else if (b->pos_.x + bollR > xoffset + 400) {
				b->pos_.x = xoffset + 400 - bollR;
			}
			b->angle_++;
		}
		for (auto boll : bolls) {
			if (boll->alive) {
				if (boll->pos_.y > 600 + bollR) {
					boll->alive = false;
					life--;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_5)) {
		baseGame = std::make_shared<GameSel>();
		baseGame->Init();
		StopSoundMem(soccerbgm);
	}
	if (life <= 0&&gamestart) {
		gamestart = false;
		for(auto boll:bolls){
			boll->vec_ = {};
		}
		int c = score / 1000;
		Coins::GetInstance().coins += c;
	}
	if (!gamestart) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			gamestart = true;
			life = 5;
			score = 0;
			Coins::GetInstance().coins--;
			bolls.clear();
		}
	}

	tcon_++;
}

void WorldSoccer::Draw()
{
	//ゲームエリアの描画
	//DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);

	//DrawBox(hollmin_x, holl.y - hollR / 2, hollmax_x, holl.y + hollR / 2, 0xb8860b, true);
	//DrawBox(hollmin_x + bollR, holl.y - hollR / 2 + bollR, hollmax_x - bollR, holl.y + hollR / 2 - bollR, 0xffffff, true);

	lpImglMng.AddImg(L"Resource\\image/tile2.png", Vector2(800/2, 600/2));
	lpImglMng.AddImg(L"Resource\\image/setumei3.png", Vector2(800 / 2 + 300, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/soccerGame!.png", Vector2(800/2, 600/2));
	

	//ボールの描画
	for (auto b : bolls) {
		if (b->alive) {
			auto color = 0xff0000;
			//DrawCircle(b->pos_.x, b->pos_.y, bollR, color, true, true);
			//DrawCircle(b->pos_.x, b->pos_.y, bollR, 0x000000, false, true);
			lpImglMng.AddImg(L"Resource\\image/ball.png", Vector2(b->pos_.x, b->pos_.y),b->angle_);
		}
	}

	//打ちだし場所の描画(デバッグ用)
#ifdef _DEBUG
	//DrawCircle(downpt, 20, 20, 0x000000, false, true);
	lpImglMng.AddImg(L"Resource\\image/ball.png", Vector2(downpt, 20));

#endif


	//ピンの描画
	//for (auto p : pinPositions) {
	//	DrawCircle(p.x, p.y, pinsize, 0x000000, true, true);
	//}
	//DrawCircle(holl.x, holl.y, hollR, 0x000000, true, true);
	lpImglMng.AddImg(L"Resource\\image/ga.png", Vector2(holl.x, holl.y));

	if (!gamestart) {

		lpImglMng.SetDrawBoxIm();

		if (tcon_ / 60 % 2 == 0)
		{
			lpImglMng.AddImg(L"Resource\\image/onecoin.png", Vector2(800 / 2, 600 / 2));
			lpImglMng.AddImg(L"Resource\\image/ps.png", Vector2(800 / 2, 600 / 2));
		}
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		//DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, GetColor(0, 0, 0), TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawFormatString(0, 0, 0xffffff, L"スコア　%d", score);
	DrawFormatString(0, 20, 0xffffff, L"ライフ　%d", life);
}

void WorldSoccer::Init()
{
	PinInit();
	holl.x = 400;
	holl.y = 490;
	initflag = true;
	soccerbgm = LoadSoundMem(L"Resource\\music/soccer.mp3");
	tcon_ = 0;
}

void WorldSoccer::PinInit()
{
	for (int y = 0; y < ynum; y++) {
		int xnum = startnum;
		if (y % 2 == 1) {
			xnum = startnum + 1;
		}
		for (int x = 0; x < xnum; x++) {
			auto xnumoffset = 50;
			if (xnum != startnum) {
				xnumoffset /= 2;
			}
			pinPositions.emplace_back(Vector2(xoffset + xnumoffset + 70 * x+30, 100 + 70 * y));
		}
	}
}

void WorldSoccer::IsHit(std::shared_ptr<Boll>& boll)
{
	for (auto pin : pinPositions) {
		if ((boll->pos_ - pin).Magnitude() <= (bollR + pinsize)) {
			auto distance = pin - boll->pos_;
			if (distance.x == 0) {
				distance.x = (std::rand() % 2) * 2 - 1;
			}
			auto vec = boll->vec_;
			boll->vec_.x += distance.x * -0.1;
			boll->vec_.y = distance.y * -0.1;

		}
	}
	hollIsHit(boll);
}

void WorldSoccer::hollIsHit(std::shared_ptr<Boll>& boll)
{
	if (!boll->alive) {
		return;
	}
	if (boll->pos_.x + bollR * 2 < holl.x + hollR * 2 &&
		boll->pos_.x - bollR * 2 > holl.x - hollR * 2 &&
		boll->pos_.y + bollR * 2 < holl.y + hollR * 2 &&
		boll->pos_.y - bollR * 2 > holl.y - hollR * 2) 
	{
		boll->alive = false;
		score += 100;
	}
}