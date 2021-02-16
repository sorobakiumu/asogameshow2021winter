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
//	//ピンの初期化
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
////// 線分構造体
////struct Segment {
////    Vector2 s; // 始点
////    Vector2 v; // 方向ベクトル（線分の長さも担うので正規化しないように！）
////};
////
////// 線分の衝突
////bool ColSegments(
////    Segment& seg1,          // 線分1
////    Segment& seg2,          // 線分2
////    float* outT1 = 0,       // 線分1の内分比（出力）
////    float* outT2 = 0,       // 線分2の内分比（出力
////    Vector2* outPos = 0 // 交点（出力）
////) {
////
////    Vector2 v = seg2.s - seg1.s;
////    float Crs_v1_v2 = Cross(seg1.v, seg2.v);
////    if (Crs_v1_v2 == 0.0f) {
////        // 平行状態
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
////        // 交差していない
////        return false;
////    }
////
////    if (outPos)
////        *outPos = seg1.s + seg1.v * t1;
////
////    return true;
////}