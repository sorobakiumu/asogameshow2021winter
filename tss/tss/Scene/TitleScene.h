#pragma once

#include "BaseScene.h"
#include <vector>
#include "../obj.h"
#include<memory>
#include <map>
#include "../camera.h"


class TitleScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;		//シーンを、更新する。
	TitleScene();
	~TitleScene(); 
	void Draw(void)override;
	SCN_ID GetSCNID_(void)override;
private:
	float cpy_;

	std::pair < bool, bool > sps_;
};

