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
	UNBS Update(UNBS own) override;		//�V�[�����A�X�V����B
	TitleScene();
	~TitleScene(); 
	void Draw(void)override;
	SCN_ID GetSCNID_(void)override;
private:
	float cpy_;

	std::pair < bool, bool > sps_;
};

