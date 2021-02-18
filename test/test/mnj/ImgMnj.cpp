#include "ImgMnj.h"

ImgMnj* ImgMnj::sInstance = nullptr;

void ImgMnj::ResetD(void)
{
	drawListImg_.clear();
}

void ImgMnj::AddImg(std::string que, Vector2 pos, int num)
{
	GetGH(que);
	std::pair<Vector2, int> tp1 = { pos,num };
	std::pair<int, std::pair<Vector2, int>> tp = { GetGH(que),tp1 };
	drawListImg_.emplace_back(tp);
}

int ImgMnj::GetGH(std::string que)
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
		bool f = true;
		dQue.second.second == 0 ? f = false : f = true;
		DxLib::DrawRotaGraph(dQue.second.first.x, dQue.second.first.y,1.0f,0.0f, dQue.first, true,f);
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
