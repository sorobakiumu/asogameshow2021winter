#pragma once
#include<DxLib.h>
#include "Scene/sceneMng.h"

#define LpPadMng PadMng::GetInstance()

class PadMng
{
public:
	static PadMng& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new PadMng();
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
	void Run(void);
	DINPUT_JOYSTATE GetPad(void);
private:
	static PadMng* sInstance;

	DINPUT_JOYSTATE pad_;

	PadMng();
	~PadMng();
};

