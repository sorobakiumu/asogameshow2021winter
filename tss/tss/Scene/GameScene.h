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
	UNBS Update(UNBS own) override;		//シーンを、更新する。
	GameScene();
	~GameScene();
	void Draw(void)override;
	SCN_ID GetSCNID_(void)override;
private:

	int pHp_;

	int lrSF_;
	float cpy_;
	int gcon_;
	Camera cam;											//カメラクラス格納
	std::vector<std::pair<shardObj, UNIT_ID>> _objList;	//アライブになっている存在を管理する。
	VECTOR ppos;										//プレイヤー座標渡し用

	bool plwlF_;
	int plwlFCon_;
};

