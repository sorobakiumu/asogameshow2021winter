#include "EffekseerCtl.h"

EffekseerCtl* EffekseerCtl::sInstance = nullptr;

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
		auto a = LoadEffekseerEffect(text.c_str(), 1.0f);
		effectData_.emplace(fname, std::move(a));
	}
	return effectData_[fname];
}

void EffekseerCtl::SetEffect(std::string id, VECTOR pos)
{
	auto efct = PlayEffekseer2DEffect(GetEffect(id));
	SetPosPlayingEffekseer2DEffect(std::move(efct), pos.x, pos.y, 0);
}

void EffekseerCtl::Draw(void)
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer2D();
}

void EffekseerCtl::Updata(void)
{	
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer2D();
}
