#include <DxLib.h>
#include <memory>
#include "Geometry.h"
#include <cmath>
#include <random>

class Boll {
public:
	Vector2 pos_;
	Vector2 vec_;

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

float bollR = 20;
float hollR = bollR + 5;
std::pair<Vector2, Vector2> HillPositions[] = {
	{{xoffset + xgameScreen,90} ,{400,70}},
	{{xoffset+ hollR *2,90} ,{320,70}},
	{{xoffset,220}, {400,200}},
	{{400+hollR*2,200}, {xoffset + xgameScreen-hollR*2+10,180}},
	{{xoffset + xgameScreen,330} ,{xoffset+hollR*5,300}},
	{{xoffset,420} ,{400,400}},
	{{xoffset + xgameScreen,500} ,{400,480}},

};
Vector2 hollPosition[] = {
	{xoffset + hollR, 90},
	{xoffset + xgameScreen - hollR,180 } ,
	{xoffset + hollR,300 } };

//firstが上側
std::pair<Vector2, Vector2> wallPositions[] = { 
	{{xoffset + 50,550} ,{xoffset + 50,600}},
	{{xoffset + 50 + hollR * 2,550} ,{xoffset + 50 + hollR * 2,600}}
};


const float pinsize = 2.5f;
const int startnum = 7;
const int ynum = 5;
std::vector<Vector2> pinPositions;

void HillIsHit(std::shared_ptr<Boll>& boll);

void PinInit();


bool zff = false;			//球つきフラグ
Vector2 neuVec = { 0,0 };	//フレーム毎の移動量
int neuCon = 0;				//玉つき用のカウント
float powP = 40;			//たまつきのパワー変数

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

/// <summary>
/// 球をつくための関数
/// </summary>
/// <param name="pow">パワー値</param>
void bam(int pow = powP)
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
			Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
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
			Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
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
		else if (CheckHitKey(KEY_INPUT_C) && !zff)
		{
			auto hillflt = GetRadian(HillPositions[0]);
			Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
			neuVec.y -= pow;
			tvec.Normalized();
			auto rtvec = RefLectVec(neuVec, tvec);
			zff = true;
			neuVec = rtvec / 10;
			neuVec.x *= 2;
			neuCon++;
		}
		else
		{
			if (neuCon == 0)
			{
				neuVec = { 0,0 };
				zff = false;
			}
			else
			{
				if (neuCon / 2 < 5)
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

void pinIshit(std::shared_ptr<Boll>& boll);

void hollIsHit(std::shared_ptr<Boll>& boll, bool& balF);

int main()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	if (DxLib_Init()) {
		return false;
	}
	ClsDrawScreen();

	//ピンの初期化
	//PinInit();

	bool balF = false;
	while (ProcessMessage() != -1)
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
			pinIshit(boll);
			hollIsHit(boll, balF);
			for (auto wall : wallPositions) {
				auto wallnorm = (wall.second - wall.first).Normalized();
				auto b = boll->pos_ - wall.first;
				auto P = wall.first + wallnorm * (wallnorm * b);
				auto bottom = max(wall.first.y, wall.second.y);
				auto top = min(wall.first.y, wall.second.y);
				if (top < boll->pos_.y) {
					if ((boll->pos_ - P).Magnitude() < bollR) {
						auto A = boll->pos_ - wall.second;
						auto B = wall.first - wall.second;
						auto S = boll->pos_ - wall.first;
						if ((A * S) * (B * S) >= 0) {
							if (boll->pos_.x < wall.first.x)
							{
								boll->pos_.x = wall.first.x - bollR;
							}
							else {
								boll->pos_.x = wall.first.x + bollR;
							}
							auto wallflt = GetRadian(wall);
							Vector2 tvec = { (static_cast<float>(sin(wallflt) * 0.1f)),(static_cast<float>(cos(wallflt) * 0.1f)) };
							tvec.Normalized();
							boll->vec_.y += gravity;
							auto rtvec = RefLectVec(boll->vec_.Normalized(), tvec);
							boll->vec_.x = boll->vec_.x * rtvec.x;
							boll->vec_.y = boll->vec_.y * rtvec.y;
						}
					}
				}
			}
		}

		ClearDrawScreen();
		//ゲームエリアの描画
		DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);

		//ボールの描画
		for (auto b : bolls) {
			auto color = 0xff0000;
			DrawCircle(b->pos_.x, b->pos_.y, bollR, color, true, true);
			DrawCircle(b->pos_.x, b->pos_.y, bollR, 0x000000, false, true);
		}
		//打ちだし場所の描画(デバッグ用)
		DrawCircle(downpt, 20, 20, 0x000000, false, true);
		//坂の描画
		for (auto h : HillPositions) {
			DrawLine(h.first.x, h.first.y, h.second.x, h.second.y, 0x000000);
		}
		//ピンの描画
		for (auto p : pinPositions) {
			DrawCircle(p.x, p.y, pinsize, 0x000000, true, true);
		}
		//穴の描画
		for (auto p : hollPosition) {
			DrawCircle(p.x, p.y, hollR, 0x000000, true, true);
		}
		for (auto p:wallPositions) {
			DrawLine(p.first.x, p.first.y, p.second.x, p.second.y, 0x000000);
		}
		DrawFormatString(0, 0, 0xFFFFFF, L"ぱわー %3.3f �l ", powP);
		ScreenFlip();
		//ボールの更新
		bam();


		for (auto b : bolls) {
			b->updata();
			if (b->pos_.x - bollR < xoffset) {
				b->pos_.x = xoffset + bollR;
			}
			else if (b->pos_.x + bollR > xoffset + 400) {
				b->pos_.x = xoffset + 400 - bollR;
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
void hollIsHit(std::shared_ptr<Boll>& boll, bool& balF)
{
	for (auto holl : hollPosition) {
		if (boll->pos_.x + bollR * 2 < holl.x + hollR * 2 &&
			boll->pos_.x - bollR * 2 > holl.x - hollR * 2 &&
			boll->pos_.y + bollR * 2 < holl.y + hollR * 2 &&
			boll->pos_.y - bollR * 2 > holl.y - hollR * 2) {
			bolls.clear();
			balF = false;
		}
	}
}
void pinIshit(std::shared_ptr<Boll>& boll)
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


			//auto pos = boll->pos_ + vec;
			//if ((boll->pos_ - pin).Magnitude() <= (boll->r + pinsize)) {

			//}


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
		if ((boll->pos_ - P).Magnitude() < bollR) {
			auto A = boll->pos_ - hillpos.second;
			auto B = hillpos.first - hillpos.second;
			auto S = boll->pos_ - hillpos.first;
			if ((A * S) * (B * S) >= 0)
			{
				auto right = max(hillpos.first.x, hillpos.second.x);
				auto left = min(hillpos.first.x, hillpos.second.x);
				if (right > boll->pos_.x && left < boll->pos_.x) {
					boll->alive = false;
					boll->vec_.y = 0;
					boll->pos_.y = P.y - bollR;
					gPosChange(boll, hillpos);
				}
			}
		}
		else {
			boll->alive = true;
		}
	}
}


