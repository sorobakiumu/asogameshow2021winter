#pragma once
#include <vector>
#include <tuple>
#include <DxLib.h>
#include "BaseScene.h"
#include "../common/Geometry.h"

#define lpSceneMng SceneMng::GetInstance()

using 	BulletQueT = std::tuple<VECTOR, int>;

class SceneMng
{
public:
	
	static SceneMng& GetInstance(void)
	{
		
		Create();
		return *sInstance;
	}
	
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
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

	int GetFcon(void) 
	{
		return fcon_; 
	}

	void Run(void);									//���s����

	const Vector2 ScreenSize;						//��ʃT�C�Y

	void GameEnd(void);

	void SetLight(int num);

	VECTOR campos_;

private:
	bool systemEnd;									//**���쐬**�I��������A�������ꍇ

	int lightC_;

	int fcon_;										//�t���[���J�E���g
	static SceneMng* sInstance;						//�V�[���}�l�[�W���[�̐ÓI�Ȑ錾
	bool SysInit();									//������
	UNBS activeScene_;								//�������Ă�scene������B

	/*	�������Â��Đ^���ÁB�ŁB�@�|���S�����\���]�������h�[����p�ӂ��āA������ۂ��摜�\��t���������ۂ��Ȃ�Ǝv������A�^���ÁB���C�g�̐���3�܂ŁB���ׂ���A�V�F�[�_�[�Ƃ������̂ŉ����ł���悤�����A�S��������Ȃ������B���Ԃ��������炠�Ƃł���Ă݂悤		*/

	int lightHandle_;								//������1�J�����ǐՃ��C�g(���߂ăJ�������͖͂��邭�������Ǝv�������ǁA���C�g�펞�������̂͂�߂��ق����������ȁH)
	int lightHandle2_;								//������2�ʏ탉�C�g�@�i�������͂ӂ��̃��C�g�ŏƂ炵�Ă�\��i�X�|�b�g���C�g��������l�������ǁA���ғ����ł͂Ȃ������j�j
	int lightHandle3_;								//������3�ʏ탉�C�g�i����ɕ�����ł郉�C�g�S���ʂ��ォ��Ƃ点�΂�����ۂ��Ȃ邩�ȂƁB���̌������H������������ƁA��ʐ^�����Ō����Ȃ��B�j


	std::vector<BulletQueT> bulletList_;			//�e�ۃL���[
	void Draw(void);								//�`�揈��
	SceneMng();
	~SceneMng();

};

