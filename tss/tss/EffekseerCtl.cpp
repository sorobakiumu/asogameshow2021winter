#include "EffekseerCtl.h"

EffekseerCtl::EffekseerCtl()
{
	fcon_ = 0;
	
	
	/*Vector2 tmsss = { 1430,600 };
	SetEffect(std::move(static_cast<std::string>("pblk")), tmsss);*/
}

EffekseerCtl::~EffekseerCtl()
{
}

int& EffekseerCtl::GetEffect(std::string fname)
{
	if (effectData_.find(fname) == effectData_.end())
	{
		std::string text = fname + ".efk";
		auto a = LoadEffekseerEffect(text.c_str(), 100.0f);
		effectData_.emplace(fname, std::move(a));
	}
	return effectData_[fname];
}

void EffekseerCtl::SetEffect(std::string id, VECTOR pos)
{
	auto efct = PlayEffekseer3DEffect(GetEffect(id));
	SetPosPlayingEffekseer3DEffect(std::move(efct), pos.x, pos.y, pos.z);
}

void EffekseerCtl::Drow(void)
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffekseerCtl::Updata(void)
{	
	// Effekseerにより再生中のエフェクトを更新する。
	DrawEffekseer3D();
}
