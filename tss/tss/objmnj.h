#pragma once
#include <vector>
#include "obj.h"


//#define CHARA_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
//#define CHARA_ENUM_DEFAULT_SIZE		3000.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
//#define CHARA_HIT_WIDTH				3000.0f		// �����蔻��J�v�Z���̔��a
//#define CHARA_HIT_HEIGHT			1000.0f		// �����蔻��J�v�Z���̍���
//#define CHARA_HIT_PUSH_POWER		40.0f		// �L�����N�^�[���m�œ��������Ƃ��̉����o������

#define lpobjlMng Objmnj::GetInstance()


//���f���Ǘ��}�l�[�W��
class Objmnj
{
public:
	static Objmnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Objmnj();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	void DrawNaw(void);

	void ReSetD(void);	//���t���[���ŏ��ɌĂ�

	void Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num);	//�ʒu�����Z�b�g id�ŁA����

	int Getobjpos(VECTOR pos, UNIT_ID id, int num);					//�ʒu����Ԃ��B

	UNIT_ID CheckHit(UNIT_ID id, int num);							//���������Ă邩�m�F�p**���ݎg�p�s��**								

	void ObjDraw(UNIT_ID id, int num);								//������ĂԂƁA�`��v�����Ascene�}�l�[�W���ɂ��܂�

	void ObjRotation(UNIT_ID id,float moveangle, int num);			//��]���i�����ځj���Z�b�g


private:
	static Objmnj* sInstance;


	std::vector<int> _drawList;						//�`�悷����̂𗭂߂Ă����L���[
	std::vector<int> _drawListnex;					//�`�悷����̂𗭂߂Ă����L���[�i������j

	int		issobj;					//�Ǌi�[�p
	int		playerobj;				//��ڲԃ��f���i�[�p
	int		phitobj;				//��ڲԓ����蔻�胂�f���i�[�p
	int		skyobj;					//��
	int		mapmodel;				//�C���f���i�[�p
	VECTOR	pvec;					//�v���C���ړ��x�N�g��
	VECTOR	ppos;					//�v���C���[���W

	UNIT_ID	player;					//��ڲԃ��f���i�[�p

	Objmnj();
	~Objmnj();
};

