#pragma once
#include <vector>
#include <map>
#include <string>
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

	/// <summary>
	/// �ʒu�����Z�b�g id�ŁA����
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="vec"></param>
	/// <param name="id">���O</param>
	/// <param name="num"></param>
	void Setobjpos(VECTOR pos, VECTOR vec, std::string id, int num);
	
	/// <summary>
	/// �ʒu����Ԃ��B
	/// </summary>
	/// <param name="id">�t�@�C��</param>
	/// <param name="num"></param>
	/// <returns></returns>
	VECTOR Getobjpos(std::string id);

	/// <summary>
	/// //������ĂԂƁA�`��v�����Ascene�}�l�[�W���ɂ��܂�
	/// </summary>
	/// <param name="id"></param>
	/// <param name="num"></param>
	void ObjDraw(std::string id, int num);								

	/// <summary>
	/// �I�u�W�F�N�g����]������I//��]���i�����ځj���Z�b�g
	/// </summary>
	/// <param name="id">�t�@�C����</param>
	/// <param name="moveangle">���񂮂�</param>
	void ObjRotation(std::string id,float moveangle);			

	/// <summary>
	/// �I�u�W�F�N�g��ǉ��I��̂��Ƃ��t�@�C�����̓^�O�ɂȂ邼�I
	/// </summary>
	/// <param name="que"></param>
	/// <param name="num"></param>
	void AddObj(std::string que, int num = 0);

	/// <summary>
	/// �Ă񂫂イ
	/// </summary>
	/// <param name=""></param>
	void update(void);
private:
	static Objmnj* sInstance;


	std::vector<int> _drawList;						//�`�悷����̂𗭂߂Ă����L���[
	std::vector<int> _drawListnex;					//�`�悷����̂𗭂߂Ă����L���[�i������j

	std::map<std::string, int> objHMap_;
	//int		issobj;					//�Ǌi�[�p
	//int		playerobj;				//��ڲԃ��f���i�[�p
	//int		phitobj;				//��ڲԓ����蔻�胂�f���i�[�p
	int		skyobj;					//��
	//int		mapmodel;				//�C���f���i�[�p
	//VECTOR	pvec;					//�v���C���ړ��x�N�g��
	//VECTOR	ppos;					//�v���C���[���W

	UNIT_ID	player;					//��ڲԃ��f���i�[�p

	Objmnj();
	~Objmnj();
};

