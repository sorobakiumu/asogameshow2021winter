#include "Result.h"
#include <DxLib.h>
#include "Title.h"
#include "Coins.h"
#include <assert.h>
#include "mnj/ImgMnj.h"

void Result::Run(std::shared_ptr<BaseGame>& baseGame)
{
	if (CheckHitKey(KEY_INPUT_0)) {
		baseGame = std::make_shared<Title>();
		baseGame->Init();
	}
}

void Result::Draw()
{
	ImgMnj::GetInstance().AddImg(L"Resource/image/tile.png", Vector2(-20, -20), 0.0);
	ImgMnj::GetInstance().Draw();
	ImgMnj::GetInstance().ResetD();
	DrawFormatString(0, 0, 0xffffff, L"result");
	for (int n = 0; n < 4; n++) {
		DrawFormatString(0, 20+n*20, 0xffffff, L"%d = %d個",n,okasi[n]);
	}
}

void Result::Init()
{
	valueTable[0] = 200;
	valueTable[1] = 100;
	valueTable[2] = 10;
	valueTable[3] = 5;

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

	flame = 0;
	//okasiList_[0] = L"スカイクッキー";
	//okasiList_[1] = L"コーンソード";
	//okasiList_[2] = L"うまか棒";
	//okasiList_[3] = L"トロルチョコ";

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
