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
float GetRadian(std::pair<Vector2, Vector2>);
void gPosChange(std::shared_ptr<Boll>& boll, std::pair<Vector2, Vector2> hillPos) {
	auto up = hillPos.first;
	auto down = hillPos.second;

	if (hillPos.second.y < hillPos.first.y) {
		up = hillPos.second;
		down = hillPos.first;
	}

	auto radian = GetRadian(hillPos);

	auto xvec = 0.5f;
	if (up.x > down.x) {
		xvec *= -1.0;
	}
	boll->vec_.x += xvec;
	boll->vec_.y += xvec * tan(radian);

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
Vector2 neuVec = { 0,0 };
int neuCon = 0;
float powP=40;

Vector2 RefLectVec(const Vector2& i, const Vector2& n)
{
	//反射ベクトルの式
	//R=I-2*（N・I）N
	//をそのままプログラムにする
	//ただし、オペレーターオーバーロード
	//の関係で
	//
	Vector2 r = i - Vector2(n.x * (Dot(i, n) * 2), n.y * (Dot(i, n) * 2));
	return r;
}

void bam(void)
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		powP += 0.5;
		if (powP > 100)
		{
			powP = 100;
		}
		printf("ぱわぁぽいんと＝[%3.3f]\n", powP);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		powP -= 0.5;
		if (powP < 0)
		{
			powP = 0;
		}
		printf("ぱわぁぽいんと＝[%3.3f]\n", powP);
	}
	
	for (auto b : bolls)
	{
		auto* ve = &b->vec_;

		if (CheckHitKey(KEY_INPUT_Z) && !zff)
		{
			auto hillflt = GetRadian(HillPositions[0]);
			//float momentX = (float)(Math.Sin(radian) * 0.1);
			//float momentZ = (float)(Math.Cos(radian) * 0.1);
			Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
			//if (rand() % 2 == 0)
				neuVec.x -= powP;
			tvec.Normalized();
			auto rtvec = RefLectVec(neuVec, tvec);
			zff = true;
			neuVec = rtvec / 10;
			neuVec.x *= 2;
			neuCon++;
		}
		else if (CheckHitKey(KEY_INPUT_X) && !zff)
		{
			auto hillflt = GetRadian(HillPositions[0]);
			//float momentX = (float)(Math.Sin(radian) * 0.1);
			//float momentZ = (float)(Math.Cos(radian) * 0.1);
			Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
			//if (rand() % 2 == 0)
			neuVec.x = -powP;
			tvec.Normalized();
			auto rtvec = RefLectVec(neuVec, tvec);
			zff = true;
			neuVec = rtvec / 10;
			if (neuVec.x < 0)
				neuVec.x *= -1;
			neuVec.x *= 2;
			neuCon++;
		}
		else
		{
			if(neuCon == 0)
			{
				neuVec = { 0,0 };
				zff = false;
			}
			else
			{
				if (neuCon/2 < 5)
				{
					*ve = neuVec;
					neuCon++;
				}
				else
				{
					neuCon = 0;
				}
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

	//ピンの初期化
	PinInit();

	bool balF = false;
	while (true)
	{
		//移動入力情報
		key = CheckHitKey(KEY_INPUT_SPACE);
		if (!balF)
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

		//当たり判定
		for (auto boll : bolls) {
			boll->vec_.y += gravity;
			//坂の当たり判定
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
		//ゲームエリアの描画
		DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);

		//ボールの描画
		for (auto b : bolls) {
			auto color = 0xff0000;
			DrawCircle(b->pos_.x, b->pos_.y, b->r, color, true, true);
			DrawCircle(b->pos_.x, b->pos_.y, b->r, 0x000000, false, true);
		}
		//打ちだし場所の描画(デバッグ用)
		DrawCircle(downpt, 20, 20, 0x000000, false, true);
		//坂の描画
		for (auto h : HillPositions) {
			DrawLine(h.first.x, h.first.y, h.second.x, h.second.y, 0x000000);
		}
		//ピンの描画
		//for (auto p : pinPositions) {
		//	DrawCircle(p.x, p.y, pinsize, 0x000000, true, true);
		//}
		DrawFormatString(0, 0, 0xFFFFFF, L"ぱわー %3.3f ㌫ ", powP);
		ScreenFlip();
		//ボールの更新
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
//ピンの初期化
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


