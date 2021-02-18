#pragma once
#include "Dxlib.h"
#include<memory>

enum class UNIT_ID			//���ꂼ��̗���
{
	PLAYER,	//�v���C���[�L����
	CPU,	//�v���C���[���삶��Ȃ��L����
	BULLET,	//�e
	NON,	//������
	MAX,	
};

// �ړ����x
#define MOVESPEED					10.0f

// ���쎲����ڲԖ{�̂Ƃ̂̋���
#define MOVE_DISTANCE		1.0f

// �p�x�ω����x
#define PLAYER_ANGLE_SPEED			0.2f	

class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual UNIT_ID GetUnitID(void)	//���j�b�gID��Ԃ�
	{
		return unitID_;
	}
	virtual VECTOR GetPos(void)	//�ʒu����Ԃ�
	{
		return pos_;
	}

	virtual void Updata(void) = 0;	//OBJ�n�̍X�V�p

	virtual void Updata(VECTOR pos)	//OBJ�n�̍X�V�p2�ق���OBJ�n�̍��W�Ȃǂ�����ꍇ
	{
		return;
	}

	void SetUnitID(UNIT_ID unitID) { unitID_ = unitID; }
	virtual	int GetSLR(void)
	{
		return 0;
	}
protected:
	VECTOR pos_;	//���W�i�[
	UNIT_ID unitID_;	//���j�b�gID�i�[
};

