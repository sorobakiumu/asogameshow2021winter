#pragma once
#include <vector>
#include <DxLib.h>
#include "../Geometry.h"
#include <string>
#include <map>

#define lpSudlMng SoundMnj::GetInstance()

class SoundMnj
{
public:
	static SoundMnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SoundMnj();
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

	void AddBGM(std::wstring que);

	void AddSE(std::wstring que, VECTOR pos, float Dis);
	
	void Run(void);

	bool CheckSEList(std::wstring que);//指定したSEをすでに読み込んであるか調べる

	void StopBgm();
private:
	static SoundMnj* sInstance;

	std::vector <std::pair<std::wstring,std::pair<VECTOR,float>>> seList_;					//SEを溜めておくキュー
	std::map<std::wstring, int> seHMap_;

	int bgmH_;

	SoundMnj();
	~SoundMnj();
};

