#include "WorldSoccer.h"

void WorldSoccer::Ran()
{
	for (int y = 0; y < ynum; y++) {
		int xnum = startnum;
		if (y % 2 == 1) {
			xnum = startnum + 1;
		}
		for (int x = 0; x < xnum; x++) {
			auto xnumoffset = 50;
			if (xnum != startnum) {
				xnumoffset = 25;
			}
			pinPositions.emplace_back(Vector2(xoffset + xnumoffset + 70 * x, 100 + 70 * y));
		}
	}
}

void WorldSoccer::Draw()
{
}

void WorldSoccer::Init()
{
}

void WorldSoccer::IsHit(std::shared_ptr<Boll>& boll)
{
	for (auto pin : pinPositions) {
		if ((boll->pos_ - pin).Magnitude() <= (bollR + pinsize)) {
			auto distance = pin - boll->pos_;
			if (distance.x == 0) {
				distance.x = (std::rand() % 2) * 2 - 1;
			}
			auto vec = boll->vec_;
			boll->vec_.x += distance.x * -0.1;
			boll->vec_.y = distance.y * -0.1;

		}
	}
}
