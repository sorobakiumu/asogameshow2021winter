#pragma once
#include "BaseScene.h"
#include <vector>
#include "../obj.h"
#include<memory>
#include "../camera.h"


class GameScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;		//�V�[�����A�X�V����B
	GameScene();
	~GameScene();
	void Draw(void)override;
	SCN_ID GetSCNID_(void)override;
private:

	int pHp_;

	int lrSF_;
	float cpy_;
	int gcon_;
	Camera cam;											//�J�����N���X�i�[
	std::vector<std::pair<shardObj, UNIT_ID>> _objList;	//�A���C�u�ɂȂ��Ă��鑶�݂��Ǘ�����B
	VECTOR ppos;										//�v���C���[���W�n���p

	bool plwlF_;
	int plwlFCon_;
};

