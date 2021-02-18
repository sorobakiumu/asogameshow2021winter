#pragma once
#include <vector>
#include <DxLib.h>
#include "common/Geometry.h"
#include <string>
#include <map>

#define lpImglMng ImgMnj::GetInstance()

class ImgMnj
{
public:
	static ImgMnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ImgMnj();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void ResetD(void);

	/// <summary>
	/// 描画要請
	/// </summary>
	/// <param name="que">名前！</param>
	/// <param name="pos">座標！</param>
	/// <param name="num">左右反転するなら０以外入れること。しないなら無視可</param>
	void AddImg(std::string que, Vector2 pos, int num = 0);

	int GetGH(std::string que);

	void Draw(void);

private:
	static ImgMnj* sInstance;
	std::vector < std::pair<int, std::pair<Vector2,int>> > drawListImg_;					//描画するものを溜めておくキュー（画像）
	std::map<std::string, int> imgHMap_;

	ImgMnj();
	~ImgMnj();
};

