//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include"Geometry.h"
//#include <DxLib.h>
//#include "BaseballGame.h"
//
//int main()
//{
//	DxLib::ChangeWindowMode(true);
//	DxLib::SetGraphMode(800, 600, 0, 0);
//	if (DxLib_Init()) {
//		return false;
//	}
//	ClsDrawScreen();
//
//	//�s���̏�����
//	//PinInit();
//
//	bool balF = false;
//
//	BaseballGame janken;
//	bool jankF = true;
//	while (ProcessMessage() == 0)
//	{
//		janken.RunGame();
//		ClearDrawScreen();
//		janken.DrawGame();
//		ScreenFlip();
//	}
//	delete& janken;
//	return 0;
//}
//
////// �����\����
////struct Segment {
////    Vector2 s; // �n�_
////    Vector2 v; // �����x�N�g���i�����̒������S���̂Ő��K�����Ȃ��悤�ɁI�j
////};
////
////// �����̏Փ�
////bool ColSegments(
////    Segment& seg1,          // ����1
////    Segment& seg2,          // ����2
////    float* outT1 = 0,       // ����1�̓�����i�o�́j
////    float* outT2 = 0,       // ����2�̓�����i�o��
////    Vector2* outPos = 0 // ��_�i�o�́j
////) {
////
////    Vector2 v = seg2.s - seg1.s;
////    float Crs_v1_v2 = Cross(seg1.v, seg2.v);
////    if (Crs_v1_v2 == 0.0f) {
////        // ���s���
////        return false;
////    }
////
////    float Crs_v_v1 = Cross(v, seg1.v);
////    float Crs_v_v2 = Cross(v, seg2.v);
////
////    float t1 = Crs_v_v2 / Crs_v1_v2;
////    float t2 = Crs_v_v1 / Crs_v1_v2;
////
////    if (outT1)
////        *outT1 = Crs_v_v2 / Crs_v1_v2;
////    if (outT2)
////        *outT2 = Crs_v_v1 / Crs_v1_v2;
////
////    const float eps = 0.00001f;
////    if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1) {
////        // �������Ă��Ȃ�
////        return false;
////    }
////
////    if (outPos)
////        *outPos = seg1.s + seg1.v * t1;
////
////    return true;
////}