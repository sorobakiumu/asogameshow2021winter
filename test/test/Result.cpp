#include "Result.h"
#include <DxLib.h>
#include "Title.h"
#include "Coins.h"
#include <assert.h>
#include "mnj/ImgMnj.h"
#include "mnj/masterMnj.h"

void Result::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (CheckHitKey(KEY_INPUT_0)) {
		baseGame = std::make_shared<Title>();
		baseGame->Init();
	}
	flame++;
	if (flame == 10) {
		PlaySoundMem(drum, DX_PLAYTYPE_BACK);
	}
	if (flame == 240) {
		StopSoundMem(drum);
		PlaySoundMem(jan, DX_PLAYTYPE_BACK);
		PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	}
	if (flame >= 240)
	{
		for (int i = 0; i < okasiPos_.size(); i++)
		{
			okasiPos_[i].y += 1;

			okasiPos_[i].x -= 0.5;
			if (okasiPos_[i].y > 620 || okasiPos_[i].x < -300)
				okasiPos_[i] = Vector2(rand() % 800, 0);
		}
	}
}

void Result::Draw()
{
	ImgMnj::GetInstance().AddImg(L"Resource/image/tile.png", Vector2(0, 100), 0.0);
	ImgMnj::GetInstance().Draw();
	ImgMnj::GetInstance().ResetD();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (flame >= 240)
	{
		int tcon = 0;
		for (int a = 0; a < okasi[0]; a++)
		{
			DrawGraph(okasiPos_[tcon].x, okasiPos_[tcon].y, okasiGraph[0], true);
			tcon++;
		}
		for (int a = 0; a < okasi[1]; a++)
		{
			DrawGraph(okasiPos_[tcon].x, okasiPos_[tcon].y, okasiGraph[1], true);
			tcon++;
		}
		for (int a = 0; a < okasi[2]; a++)
		{
			DrawGraph(okasiPos_[tcon].x, okasiPos_[tcon].y, okasiGraph[2], true);
			tcon++;
		}
		for (int a = 0; a < okasi[3]; a++)
		{
			DrawGraph(okasiPos_[tcon].x, okasiPos_[tcon].y, okasiGraph[3], true);
			tcon++;
		}
	}
	DrawRotaGraph(400,300,0.8,0.0,flameGraph,true);
	DrawGraph(250, 110, graph[0], true);

	if (flame > 60) {
		//DrawFormatString(200, 20, 0xffffff, L"スカイクッキー = %d個", okasi[0]);
		DrawGraph(200, 170, graph[1], true);
		numberDraw(okasi[0],Vector2(500, 170));
		DrawGraph(500, 170, graph[7], true);
	}
	if (flame > 90) {
		//DrawFormatString(200, 20 + 1 * 20, 0xffffff, L"コーンソード = %d個", okasi[1]);
		DrawGraph(200, 210, graph[2], true);
		numberDraw(okasi[1], Vector2(500, 210));
		DrawGraph(500, 210, graph[7], true);
	}
	if (flame > 120) {
		//DrawFormatString(200, 20 + 2 * 20, 0xffffff, L"うまか棒 = %d個",okasi[2]);
		DrawGraph(200, 250, graph[3], true);
		numberDraw(okasi[2], Vector2(500, 250));
		DrawGraph(500, 250, graph[7], true);
	}
	if (flame > 150) {
		//DrawFormatString(200, 20 + 3 * 20, 0xffffff, L"トロルチョコ = %d個", okasi[3]);
		DrawGraph(200, 290, graph[4], true);
		numberDraw(okasi[3], Vector2(500, 290));
		DrawGraph(500, 290, graph[7], true);
	}
	if (flame > 180&&flame<240) {
		//DrawFormatString(200, 200, 0xffffff, L"合計 %000d円分買いました", rand() % 1000);
		DrawGraph(200, 400, graph[5], true);
		numberDraw(rand() % 1000, Vector2(400, 400));
		DrawGraph(400, 400, graph[6], true);
	}
	if (flame >= 240) {
		//DrawFormatString(200, 200, 0xffffff, L"合計 %000d円分買いました", sum);
		DrawGraph(200, 400, graph[5], true);
		numberDraw(sum, Vector2(400, 400));
		DrawGraph(400, 400, graph[6], true);
	}
}

