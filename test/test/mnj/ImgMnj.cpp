#include <algorithm>
#include "ImgMnj.h"

ImgMnj* ImgMnj::sInstance = nullptr;

void ImgMnj::ResetD(void)
{
	drawListImg_.clear();
	setDrawBoxF_ = false;
}

void ImgMnj::AddImg(std::wstring que, Vector2 pos, float angle)
{
	std::pair<int, std::pair<Vector2, float>> tp = { std::move<>(GetGH(que)), std::move<>(std::pair<Vector2,float>(std::move<>(pos), std::move<>(angle))) };
	drawListImg_.emplace_back(std::move<>(tp));
}

int ImgMnj::GetGH(std::wstring que)
{
	if (imgHMap_.find(que) == imgHMap_.end())
	{
		imgHMap_.try_emplace(que, LoadGraph(que.c_str(), true));
	}
	return imgHMap_[que];
}

void ImgMnj::Draw(void)
{
	std::for_each(drawListImg_.begin(), drawListImg_.end(), [](auto dQue)
		{
			int handle = dQue.first;
			Vector2 pos = dQue.second.first;
			float angle = dQue.second.second;
			DxLib::DrawRotaGraph(pos.x, pos.y, 1.0f, angle, handle, true, false);
		});
	//for (auto& dQue : drawListImg_)
	//{
	//	int handle = dQue.first;
	//	Vector2 pos = dQue.second.first;
	//	float angle = dQue.second.second;
	//	DxLib::DrawRotaGraph(pos.x, pos.y, 1.0f, angle, handle, true, false);
	//}
	if (setDrawBoxF_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		DrawBox(800 / 2 - 200, 0, 800 / 2 + 200, 600, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ImgMnj::SetDrawBoxIm()
{
	setDrawBoxF_ = true;
}

ImgMnj::ImgMnj()
{
	setDrawBoxF_ = false;
	imgHMap_.clear();
}

ImgMnj::~ImgMnj()
{
	imgHMap_.clear();
}
