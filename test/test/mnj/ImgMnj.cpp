#include "ImgMnj.h"

ImgMnj* ImgMnj::sInstance = nullptr;

void ImgMnj::ResetD(void)
{
	drawListImg_.clear();
}

void ImgMnj::AddImg(std::wstring que, Vector2 pos, float angle, bool flag)
{
	GetGH(que);
	std::tuple<int, Vector2, float, bool> tp = { GetGH(que), pos, angle, flag };
	drawListImg_.emplace_back(tp);
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
	for (auto dQue : drawListImg_)
	{
		int handle;
		Vector2 pos;
		float angle;
		bool turnFlag;
		std::tie(handle, pos, angle, turnFlag) = dQue;
		DxLib::DrawRotaGraph(pos.x, pos.y,1.0f,angle, handle, true,turnFlag);
	}
}

ImgMnj::ImgMnj()
{
	imgHMap_.clear();
}

ImgMnj::~ImgMnj()
{
	imgHMap_.clear();
}
