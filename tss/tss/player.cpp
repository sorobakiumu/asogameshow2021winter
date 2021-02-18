#include <DxLib.h>
#include "scene/SceneMng.h"
#include "Scene/GameScene.h"
#include "player.h"
#include "objmnj.h"
#include "PadMng.h"

Player::Player()
{
	unitID_ = UNIT_ID::PLAYER;
	pos_ = VGet(0.0f, 0.0f, 0.0f);	//��ڲԍ��W������

	moveVec_ = VGet(0.0f, 0.0f, 1.0f);
	movePos_ = VGet(0.0f, 0.0f, 0.0f);	//���쎲�̍��W������
	moveYAngle_ = 0.0f;	//���쎲�̊p�x������
	moveXAngle_ = DX_PI_F;
	bltAngl_ = 0.0f;
	kazi_ = NULL;
	flag_ = true;
	flagcon_ = 10;
	fKeyold_ = false;
	oneCount_ = GetNowCount();
	tmppPos_ = pos_;

	//��ڲԂ̌�����ύX
	lpobjlMng.ObjRotation(unitID_, -moveYAngle_, 0);
	//���W�ݒ�
	lpobjlMng.Setobjpos(pos_, moveVec_, unitID_, 0);
	pMAng_.emplace_back(moveYAngle_);
	pMmm_.emplace_back(pos_, moveVec_);
	for (int i = 0; i < 3; i++)
	{
		pMcon_.emplace_back(0);
	}
	bcoon_ = 0;
	shotLR_ = 0;
}

Player::~Player()
{
}

void Player::Updata(void)
{
	if (CheckHitKey(KEY_INPUT_F))
	{
		if (!fKeyold_)
		{
			if (!flag_)
			{
				flag_ = true;
			}
			else
			{
				flag_ = false;
				flagcon_ = 10;
			}
		}
	}
	if (LpPadMng.GetPad().Buttons[4] && LpPadMng.GetPad().Buttons[5])
	{
		//����������Ă���ꍇ�͖�������B
	}
	else
	{
		if (LpPadMng.GetPad().Buttons[4])
		{
			shotLR_ = 1;
		}
		if (LpPadMng.GetPad().Buttons[5])
		{
			shotLR_ = 0;
		}

	}
	if (!flag_)
	{
		// �P�b�����Ă��邩
		if (GetNowCount() - oneCount_ > 1000)
		{
			flagcon_--;
			oneCount_ = GetNowCount();
		}
	}
	MoveControl();

	pMAng_.emplace_back(moveYAngle_);
	pMmm_.emplace_back(pos_, moveVec_);

	//��ڲԂ̌�����ύX
	lpobjlMng.ObjRotation(unitID_, -moveYAngle_, 0);
	lpobjlMng.ObjRotation(unitID_, -pMAng_[pMcon_[1]], 1);
	lpobjlMng.ObjRotation(unitID_, -pMAng_[pMcon_[2]], 2);
	//���W�ݒ�
	lpobjlMng.Setobjpos(pos_, moveVec_, unitID_, 0);
	lpobjlMng.Setobjpos(pMmm_[pMcon_[1]].first, pMmm_[pMcon_[1]].second, unitID_, 1);
	lpobjlMng.Setobjpos(pMmm_[pMcon_[2]].first, pMmm_[pMcon_[2]].second, unitID_, 2);

	//�`��ɓ�����
	lpobjlMng.ObjDraw(unitID_, 0);
	lpobjlMng.ObjDraw(unitID_, 1);
	lpobjlMng.ObjDraw(unitID_, 2);

	fKeyold_ = CheckHitKey(KEY_INPUT_F);

	VECTOR tmpvec = VNorm(VSub(pos_, movePos_));
	tmpvec.x *= 400.0f;
	tmpvec.z *= 400.0f;
	tmpvec.y = 0;
	tmppPos_ = pos_;
	pos_ = VAdd(pos_, tmpvec);
	if (pMcon_[0] >= 60*3)
	{
		if (pMcon_[1] >= 60*3)
		{
			pMcon_[2]++;
		}
		pMcon_[1]++;
	}
	pMcon_[0]++;
}

int Player::GetSLR(void)
{
	return shotLR_;
}

