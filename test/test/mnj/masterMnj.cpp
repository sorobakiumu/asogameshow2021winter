#include "masterMnj.h"

masterMnj* masterMnj::sInstance = nullptr;

void masterMnj::Run(void)
{
	lpSudlMng.ResetD();
	lpImglMng.ResetD();
	LpPadMng.Run();

	lpEfclMng.Updata();
}

void masterMnj::Draw(void)
{
	lpImglMng.Draw();
	lpEfclMng.Draw();
	lpSudlMng.Run();
}

masterMnj::masterMnj()
{
	lpSudlMng.ResetD();
	lpImglMng.ResetD();
	lpEfclMng;
}

masterMnj::~masterMnj()
{
}
