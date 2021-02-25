// tss.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <DxLib.h>

int main(void)
{
	int i, j, k;
	printf("1:[2]\n ");
	int c = 0;
	c++; 
	const char* fileName = "log.txt";

	std::ofstream ofs(fileName);
	ofs << "1: [2]" ;
	ofs << std::endl;

	for (i = 3; ProcessMessage()==0; i += 2)
	{
		k = 0;
		for (j = 3; j <= sqrt(i); j += 2)
		{
			if (i % j == 0)
			{
				k = 1;
				break;
			}
		}

		if (k == 0)
			c++; \
			printf("%d:[%d] \n", c, i); \
			ofs << c;\
			ofs << ":[";\
			ofs << i;\
			ofs << "]";\
			ofs << std::endl;

	}
	ofs.close();
	printf("\n");

	return 0;
}

