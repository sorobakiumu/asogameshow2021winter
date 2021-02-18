#pragma once
#include "BaseScene.h"

enum class MenuMode
{
	MnM_DEFF,
	MnM_LIGHT,
	MnM_BACK,
	MnM_TITLE,
	MnM_END,
	MnM_MAX,
};

class MenuScene :
	public BaseScene
{
public:
	MenuScene(UNBS oscn);
	~MenuScene();
	UNBS Update(UNBS nsn)override;
	void Draw(void);
private:
	void Init(void);
	int yn;
	UNBS holdScn_;
	std::pair<bool, bool> rlF_;
	std::pair<bool, bool> llF_;
	std::pair<bool, bool> pbF_;
	
	int lightcon_;

	const int lightMax_;
	const int lightMin_;

	bool backF_;
	int backCon_;
	MenuMode mode_;
};
