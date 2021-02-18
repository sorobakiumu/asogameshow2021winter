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
	std::shared_ptr<BaseGame> game_;
	std::shared_ptr<WorldSoccer> worldSoccer_;
	std::shared_ptr<JankenPon> jankenpon_;
}

enum class GameMode
{
	CarRace,
	WorldSoccer,
	JankenPon
};
int main()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(800, 600, 0, 0);
	if (DxLib_Init()) {
		return false;
	}
	ClsDrawScreen();

	game_ = std::make_shared<JankenPon>();
	game_->Init();

	while (ProcessMessage() != -1)
	{
		game_->Run();
		ClsDrawScreen();
		game_->Draw();
		ScreenFlip();
	}

}




