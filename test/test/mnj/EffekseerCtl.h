#pragma once
#include <tuple>
#include <vector>
#include <DxLib.h>
#include<map>
#include<string>
#include "../Geometry.h"
#include<EffekseerForDXLib.h>

using effmap = std::map<std::string,int>;
class EffekseerCtl
{
public:
	EffekseerCtl();
	~EffekseerCtl();

	int& GetEffect(std::string fname);
	void SetEffect(std::string id, VECTOR pos);
	void Drow(void);
	void Updata(void);
private:
	effmap effectData_;
	int fcon_;

};

