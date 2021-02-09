#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <memory>
#include <tuple>
#include "Geometry.h"
#include <cmath>
#include <random>

class Boll {
public:
	Vector2 pos_;
	Vector2 vec_;
	float r = 20;
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
	float gravity = 0.5f;
}
float GetRadian(Vector2& up, Vector2& down);
void gPosChange(std::shared_ptr<Boll>& boll, std::pair<Vector2, Vector2> hillPos) {
	auto up = hillPos.first;
	auto down = hillPos.second;

	if (hillPos.second.y < hillPos.first.y) {
		up = hillPos.second;
		down = hillPos.first;
	}

	auto radian = GetRadian(up, down);

	auto xvec = 0.5f;
	if (up.x > down.x) {
		xvec *= -1.0;
	}
	boll->vec_.x += xvec;
	boll->vec_.y += xvec * tan(radian);

}

float GetRadian(Vector2& up, Vector2& down)
{
	return atan2(up.y - down.y, up.x - down.x);
}


std::pair<Vector2, Vector2> HillPositions[] = {
	{{xoffset + xgameScreen,130} ,{400,110}},
	{{xoffset,220}, {400,200}},
	{{xoffset + xgameScreen,330} ,{400,300}},
	{{xoffset,420} ,{400,400}}
};

const float pinsize = 2.5f;
const int startnum = 7;
const int ynum = 5;
std::vector<Vector2> pinPositions;

void HillIsHit(std::shared_ptr<Boll>& boll);

void PinInit();


bool zff = false;
Vector2 neuVec = {0,0};

void bam(void)
{
	for (auto b : bolls)
	{
		///����*����+(�d�͉����x*����)/2
		//tmpvec.y += -2 * (100 * bulletCon_[i] / 60 + static_cast<float>(S_GRAVITY * bulletCon_[i] / 60) * 2 / 2);
		auto* ve = &b->vec_;
		if (CheckHitKey(KEY_INPUT_Z))
		{
			if (!zff)
			{

				auto hillflt = GetRadian(HillPositions[0].first, HillPositions[0].second);
				ve->y = 10 * (100 * neuVec.y / 60 + static_cast<float>(9.8f * neuVec.y / 60) * 2 / 2)/10;
				ve->x--;
				neuVec.y++;
			}
			zff = true;
		}
		else
		{
			if (neuVec.y != 0)
				if (neuVec.y < 30)
				{
					neuVec.y++;
					auto hillflt = GetRadian(HillPositions[0].first, HillPositions[0].second);
					ve->y = -0.5 * (1 * neuVec.y + static_cast<float>(9.8f * neuVec.y) * 2 / 2)/30;
					ve->x = -0.5;

				}
				else
				{
					neuVec = { 0,0 };
					zff = false;
				}
		}
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

	//�s���̏�����
	PinInit();

	bool balF = false;
	while (true)
	{
		//�ړ����͏��
		key = CheckHitKey(KEY_INPUT_SPACE);
		if(!balF)
			if ((key == true) && (oldkey == true)) {
				bolls.emplace_back(new Boll({ downpt,1.0f }));
				balF = true;
			}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			downpt += 3;
		}
		else if (CheckHitKey(KEY_INPUT_LEFT)) {
			downpt -= 3;
		}
		oldkey = key;

		//�����蔻��
		for (auto boll : bolls) {
			boll->vec_.y += gravity;
			//��̓����蔻��
			HillIsHit(boll);
			/*for (auto pin : pinPositions) {
				if ((boll->pos_ - pin).Magnitude() <= (boll->r + pinsize)) {
					auto distance = pin - boll->pos_;
					if (distance.x == 0) {
						distance.x = (std::rand() % 2) * 2 - 1;
					}
					auto vec = boll->vec_;
					vec.x += distance.x * -0.1;
					vec.y = distance.y * -0.1;
					auto pos = boll->pos_ + vec;
					if ((boll->pos_ - pin).Magnitude() <= (boll->r + pinsize)) {

					}


				}
			}*/
		}

		ClearDrawScreen();
		//�Q�[���G���A�̕`��
		DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);

		//�{�[���̕`��
		for (auto b : bolls) {
			auto color = 0xff0000;
			DrawCircle(b->pos_.x, b->pos_.y, b->r, color, true, true);
			DrawCircle(b->pos_.x, b->pos_.y, b->r, 0x000000, false, true);
		}
		//�ł������ꏊ�̕`��(�f�o�b�O�p)
		DrawCircle(downpt, 20, 20, 0x000000, false, true);
		//��̕`��
		for (auto h : HillPositions) {
			DrawLine(h.first.x,h.first.y,h.second.x,h.second.y,0x000000);
		}
		//�s���̕`��
		//for (auto p : pinPositions) {
		//	DrawCircle(p.x, p.y, pinsize, 0x000000, true, true);
		//}
		ScreenFlip();
		//�{�[���̍X�V
		bam();
		for (auto b : bolls) {
			b->updata();
			if (b->pos_.x - b->r < xoffset) {
				b->pos_.x = xoffset + b->r;
			}
			else if (b->pos_.x + b->r > xoffset + 400) {
				b->pos_.x = xoffset + 400 - b->r;
			}
		}
		for (auto b : bolls) {
			if (b->pos_.y > 600) {
				bolls.clear();
				balF = false;
			}
		}
	}

}
//�s���̏�����
void PinInit()
{
	for (int y = 0; y < ynum; y++) {
		int xnum = startnum;
		if (y % 2 == 1) {
			xnum = startnum + 1;
		}
		for (int x = 0; x < xnum; x++) {
			auto xnumoffset = 50;
			if (xnum != startnum) {
				xnumoffset = 25;
			}
			pinPositions.emplace_back(Vector2(xoffset + xnumoffset + 70 * x, 100 + 70 * y));
		}
	}
}

void HillIsHit(std::shared_ptr<Boll>& boll)
{
	for (auto hillpos : HillPositions) {
		auto hillnorm = (hillpos.second - hillpos.first).Normalized();
		auto b = boll->pos_ - hillpos.first;
		auto P = hillpos.first + hillnorm * (hillnorm * b);
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
		else {
			boll->alive = true;
		}
	}
}


