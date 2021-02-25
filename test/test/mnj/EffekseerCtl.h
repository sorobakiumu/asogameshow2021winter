#pragma once
#include <tuple>
#include <vector>
#include <DxLib.h>
#include<map>
#include<string>
#include "../Geometry.h"
#include<EffekseerForDXLib.h>

#define lpEfclMng EffekseerCtl::GetInstance()

using effmap = std::map<std::string,int>;

class EffekseerCtl
{
public:
	static 	EffekseerCtl& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new EffekseerCtl();
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

	int& GetEffect(std::string fname);
	void SetEffect(std::string id, VECTOR pos);
	void Draw(void);
	void Updata(void);
private:
	EffekseerCtl();
	~EffekseerCtl();
	static EffekseerCtl* sInstance;
	effmap effectData_;
	int fcon_;

};

