#include "CarRace.h"
#include <DxLib.h>

CarRace::CarRace()
{
}

CarRace::~CarRace()
{
}

void CarRace::Run()
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
		printf("射出場所＝[%f]\n", downpt);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		downpt -= 3;
		printf("射出場所＝[%f]\n", downpt);
	}
	oldkey = key;

	//当たり判定
	for (auto boll : bolls) {
		boll->vec_.y += gravity;
		IsHit(boll, balF);
		//坂の当たり判定
	}
}

void CarRace::Draw()
{
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

	//穴の描画
	for (auto p : hollPosition) {
		DrawCircle(p.x, p.y, hollR, 0x000000, true, true);
	}
	for (auto p : wallPositions) {
		DrawLine(p.first.x, p.first.y, p.second.x, p.second.y, 0x000000);
	}
	DrawFormatString(0, 0, 0xFFFFFF, L"ぱわー %3.3f ㌫ ", powP);
	//ボールの更新
	bam(powP);


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

void CarRace::Init()
{
	HillPositions = {
	{{xoffset + xgameScreen,90} ,{400,70}},
	{{xoffset + hollR * 2,90} ,{320,70}},
	{{xoffset,220}, {400,200}},
	{{400 + hollR * 2,200}, {xoffset + xgameScreen - hollR * 2 + 10,180}},
	{{xoffset + xgameScreen,330} ,{xoffset + hollR * 5,300}},
	{{xoffset,420} ,{400,400}},
	{{xoffset + xgameScreen,500} ,{400,480}},
	};
	hollPosition = {
		{xoffset + hollR, 90},
		{xoffset + xgameScreen - hollR,180 } ,
		{xoffset + hollR,300 } };

	//firstが上側
	wallPositions = {
		{{xoffset + 50,550} ,{xoffset + 50,600}},
		{{xoffset + 50 + hollR * 2,550} ,{xoffset + 50 + hollR * 2,600}}
	};
}

void CarRace::IsHit(std::shared_ptr<Boll>& boll, bool& balF)
{
	HillIsHit(boll);
	hollIsHit(boll, balF);
	wallIsHit(boll);
}

void CarRace::HillIsHit(std::shared_ptr<Boll>& boll)
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

void CarRace::hollIsHit(std::shared_ptr<Boll>& boll, bool& balF)
{
	for (auto holl : hollPosition) {
		if (boll->pos_.x + bollR * 2 < holl.x + hollR * 2 &&
			boll->pos_.x - bollR * 2 > holl.x - hollR * 2 &&
			boll->pos_.y + bollR * 2 < holl.y + hollR * 2 &&
			boll->pos_.y - bollR * 2 > holl.y - hollR * 2) {
			boll->alive = false;
			balF = false;
		}
	}
}

void CarRace::wallIsHit(std::shared_ptr<Boll>& boll)
{
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

void CarRace::gPosChange(std::shared_ptr<Boll>& boll, std::pair<Vector2, Vector2> hillPos)
{
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
void CarRace::bam(int pow)
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
void Boll::updata() {
	pos_ += vec_;
}