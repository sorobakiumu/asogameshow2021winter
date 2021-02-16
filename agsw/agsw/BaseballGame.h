#pragma once
#include "Geometry.h"

struct BattStruct
{
	Vector2 batPos1_;
	Vector2 batPos2_;
	float leng_;
	int kakudo_;
};


struct Boll
{
	Vector2 pos_;
	Vector2 vec_;

	void updata() { pos_ += vec_; };
	bool alive = true;
};

class BaseballGame
{
public:
	BaseballGame();
	~BaseballGame();

	/// <summary>
	/// Ç∞Å[ÇﬁÇÈÅ[Ç’
	/// </summary>
	/// <param name=""></param>
	void RunGame(void);

	/// <summary>
	/// Ç—ÇÂÇ§Ç™
	/// </summary>
	/// <param name=""></param>
	void DrawGame(void);
private:
	/// <summary>
	/// ç≈èâÇæÇØÇÃèâä˙âª
	/// </summary>
	/// <param name=""></param>
	void init(void);

	void PushBat(void);

	void BatMoveing(void);

	bool CheckHitBat(std::pair<Vector2, Vector2> par1, std::pair<Vector2, Vector2> par2);

	bool PushBatF_;
	bool PushBatMOVEF_;
	bool BatMOVErF_;

	int gcon_;
	BattStruct batt_;
	Boll boll_;
	bool bollF_;
};


