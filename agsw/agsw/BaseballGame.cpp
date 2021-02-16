#include <DxLib.h>
#include <cmath>
#include <random>
#include "BaseballGame.h"

Vector2 RefLectVec(const Vector2& i, const Vector2& n)
{
	Vector2 r = i - Vector2(n.x * (Dot(i, n) * 2), n.y * (Dot(i, n) * 2));
	return r;
}

float GetRadian(std::pair<Vector2, Vector2> hillPos)
{
	auto up = hillPos.first;
	auto down = hillPos.second;

	if (hillPos.second.y < hillPos.first.y) {
		up = hillPos.second;
		down = hillPos.first;
	}
	return atan2(up.y - down.y, up.x - down.x);
}

BaseballGame::BaseballGame()
{
	init();
}

BaseballGame::~BaseballGame()
{
}

void BaseballGame::RunGame(void)
{
	if (CheckHitKey(KEY_INPUT_Z))
		PushBat();
	auto key = CheckHitKey(KEY_INPUT_SPACE);
	if (!bollF_)
		if ((key == true)) 
		{
			boll_.alive = true;
			bollF_ = true;
		}
	if (boll_.alive)
	{
		boll_.vec_.y = 1;
	}
	boll_.updata();
	BatMoveing();
	gcon_++;
}

void BaseballGame::DrawGame(void)
{
	printf("%d\n", batt_.kakudo_);
	//ƒQ[ƒ€ƒGƒŠƒA‚Ì•`‰æ
	DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
	DrawLine(batt_.batPos1_.x, batt_.batPos1_.y, batt_.batPos2_.x, batt_.batPos2_.y, 0xff0000);
	DrawCircle(boll_.pos_.x, boll_.pos_.y,10,0xff0000);
}

void BaseballGame::init(void)
{
	batt_.leng_ = 100;
	batt_.batPos1_.x = 800 / 2 + 50;
	batt_.batPos1_.y = 600 / 2 + 150;
	batt_.batPos2_.x = batt_.batPos1_.x;
	batt_.batPos2_.y = batt_.batPos1_.y + batt_.leng_;
	PushBatF_ = true;
	PushBatMOVEF_ = false;
	batt_.kakudo_ = 0;
	BatMOVErF_ = false;
	gcon_ = 0;
	bollF_ = false;
	boll_.alive = false;
	boll_.pos_.x = 800 / 2;
	boll_.pos_.y = 600 / 2 - 200;
}

void BaseballGame::PushBat(void)
{
	if (PushBatF_)
	{
		BatMOVErF_ = false;
		PushBatF_ = false;
		PushBatMOVEF_ = true;
		batt_.batPos2_.x = batt_.batPos1_.x;
		batt_.batPos2_.y = batt_.batPos1_.y + batt_.leng_;
	}
}

void BaseballGame::BatMoveing(void)
{
	//if(gcon_/10%2==0)
		if (PushBatMOVEF_)
		{
			Vector2 tmpVec;
			tmpVec.y = sin((batt_.kakudo_ + 90) * (DX_PI_F / 180)) * batt_.leng_;
			tmpVec.x = cos((batt_.kakudo_ + 90) * (DX_PI_F / 180)) * batt_.leng_;
			if (!BatMOVErF_)
				batt_.kakudo_++;
			else
				batt_.kakudo_--;
			batt_.batPos2_ = tmpVec+ batt_.batPos1_;

			if (batt_.kakudo_ >= 90)
			{
				BatMOVErF_ = true;
			}
			if (batt_.kakudo_ < 0)
			{
				batt_.batPos2_.x = batt_.batPos1_.x;
				batt_.batPos2_.y = batt_.batPos1_.y + batt_.leng_;
				batt_.kakudo_ = 0;
				PushBatF_ = true;
				PushBatMOVEF_ = false;
			}
			std::pair<Vector2, Vector2> batp = {batt_.batPos1_,batt_.batPos2_};
			std::pair<Vector2, Vector2> bollp = { boll_.pos_ ,{0,20} };
			if (CheckHitBat(bollp, batp))
			{
				auto hillflt = GetRadian(batp);
				Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
				tvec.Normalized();
				auto rtvec = RefLectVec(boll_.vec_.Normalized(), tvec);
				auto spesize = RefLectVec(boll_.vec_, tvec).Magnitude();
				rtvec.x *= spesize;
				rtvec.y *= spesize;
				boll_.vec_ = rtvec;
			}
		}
}

bool BaseballGame::CheckHitBat(std::pair<Vector2, Vector2> par1, std::pair<Vector2, Vector2> par2)
{
	Vector2 v = par2.first - par1.first;
	float tmpF = Cross(par1.second, par2.second);

	if (Cross(par1.second, par2.second) == 0.0f)
		return false;

	Vector2 tmpvec = { Cross(v, par1.second) ,Cross(v, par2.second) };
	//if (v.y < 0)
	//	v.y *= -1;
	tmpvec.x = tmpvec.x / tmpF;
	tmpvec.y = tmpvec.y / tmpF;

	const float eps = 0.00001f;
	//0<= n <=1 0<= n <=1‚ª“–‚½‚Á‚Ä‚é‚È‚ç‚»‚Ì‹t
	if (tmpvec.y + eps < 0 || tmpvec.y - eps > 1 || tmpvec.x + eps < 0 || tmpvec.x - eps > 1)
		return false;

	return true;
}
