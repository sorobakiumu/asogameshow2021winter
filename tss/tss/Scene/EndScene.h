#pragma once
#include "BaseScene.h"
#include <vector>
#include "../obj.h"
#include<memory>
#include "../camera.h"

class EndScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;		//シーンを、更新する。
	EndScene();
	~EndScene();
	void Draw(void)override;
	SCN_ID GetSCNID_(void)override;
private:
	float cpy_;
	std::pair < bool, bool > sps_;
};

