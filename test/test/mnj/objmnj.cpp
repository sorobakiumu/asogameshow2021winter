#include<DxLib.h>
#include "masterMnj.h"
#include "objmnj.h"

Objmnj* Objmnj::sInstance = nullptr;

void Objmnj::DrawNaw(void)
{
	//í èÌï®ÇÇ∑Ç◊Çƒï`âÊå„ÅAÉKÉâÉXÇ»Ç«ÇÃìßÇØÇΩÇ¢Ç‡ÇÃÇï`âÊÇ∑ÇÈ
	//àÍÇ¬Ç∏Ç¬ï`âÊ
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);
	for (auto dQue : _drawList)
	{
		DxLib::MV1DrawModel(dQue);
	}
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);
	//Ç∑ÇØÇÈÇÃÇï`âÊ
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	for (auto dQue : _drawListnex)
	{
		DxLib::MV1DrawModel(dQue);
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}

void Objmnj::ReSetD(void)
{
	_drawList.clear();
	_drawListnex.clear();
}

void Objmnj::Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER==id)

	{	DxLib::MV1SetPosition(playerobj, pos);
		DxLib::MV1SetPosition(skyobj, pos);
		DxLib::MV1SetPosition(phitobj, pos);
		DxLib::MV1SetPosition(mapmodel, VAdd(pos,VGet(0.0f,30.0f,0.0f)));
		pvec = vec;
		ppos = pos;		

	}
	if (UNIT_ID::NON == id)
	{
		DxLib::MV1SetPosition(mapmodel, VAdd(pos, VGet(0.0f, 30.0f, 0.0f)));
	}
}

int Objmnj::Getobjpos(VECTOR pos, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		return playerobj;
	}
	return false;
}

UNIT_ID Objmnj::CheckHit(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		return player;
	}
	return UNIT_ID::NON;
}

void Objmnj::ObjDraw(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		_drawList.emplace_back(playerobj);
		_drawList.emplace_back(skyobj);
		_drawListnex.emplace_back(mapmodel);
	}
}

void Objmnj::ObjRotation(UNIT_ID id, float moveangle, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		DxLib::MV1SetRotationXYZ(playerobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
	}
}

Objmnj::Objmnj()
{
	playerobj = DxLib::MV1LoadModel("mv/vicShip.mv1");
	phitobj = DxLib::MV1LoadModel("mv/pHIT.mv1");
	issobj = DxLib::MV1LoadModel("mv/wll.mv1");
	DxLib::MV1SetPosition(issobj, VGet(0.0f, 0.0f, -5000.0f));
	DxLib::MV1SetupCollInfo(phitobj, -1, 8, 8, 8);
	ppos = VGet(0.0f, 0.0f, 0.0f);
	pvec = VGet(0.0f, 0.0f, 0.0f);
	//int FrNum = MV1GetFrameNum(issobj);

	//for (int i = 0; i < FrNum; i++)
	//{
	//	MV1SetFrameOpacityRate(issobj, i, 0.5f);
	//}
	skyobj = DxLib::MV1LoadModel("mv/sora.mv1");

	DxLib::MV1SetScale(skyobj, VGet(2.0f, 2.0f, 2.0f));

	player = UNIT_ID::NON;

	mapmodel = DxLib::MV1LoadModel("mv/men.mv1");

	DxLib::MV1SetOpacityRate(mapmodel, 0.5f);

	DxLib::MV1SetScale(mapmodel, VGet(2.5f, 1.1f, 2.5f));
}

Objmnj::~Objmnj()
{
}

