#include <DxLib.h>
#include <memory>
#include "Geometry.h"
#include <cmath>
#include <random>
#include <vector>
#include "CarRace.h"
#include "JankenPon.h"
#include "WorldSoccer.h"

namespace {
	std::shared_ptr<CarRace> carRace_;
	std::shared_ptr<WorldSoccer> worldSoccer_;
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

	worldSoccer_ = std::make_shared<WorldSoccer>();
	worldSoccer_->Init();

	while (ProcessMessage() != -1)
	{
		worldSoccer_->Ran();
		ClsDrawScreen();
		worldSoccer_->Draw();
		ScreenFlip();
	}

}




