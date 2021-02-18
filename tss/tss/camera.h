#pragma once
#include "common/Geometry.h"

// �J�����̉�]���x
#define LOOK_ANGLE_SPEED		0.5f

// �J�����̍���
#define CAMERA_HEIGHT		100.0f

// �J��������ڲԖ{�̂Ƃ̂̋���
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
	float	cameraYAngle;			//�J�������̊p�x
	float	cameraXAngle;			//�J�����c�̊p�x
	float	cameraDistance;			//�J��������


	Vector2 mouse;					//�}�E�X�ʒu���i�[�p

	friend Bullet;
};
