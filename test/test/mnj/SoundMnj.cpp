#include "SoundMnj.h"

SoundMnj* SoundMnj::sInstance = nullptr;

void SoundMnj::ResetD(void)
{
	seList_.clear();
}

void SoundMnj::AddBGM(std::wstring que)
{
	SetCreate3DSoundFlag(FALSE);
	bgmH_ = LoadSoundMem(que.c_str());

	ChangeVolumeSoundMem(255 * 30 / 100, bgmH_);
}

void SoundMnj::AddSE(std::wstring que,VECTOR pos,float Dis)
{
	CheckSEList(que);

	//PlaySoundMem(seHMap_[que], DX_PLAYTYPE_NORMAL);
	seList_.emplace_back(std::pair<std::wstring, std::pair<VECTOR, float>>(que, std::pair<VECTOR, float>(pos, Dis)));

}

void SoundMnj::Run(void)
{
	for (auto a : seList_)
	{
		Set3DPositionSoundMem(a.second.first, seHMap_[a.first]);
		Set3DRadiusSoundMem(a.second.second, seHMap_[a.first]);
		PlaySoundMem(seHMap_[a.first], DX_PLAYTYPE_BACK);
	}
	if (bgmH_ != -1)
	{
		if (CheckSoundMem(bgmH_) != 1)
		{
			PlaySoundMem(bgmH_, DX_PLAYTYPE_LOOP);
		}
	}
}

bool SoundMnj::CheckSEList(std::wstring que)
{
	if (seHMap_.find(que) == seHMap_.end())
	{
		SetCreate3DSoundFlag(TRUE);
		seHMap_.try_emplace(que, LoadSoundMem(que.c_str()));
		return true;
	}
	return false;
}

SoundMnj::SoundMnj()
{
	bgmH_ = -1;
}

SoundMnj::~SoundMnj()
{
}
