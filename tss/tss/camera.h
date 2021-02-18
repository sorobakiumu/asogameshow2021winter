#pragma once
#include "common/Geometry.h"

// カメラの回転速度
#define LOOK_ANGLE_SPEED		0.5f

// カメラの高さ
#define CAMERA_HEIGHT		100.0f

// カメラとﾌﾟﾚｲﾔ本体とのの距離
#define CAMERA_DISTANCE		200.0f*3

class Bullet;

class Camera
{
public:
	Camera();
	~Camera();
	void CameraRun(VECTOR targetPos);

private:
	void CameraInit(void);
	float	cameraYAngle;			//カメラ横の角度
	float	cameraXAngle;			//カメラ縦の角度
	float	cameraDistance;			//カメラ距離


	Vector2 mouse;					//マウス位置情報格納用

	friend Bullet;
};
