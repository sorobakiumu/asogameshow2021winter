#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <memory>
#include <tuple>
#include "Geometry.h"
#include <cmath>

class Boll {
public:
	Vector2 pos_;
	Vector2 vec_;
	float r=20;
	Boll(Vector2 pos) {
		pos_ = pos;
		vec_ = {};
	}
	void updata();
	bool alive = true;
private:
};

void Boll::updata() {
	pos_ += vec_;
}

namespace {
	std::vector<std::shared_ptr<Boll>> bolls;
	const int xoffset = 200;
	const int xgameScreen = 400;
	bool oldkey = false;
	bool key = false;
	float downpt = 400;
	float gravity = 0.05f;//2.5f
	auto xvec = 0.05f;//0.5f
}

void gPosChange(std::shared_ptr<Boll>& boll, std::pair<Vector2, Vector2> hillPos) {
	auto up = hillPos.first;
	auto down = hillPos.second;

	if (hillPos.second.y < hillPos.first.y) {
		up = hillPos.second;
		down = hillPos.first;
	}

	auto radian = atan2(up.y - down.y, up.x - down.x);
	xvec = 0.5f;
	if (up.x > down.x) {
		xvec *= -1.0;
	}
	boll->vec_.x += xvec;
	boll->vec_.y += xvec * tan(radian);
	
}
 

std::pair<Vector2, Vector2> HillPositions[] = { 
	{{xoffset+xgameScreen,110} ,{400,130}},
	{{xoffset,200}, {400,220}},
	{{xoffset + xgameScreen,300} ,{400,330}},
	{{xoffset,400} ,{400,420}}
};

bool zff = false;
void bam(void)
{
	if (CheckHitKey(KEY_INPUT_Z))
	{
		if (!zff)
		{
			for (auto b : bolls) 
			{
				auto *ve = &b->vec_;
				
			}
			zff = true;
		}
	}
	else
	{
		zff = false;
	}
}

int main()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	if (DxLib_Init()) {
		return false;
	}
	ClsDrawScreen();

	bool testesF = false;

	while (ProcessMessage() == 0)
	{
		key = CheckHitKey(KEY_INPUT_SPACE);
		if (!testesF)
		{
			if ((key == true) && (oldkey == true)) {
				bolls.emplace_back(new Boll({ downpt,1.0f }));
				testesF = true;
			}
		}

		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			downpt+=3;
		}
		else if(CheckHitKey(KEY_INPUT_LEFT)){
			downpt-=3;
		}
		oldkey = key;
		for (auto boll : bolls) {
			boll->vec_.y += gravity;
			for (auto hillpos : HillPositions) {
				auto hillnorm = (hillpos.second - hillpos.first).Normalized();
				auto b = boll->pos_ - hillpos.first;
				auto P = hillpos.first + hillnorm*(hillnorm * b);
				if ((boll->pos_ - P).Magnitude() < boll->r) {
					auto A = boll->pos_ - hillpos.second;
					auto B = hillpos.first - hillpos.second;
					auto S = boll->pos_ - hillpos.first;
					if ((A * S) * (B * S) >= 0)
					{
						boll->alive = false;
						boll->vec_.y = 0;
						boll->pos_.y = P.y - boll->r;
						gPosChange(boll, hillpos);
					}
				}
				else{
					boll->alive = true;
				}
			}
		}

		ClearDrawScreen();
		DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);

		
		for (auto b : bolls) {
			auto color = 0xff0000;
			DrawCircle(b->pos_.x, b->pos_.y, b->r, color, true, true);
			DrawCircle(b->pos_.x, b->pos_.y, b->r, 0x000000, false, true);
		}
		DrawCircle(downpt, 20, 20, 0x000000, false, true);
		for (auto h : HillPositions) {
			DrawLine(h.first.x,h.first.y,h.second.x,h.second.y,0x000000);
		}
		ScreenFlip();
		for (auto b : bolls) {
			b->updata();
		}
		for (auto b : bolls) {
			if (b->pos_.y > 600) {
				bolls.clear();
				testesF = false;
			}
		}
	}
}