void Player::MoveControl(void)
{
	pos_ = tmppPos_;
	//����
	if (CheckHitKey(KEY_INPUT_A) || LpPadMng.GetPad().X < -100)
	{
		if (lpSceneMng.GetFcon() % 30 == 0)
		{
			kazi_++;
			if (kazi_ > 10)
			{
				kazi_ = 10;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_D) || LpPadMng.GetPad().X > 100)
	{

		if (lpSceneMng.GetFcon() % 30 == 0)
		{
			kazi_--;
			if (kazi_ < -10)
			{
				kazi_ = -10;
			}
		}
	}
	else
	{
		if (kazi_ != NULL)
		{
			if (kazi_ > 0)
			{
				kazi_ -= 2;
				if (kazi_ < 0)
				{
					kazi_ = NULL;
				}
			}
			else if (kazi_ < 0)
			{
				kazi_ += 2;
				if (kazi_ > 0)
				{
					kazi_ = NULL;
				}
			}
			else
			{
				kazi_ = NULL;
			}
		}
	}
	if (kazi_ > 2)
	{
		if (kazi_ < 6)
		{
			moveYAngle_ += 0.06f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}
		}
		else if (kazi_ < 8)
		{
			moveYAngle_ += 0.08f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}
		}
		else if (kazi_ <= 10)
		{
			moveYAngle_ += 0.12f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}
		}
	}
	if (kazi_ < -2)
	{
		if (kazi_ > -6)
		{
			moveYAngle_ -= 0.06f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}
		}
		else if (kazi_ > -8)
		{
			moveYAngle_ -= 0.08f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}
		}
		else if (kazi_ >= -10)
		{
			moveYAngle_ -= 0.12f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}
		}
	}
	if (flag_)
	{
		moveVec_.z += 5.0f;
	}
	else
	{
		if (flagcon_ >= 8)
		{
			moveVec_.z += 4.0f;
		}
		else if (flagcon_ >= 6)
		{
			moveVec_.z += 3.0f;
		}
		else if (flagcon_ >= 4)
		{
			moveVec_.z += 2.0f;
		}
		else
		{
			moveVec_.z += 1.0f;
		}
	}

	VECTOR tempPos1;
	VECTOR tempPos2;
	VECTOR tempMovePos;
	VECTOR tempMoveVec;
	float  tempf1;
	float  tempf2;
	float  temp1;
	float  temp2;


	tempMovePos = pos_;	//���쎲�̈ʒu����ڲԍ��W�ŏ�����

	//���쎲�̍����̊p�x�����߂�
	tempf1 = static_cast<float>(sin(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = 0.0f;
	tempPos1.z = -tempf2 * MOVE_DISTANCE;

	//���쎲�̉��̊p�x�����߂�
	tempf1 = static_cast<float>(sin(moveYAngle_ / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(moveYAngle_ / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;
	movePos_ = VAdd(tempPos2, tempMovePos);
	temp1 = static_cast<float>(sin(static_cast<double>(moveYAngle_ / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(moveYAngle_ / 180.0f)* DX_PI_F));
	tempMoveVec.x = moveVec_.x * temp2 - moveVec_.z * temp1;
	tempMoveVec.y = 0.0f;
	tempMoveVec.z = moveVec_.x * temp1 + moveVec_.z * temp2;
	moveVec_ = tempMoveVec;
	pos_ = VAdd(pos_, moveVec_);
	moveVec_ = VGet(0.0f, 0.0f, 0.0f);

	if (VNorm(VSub(lpSceneMng.campos_, VAdd(VNorm(VSub(pos_, movePos_)), pos_))).x > bltAngl_)
	{
		bltAngl_ += 0.5;
	}
	else if (VNorm(VSub(lpSceneMng.campos_, VAdd(VNorm(VSub(pos_, movePos_)), pos_))).x < bltAngl_)
	{
		bltAngl_ -= 0.5;
	}
	if (pMcon_[2] != 0)
	{
		if ((CheckHitKey(KEY_INPUT_SPACE) || LpPadMng.GetPad().Buttons[0]) && bcoon_ == 0)
		{
			VECTOR tmpvec1 = pos_, tmpvec2 = movePos_;
			tmpvec1.y = 0.0f;
			tmpvec2.y = 0.0f;
			bcoon_ = 0;
			bcoon_++;
		}
		if (bcoon_ != 0)
		{
			if (bcoon_ == 30)
			{
				VECTOR tmpvec1 = pMmm_[pMcon_[1]].first, tmpvec2 = movePos_, tmpvec3 = VNorm(movePos_);
				tmpvec1.y = 0.0f;
				tmpvec2.y = 0.0f;
			}
			if (bcoon_ == 30 * 2)
			{
				VECTOR tmpvec1 = pMmm_[pMcon_[2]].first, tmpvec2 = movePos_, tmpvec3 = VNorm(movePos_);
				tmpvec1.y = 0.0f;
				tmpvec2.y = 0.0f;
			}

			if (bcoon_ > 30 * 2)
			{
				bcoon_ = 0;
			}

			if (bcoon_ != 0)
			{
				bcoon_++;
			}
		}
	}
}

