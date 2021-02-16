#include <DxLib.h>
#include <memory>
#include "Geometry.h"
#include <cmath>
#include <random>
#include <vector>
#include "CarRace.h"

namespace {
	std::shared_ptr<CarRace> carRace_;
}


int main()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	if (DxLib_Init()) {
		return false;
	}
	ClsDrawScreen();

	carRace_ = std::make_shared<CarRace>();
	carRace_->Init();
	//ƒsƒ“‚Ì‰Šú‰»

	while (ProcessMessage() != -1)
	{
		carRace_->Ran();
		ClsDrawScreen();
		carRace_->Draw();
		ScreenFlip();
	}

}




