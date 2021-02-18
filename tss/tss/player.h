#pragma once
#include "obj.h"

class Player :
	public Obj
{
public:
	Player();
	~Player();

	UNIT_ID GetUnitID(void) override
	{
		return unitID_;
	};

	VECTOR GetPos(void) override
	{
		return pos_;
	};

	void Updata(void) override;

	int GetSLR(void);

private:
	void MoveControl(void);	//��ڲԈړ�����
	int kazi_;				//�ǂ�؂�

	int shotLR_; //0==L 1==R
			
	float  moveYAngle_;			//���쎲�̉��̊p�x
	float  moveXAngle_;			//���쎲�̉��̊p�x
	VECTOR movePos_;				//���쎲�̈ʒu

	std::vector<int> pMcon_;
	std::vector<float> pMAng_;
	std::vector < std::pair<VECTOR, VECTOR> > pMmm_;
	
	int bcoon_;

	//VECTOR pos_;				//��ڲԍ��W
	VECTOR tmppPos_;
	VECTOR moveVec_;				//��ڲԂ̈ړ��ʕۑ�

	bool	flag_;				//true�����𒣂�false������������
	bool	fKeyold_;			//F���O�̃t���[���ɉ�����Ă��邩
	int		flagcon_;			//���̃J�E���g

	int		oneCount_;			//��b�v���p

	float bltAngl_;
};

