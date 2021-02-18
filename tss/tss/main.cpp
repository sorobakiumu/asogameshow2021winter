#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "objmnj.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow)
{
	ChangeWindowMode(false);										//フルスクリーン
	if (DxLib_Init() == -1)										//DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	SceneMng::Create();
	SceneMng::GetInstance().Run();
 	SceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}