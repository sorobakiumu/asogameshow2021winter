#include "CarRace.h"
#include <DxLib.h>
#include "Result.h"
#include "mnj/ImgMnj.h"
#include "Coins.h"
#include "GameSel.h"

int racebgm;

CarRace::CarRace()
{
}

CarRace::~CarRace()
{
	bolls.clear();
}

void CarRace::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (initflag) {
		PlaySoundMem(racebgm, DX_PLAYTYPE_LOOP);
		initflag = false;
	}
	//移動入力情報
	key = CheckHitKey(KEY_INPUT_SPACE);
	if (!balF)
	{
		if ((key == true) && (oldkey == true)) {
			Coins::GetInstance().coins--;
			if (Coins::GetInstance().coins < 0) {
				baseGame = std::make_shared<Result>();
				baseGame->Init();
			}
			bolls.emplace_back(new Boll({ downpt,1.0f }));
			balF = true;
		}
	}
	spsF_.first = spsF_.second;
 	if (CheckHitKey(KEY_INPUT_SPACE))
	{
        spsF_.second = true;
		powP_++;
		if (powP_ > 100)
			powP_ = 100;
	}
	else
	{
		spsF_.second = false;
	}
	if (!spsF_.first && !spsF_.second)
		powP_ = 0;
	oldkey = key;

	//当たり判定
	for (auto boll : bolls) {
		if (!shotBF_)
		{
			boll->vec_.y += gravity;
		}
		IsHit(boll, balF);
		//坂の当たり判定
		bam(powP_);

		if (static_cast<int>(shotOldPos_.x) > 800 / 2 + 150|| static_cast<int>(shotOldPos_.x) < 800 / 2 - 150)
		{
			if (static_cast<int>(shotOldPos_.x) == static_cast<int>(boll->pos_.x))
			{
				if (static_cast<int>(shotOldPos_.y) == static_cast<int>(boll->pos_.y))
				{
					shotBF_ = true;
					if (boll->pos_.x > 800 / 2)
						ShotLR_ = false;
					else
						ShotLR_ = true;
				}
			}
		}
		else
			shotBF_ = false;
		shotOldPos_ = boll->pos_;
	}

	//画面外防止
	for (auto b : bolls) {
		b->updata();
		if (b->pos_.x <= xoffset + bollR) {
			b->pos_.x = xoffset + bollR;
			b->vec_.x = {};
		}
		else if (b->pos_.x >= xoffset + 400 - bollR) {
			b->pos_.x = xoffset + 400 - bollR;
			b->vec_.x = {};
		}
		if (b->pos_.y > 600 || !b->alive) {
			bolls.clear();
			balF = false;
			PlaySoundMem(folB_, DX_PLAYTYPE_BACK);
		}
	}

	////ボールの描画
	//for (auto boll : bolls) {
	//	BollRadian(boll);
	//	lpImglMng.AddImg(L"Resource/image/coins.png", boll->pos_,boll->angle_);
	//}

	//シーン移行（デバッグ）
	//if (CheckHitKey(KEY_INPUT_5)) 
	int px, py;
	GetMousePoint(&px, &py);

	if (px >= 0 && px <= 64 && py >= 600 - 64 && py <= 600)
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			baseGame = std::make_shared<GameSel>();
			baseGame->Init();
			StopSoundMem(racebgm);
		}
	}
	tcon_++;
}

