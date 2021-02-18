#include "PadMng.h"

PadMng* PadMng::sInstance = nullptr;

void PadMng::Run(void)
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad_);
}

DINPUT_JOYSTATE PadMng::GetPad(void)
{
	return pad_;
}

PadMng::PadMng()
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad_);
}

PadMng::~PadMng()
{
}
