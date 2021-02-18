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

	void Run(void);									//実行処理

	const Vector2 ScreenSize;						//画面サイズ

	void GameEnd(void);

	void SetLight(int num);

	VECTOR campos_;

private:
	bool systemEnd;									//**未作成**終了するを、押した場合

	int lightC_;

	int fcon_;										//フレームカウント
	static SceneMng* sInstance;						//シーンマネージャーの静的な宣言
	bool SysInit();									//初期化
	UNBS activeScene_;								//今動いてるsceneが入る。

	/*	すごく暗くて真っ暗。闇。　ポリゴン裏表反転させたドームを用意して、そらっぽい画像貼り付けたら空っぽくなると思ったら、真っ暗。ライトの数は3つまで。調べたら、シェーダーというもので解決できるようだが、全く分かんなかった。時間があったらあとでやってみよう		*/

	int lightHandle_;								//あかり1カメラ追跡ライト(せめてカメラ周囲は明るくしたいと思ったけど、ライト常時動かすのはやめたほうがいいかな？)
	int lightHandle2_;								//あかり2通常ライト　（こっちはふつうのライトで照らしてる予定（スポットライトだったり考えたけど、期待道理ではなかった））
	int lightHandle3_;								//あかり3通常ライト（お空に浮かんでるライト全方位を上から照らせばそれっぽくなるかなと。光の減衰率？を下げすぎると、画面真っ白で見えない。）


	std::vector<BulletQueT> bulletList_;			//弾丸キュー
	void Draw(void);								//描画処理
	SceneMng();
	~SceneMng();

};