void CarRace::Draw()
{

	//ゲームエリアの描画
	//DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, 0xffffff, true);
	lpImglMng.AddImg(L"Resource\\image/tile.png", Vector2(800 / 2, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/setumei.png", Vector2(800 / 2 + 300, 600 / 2));
	lpImglMng.AddImg(L"Resource\\image/CarRace.png", Vector2(800 / 2, 600 / 2-5));

	//打ちだし場所の描画(デバッグ用)
#ifdef _DEBUG
	//DrawCircle(downpt, 20, 20, 0x000000, false, true);
	lpImglMng.AddImg(L"Resource\\image/ball.png", Vector2(downpt, 20));
#endif

	////坂の描画
	//for (auto h : HillPositions) {
	//	DrawLine(h.first.x, h.first.y, h.second.x, h.second.y, 0x000000);
	//}

	//穴の描画
	for (auto p : hollPosition) {
		//DrawCircle(p.x, p.y, hollR, 0x000000, true, true);
		lpImglMng.AddImg(L"Resource\\image/hol.png", Vector2(p.x, p.y));


	}
	//for (auto p : wallPositions) {
	//	DrawLine(p.first.x, p.first.y, p.second.x, p.second.y, 0x000000);
	//}

	//ボールの描画
	for (auto boll : bolls) 
	{
		if (shotBF_ && !zff_)
			lpImglMng.AddImg(L"Resource\\image/fir.png", Vector2(static_cast<int>(boll->pos_.x ), static_cast<int>(boll->pos_.y)), 0.0F, 1.0F * (powP_+40) / 100);
		BollRadian(boll);
		lpImglMng.AddImg(L"Resource\\image/coins.png", boll->pos_, boll->angle_);
	}

	//DrawFormatString(0, 0, 0xFFFFFF, L"ぱわー %3.3f ㌫ ", powP);
	//ボールの更新

	if (bolls.empty()) {
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
	lpImglMng.AddImg(L"Resource\\image/rsel.png", Vector2(32, 600 - 32));
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

	racebgm = LoadSoundMem(L"Resource\\music/car.mp3");
	golB_ = LoadSoundMem(L"Resource\\music/ジャン！.mp3");
	folB_ = LoadSoundMem(L"Resource\\music/foll.mp3");

	ChangeVolumeSoundMem(100, racebgm);

	initflag = true;
	tcon_++;
	powP_ = 0;
	shotBF_ = false;
	ShotLR_ = false;
	spsF_.first = false;
	spsF_.second = false;
}

void CarRace::IsHit(std::shared_ptr<Boll>& boll, bool& balF)
{
	HillIsHit(boll);
	hollIsHit(boll, balF);
	wallIsHit(boll);
	GoalIsHit(boll);
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
					boll->vec_.y = 0;
					boll->pos_.y = P.y - bollR;
					gPosChange(boll, hillpos);
				}
			}
		}
	}
}

void CarRace::hollIsHit(std::shared_ptr<Boll>& boll, bool& balF)
{
	for (auto holl : hollPosition) 
	{
		if (boll->pos_.x + bollR * 2 < holl.x + hollR * 2 &&
			boll->pos_.x - bollR * 2 > holl.x - hollR * 2 &&
			boll->pos_.y + bollR * 2 < holl.y + hollR * 2 &&
			boll->pos_.y - bollR * 2 > holl.y - hollR * 2) 
		{
			boll->alive = false;
			balF = false;
			PlaySoundMem(folB_, DX_PLAYTYPE_BACK);
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

void CarRace::GoalIsHit(std::shared_ptr<Boll>& boll)
{
	if (wallPositions[0].first.x < boll->pos_.x&&
		wallPositions[1].first.x > boll->pos_.x&&
		600-bollR<boll->pos_.y&&
		boll->alive)
	{
		Coins::GetInstance().kinken += 50;
		boll->alive = false;

		PlaySoundMem(golB_, DX_PLAYTYPE_BACK);
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
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	powP += 0.5;
	//	if (powP > 100)
	//	{
	//		powP = 100;
	//	}
	//	printf("ぱわぁぽいんと＝[%3.3f]\n", powP);
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	powP -= 0.5;
	//	if (powP < 0)
	//	{
	//		powP = 0;
	//	}
	//	printf("ぱわぁぽいんと＝[%3.3f]\n", powP);
	//}

	for (auto b : bolls)
	{
		auto* ve = &b->vec_;

		if (shotBF_&& !zff_)
		{
			if (spsF_.first && !spsF_.second)
			{
				if(!ShotLR_)
				{
					auto hillflt = GetRadian(HillPositions[0]);
					Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
					neuVec_.x -= pow;
					tvec.Normalized();
					auto rtvec = RefLectVec(neuVec_, tvec);
					zff_ = true;
					neuVec_ = rtvec / 10;
					neuVec_.x *= 2;
					neuCon_++;
				}
				else
				{
					auto hillflt = GetRadian(HillPositions[0]);
					Vector2 tvec = { (static_cast<float>(sin(hillflt) * 0.1f)),(static_cast<float>(cos(hillflt) * 0.1f)) };
					neuVec_.x = -pow;
					tvec.Normalized();
					auto rtvec = RefLectVec(neuVec_, tvec);
					zff_ = true;
					neuVec_ = rtvec / 10;
					if (neuVec_.x < 0)
						neuVec_.x *= -1;
					neuVec_.x *= 2;
					neuCon_++;
				}
			}
			/*
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
			}*/
		}
		else
		{
			if (neuCon_ == 0)
			{
				neuVec_ = { 0,0 };
				zff_ = false;
			}
			else
			{
				if (neuCon_ / 2 < 5)
				{
					*ve = neuVec_;
					neuCon_++;
				}
				else
				{
					neuCon_ = 0;
				}
			}
		}
	}
}
void Boll::updata() {
	pos_ += vec_;
}