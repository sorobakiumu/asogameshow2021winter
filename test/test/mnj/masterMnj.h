#pragma once
#include "SoundMnj.h"
#include "PadMng.h"
#include "ImgMnj.h"
#include "EffekseerCtl.h"

#define LpMastMng masterMnj::GetInstance()

class masterMnj
{
public:
	static masterMnj& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new masterMnj();
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
	void Draw(void);
	bool resultF_;
private:
	static masterMnj* sInstance;

	masterMnj();
	~masterMnj();

};

