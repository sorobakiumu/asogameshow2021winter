#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "BaseGame.h"

#define JankenMAX 3
#define JankenMove 3

/// <summary>
/// ����񂯂�̎�̎�ށI
/// �o���ĂȂ��I
/// ���[
/// ���傫
/// �ρ[
/// </summary>
enum JANKENACTION
{
	NO,
	GU,
	TYOKI,
	PA,
	MAX
};

/// <summary>
/// ���܂̃Q�[���X�e�[�^�X
/// �ҋ@��
/// ����񂯂�
/// ���U���g��
/// ����[���[
/// </summary>
enum NOWMODE
{
	STAY,
	JANK,
	RESER,
	FIN
};

enum GameFlag
{
	no_Gf,
	DRAW_GF,
	WINYOU_GF,
	WINCPU_GF
};

enum class OUTPUTDAT
{
	GOLD = 1,
	Three1P,
	Seven1P,
	One1P,
	Five1P,
	Two1P,
	ElevenP,
	Three2P,
	Seven2P,
	One2P,
	Five2P,
	Two2P,
};

class JankenPon :
	public BaseGame
{
public:
	JankenPon();
	~JankenPon();

	/// <summary>
	/// ���[�ނ�[��
	/// </summary>
	/// <param name=""></param>
	void Run(std::shared_ptr<BaseGame>& baseGame) override;

	/// <summary>
	/// �т傤��
	/// </summary>
	/// <param name=""></param>
	void Draw(void) override;
	/// <summary>
	/// �ŏ������̏�����
	/// </summary>
	/// <param name=""></param>
	void Init(void) override;
private:

	/// <summary>
	/// �ǂ̎���o�����l���i���������̂�T���j�đI�ԁ@10�����ɂ������������_���I�^����I
	/// </summary>
	/// <param name=""></param>
	void SetAct(void);

	/// <summary>
	/// �����܂�
	/// </summary>
	/// <param name=""></param>
	void StayMove(void);

	/// <summary>
	/// �I�����̏�����
	/// </summary>
	/// <param name=""></param>
	void Finmove(void);

	/// <summary>
	/// �Q�[�������i����񂯂񕔕��j
	/// </summary>
	/// <param name=""></param>
	void GameMove(void);

	/// <summary>
	/// ��[�����
	/// </summary>
	/// <param name=""></param>
	void ResultMove(void);

	/// <summary>
	/// ���Ҕ���
	/// </summary>
	/// <param name=""></param>
	void WinCheck(void);

	NOWMODE nowmode_;		//���܂̂��̃~�j�Q�[���ł̏��
	JANKENACTION youact_;	//�v���C���[���I�񂾎�
	JANKENACTION myflg_;	//CPU���񂪑I�񂾎�
	int nextfindMove_;		//CPU�N���\�z()�����v���C���[�̎��̎�
	int jankenData_[JankenMove][JankenMAX];//����܂ł̂���񂯂񂰁[��
	int otout_;				//���O�̃v���C���[�̎�
	int jcon_;				//����񂯂񂩂��񂽁[
	bool gconf_;			//���[�ރJ�E���g�p�̃t���O
	int gcon_;				//���[�ރJ�E���g
	GameFlag gameflag_;		//���Ҕ��茋�ʂ̕ϐ�

	int resconNum_;			//���U���g�̕b�������̕b���i�[�ϐ�
	bool resconF_;			//���U���g�ŁA���[���b�g�I��������i���Ȃ����ǂ����j

	int res_;				//���[���b�g���ʁi�߂����V�p�j

	int initflag;
	int gcpsound;
	int tcon_;

	int pMoney_;	//1�@pr 3 or 5
	bool SetFlg_;
	
	bool af_;
	bool aof_;
	bool sf_;
	bool sof_;
	bool df_;
	bool dof_;

	bool gameEndF_;
};

