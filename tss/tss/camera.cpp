#include <math.h>
#include <DxLib.h>
#include "PadMng.h"
#include "camera.h"
#include "Scene/sceneMng.h"

Camera::Camera()
{
	CameraInit();
	
	SetMousePoint(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2);
}

Camera::~Camera()
{
}

void Camera::CameraInit(void)
{
	// カメラの座標を初期化
	cameraYAngle = 0.0f;
	cameraXAngle = 2.0f;
	mouse.x = 0;
	mouse.y = 0;
	cameraDistance = CAMERA_DISTANCE * 6;
}


void Camera::CameraRun(VECTOR targetPos)
{
	int tinx = 0, tiny = 0;
	GetMousePoint(&tinx, &tiny);
	mouse = { static_cast<float>(tinx),static_cast<float>(tiny) };
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0||LpPadMng.GetPad().Buttons[9])
	{
		// ホイールオン
		SetMousePoint(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2);
		//cameraDistance = CAMERA_DISTANCE;

		if (LpPadMng.GetPad().Ry < -100)
		{
			cameraDistance+=30;
		}
		if (LpPadMng.GetPad().Ry > 100)
		{
			cameraDistance-=30;
		}	
		if (cameraDistance < 750)
		{
			cameraDistance = 750;
		}
		if (cameraDistance > CAMERA_DISTANCE * 6)
		{
			cameraDistance = CAMERA_DISTANCE * 6;
		}
	}
	else
	{	
		cameraDistance -= static_cast<float>(GetMouseWheelRotVol()*50);
		if (cameraDistance < 750)
		{
			cameraDistance = 750;
		}
		if (cameraDistance > CAMERA_DISTANCE * 6)
		{
			cameraDistance = CAMERA_DISTANCE * 6;
		}
		// ホイールオフ
		if (LpPadMng.GetPad().Rx>100)	//CheckHitKey(KEY_INPUT_A)
		{
			cameraYAngle -= LOOK_ANGLE_SPEED;
			if (cameraYAngle >= 180.0f)
			{
				cameraYAngle -= 360.0f;
			}

		}
		if (LpPadMng.GetPad().Rx < -100)
		{
			cameraYAngle += LOOK_ANGLE_SPEED;
			if (cameraYAngle <= -180.0f)
			{
				cameraYAngle += 360.0f;
			}
		}
		if (LpPadMng.GetPad().Ry < -100)
		{
			cameraXAngle += LOOK_ANGLE_SPEED;
			if (cameraXAngle <= -180.0f)
			{
				cameraXAngle += 360.0f;
			}
		}
		if (LpPadMng.GetPad().Ry > 100)
		{
			cameraXAngle -= LOOK_ANGLE_SPEED;
			if (cameraXAngle >= 180.0f)
			{
				cameraXAngle -= 360.0f;
			}
		}
		if (lpSceneMng.ScreenSize.x / 2 - 100 > mouse.x)	//CheckHitKey(KEY_INPUT_A)
		{

			mouse.x = lpSceneMng.ScreenSize.x / 2 - 100;
			cameraYAngle -= LOOK_ANGLE_SPEED;
			if (cameraYAngle >= 180.0f)
			{
				cameraYAngle -= 360.0f;
			}

		}
		if (lpSceneMng.ScreenSize.x / 2 + 100 < mouse.x)
		{

			mouse.x = lpSceneMng.ScreenSize.x / 2 + 100;

			cameraYAngle += LOOK_ANGLE_SPEED;
			if (cameraYAngle <= -180.0f)
			{
				cameraYAngle += 360.0f;
			}
		}
		if (lpSceneMng.ScreenSize.y / 2 - 100 >= mouse.y)
		{
			mouse.y = lpSceneMng.ScreenSize.y / 2 - 100;

			cameraXAngle += LOOK_ANGLE_SPEED;
			if (cameraXAngle <= -180.0f)
			{
				cameraXAngle += 360.0f;
			}
		}
		if (lpSceneMng.ScreenSize.y / 2 + 100 <= mouse.y)
		{
			mouse.y = lpSceneMng.ScreenSize.y / 2 + 100;

			cameraXAngle -= LOOK_ANGLE_SPEED;
			if (cameraXAngle >= 180.0f)
			{
				cameraXAngle -= 360.0f;
			}
		}
		if (cameraXAngle < 0.0f)
		{
			cameraXAngle = 0.0f;
		}
		if (cameraXAngle > 20.0f)
		{
			cameraXAngle = 20.0f;
		}
		SetMousePoint(mouse.x, mouse.y);
	}
	VECTOR tempPos1= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempPos2= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	float pSin=NULL, pCos=NULL;

	tempCameraPos = VAdd(targetPos,VGet(0.0f,0.0f,0.0f));	//カメラの位置をﾌﾟﾚｲﾔ座標で初期化
	tempCameraPos.y += CAMERA_HEIGHT;	//初期化した位置にカメラの高さを加算

	//カメラの高さの角度を求める
	pSin = static_cast<float>(sin(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = pSin * cameraDistance;
	tempPos1.z = -pCos * cameraDistance;

	//カメラの横の角度を求める
	pSin = static_cast<float>(sin(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = pCos * tempPos1.x - pSin * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = pSin * tempPos1.x + pCos * tempPos1.z;
	VECTOR temptempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	temptempCameraPos = VAdd(tempPos2, tempCameraPos);	//求めた座標に初めにﾌﾟﾚｲﾔ座標で設定した値を加算してカメラ座標とする。
	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(temptempCameraPos, VAdd(temptempCameraPos, targetPos));
	SetCameraPositionAndTarget_UpVecY(temptempCameraPos, VAdd(targetPos,VGet(0.0f,0.0f,0.0f)));
	lpSceneMng.campos_ = temptempCameraPos;
}