void Result::Init()
{
	InitSoundMem();
	srand(static_cast<unsigned int>(time(NULL)));
	valueTable[0] = 200;
	valueTable[1] = 100;
	valueTable[2] = 10;
	valueTable[3] = 5;
	LpMastMng.resultF_ = true;
	for (auto oka : okasi) {
		oka = 0;
	}
	auto coin = Coins::GetInstance().coins;
	auto kinken = Coins::GetInstance().kinken;
	//金券にかえる
	if (coin > 4){
		kinken += (coin / 5) * 10;
	}
	//お菓子にかえる
	for (int n = 0; n < 4; n++) {
		okasi[n] = value(valueTable[n], kinken);
	}
	int y = -400;
	for (auto ok : okasi)
	{
		for (int co = 0; co < ok; co++)
		{
			okasiPos_.emplace_back(Vector2(rand() % 800, y));
			y += 10;
		}
	}
	flame = 0;
	sum = 0;
	for (int n = 0; n < 4; n++) {
		sum += valueTable[n] * okasi[n];
	}
	flameGraph = LoadGraph(L"Resource\\image/フレーム.png");
	number[0] = LoadGraph(L"Resource\\image/0.png");
	number[1] = LoadGraph(L"Resource\\image/1.png");
	number[2] = LoadGraph(L"Resource\\image/2.png");
	number[3] = LoadGraph(L"Resource\\image/3.png");
	number[4] = LoadGraph(L"Resource\\image/4.png");
	number[5] = LoadGraph(L"Resource\\image/5.png");
	number[6] = LoadGraph(L"Resource\\image/6.png");
	number[7] = LoadGraph(L"Resource\\image/7.png");
	number[8] = LoadGraph(L"Resource\\image/8.png");
	number[9] = LoadGraph(L"Resource\\image/9.png");

	graph[0] = LoadGraph(L"Resource\\image/結果.png");
	graph[1] = LoadGraph(L"Resource\\image/スカイクッキー.png");
	graph[2] = LoadGraph(L"Resource\\image/コーンソード.png");
	graph[3] = LoadGraph(L"Resource\\image/うまか棒.png");
	graph[4] = LoadGraph(L"Resource\\image/トロルチョコ.png");
	graph[5] = LoadGraph(L"Resource\\image/合計.png");
	graph[6] = LoadGraph(L"Resource\\image/円分買いました.png");
	graph[7] = LoadGraph(L"Resource\\image/個.png");

	okasiGraph[0] = LoadGraph(L"Resource\\image/pk1.png");
	okasiGraph[1] = LoadGraph(L"Resource\\image/pk2.png");
	okasiGraph[2] = LoadGraph(L"Resource\\image/pk3.png");
	okasiGraph[3] = LoadGraph(L"Resource\\image/pk4.png");

	bgm_ = LoadSoundMem(L"Resource\\music/title.mp3");
	drum = LoadSoundMem(L"Resource\\music/ドラムロール.mp3");
	jan = LoadSoundMem(L"Resource\\music/ジャン！.mp3");
}

int Result::value(int& okasivalue, int& val)
{
	int num=0;
	if (val >= okasivalue) {
		val -= okasivalue;
		num++;
		num += value(okasivalue,val);
		if (val < 0) {
			assert(true);
		}
	}
	return num;
}

void Result::numberDraw(int num,Vector2 pos)
{
	auto one = num % 10;
	DrawGraph(pos.x-30,pos.y,number[one],true);
	num -= one;
	if (num <= 0) {
		return;
	}
	auto ten = (num/10) % 10;
	DrawGraph(pos.x - 60, pos.y, number[ten], true);
	num -= ten*10;
	if (num <= 0) {
		return;
	}
	auto hund = (num / 100) % 10;
	DrawGraph(pos.x - 90, pos.y, number[hund], true);
	num -= hund * 100;
	if (num <= 0) {
		return;
	}
	auto thand = (num / 1000) % 10;
	DrawGraph(pos.x - 120, pos.y, number[thand], true);
	num -= thand * 100;
	if (num <= 0) {
		return;
	}
}
