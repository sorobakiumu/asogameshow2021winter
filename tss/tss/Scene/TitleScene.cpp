#include "sceneMng.h"
#include "../objmnj.h"
#include "../PadMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <DxLib.h>
#include "../common/Geometry.h"
#include "../ImgMnj.h"
#include "MenuScene.h"
#include "EndScene.h"

UNBS TitleScene::Update(UNBS own)
{
    sps_.second = sps_.first;
   
    if (LpPadMng.GetPad().Buttons[7])
    {
        return std::make_unique<MenuScene>(std::move(own));
    }

    if (CheckHitKey(KEY_INPUT_SPACE)||LpPadMng.GetPad().Buttons[0])
    {
        sps_.first = true;
    }
    else
    {
        sps_.first = false;
    }
    if (sps_.first && !sps_.second)
    {
        return std::make_unique<GameScene>();
    }
    
    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        return std::make_unique<EndScene>();
    }

    lpobjlMng.ObjRotation(UNIT_ID::PLAYER, -90, 0);
    lpobjlMng.Setobjpos(VGet(500.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::PLAYER, 0);
    lpobjlMng.Setobjpos(VGet(500.0f, cpy_-200, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::NON, 0);



    //•`‰æ‚É“Š‚°‚é
    lpobjlMng.ObjDraw(UNIT_ID::PLAYER, 0);
    SetCameraPositionAndTarget_UpVecY(VGet(0.0f, cpy_, -1000.0f), VGet(0.0f, cpy_+100, 0.0f));
    //lpobjlMng.Setobjpos(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::PLAYER, 0);
    //lpobjlMng.ObjDraw(UNIT_ID::PLAYER, 0);	

    if (lpSceneMng.GetFcon() / 60 % 2 == 0)
    {
        cpy_-=0.2f;
    }
    else
    {
        cpy_+= 0.2f;
    }
   lpImglMng.AddImg(std::string("img/title_.png"), Vector2(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2 - 300));
   lpImglMng.AddImg(std::string("img/space.png"), Vector2(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2 + 400));

   //if(lpSceneMng.GetFcon() % 60 == 0);
   //{
   //    lpSceneMng.SetEffect(EffectName::testef, VGet(500.0f, 100.0f, -250.0f));
   //}

    return own;
}

TitleScene::TitleScene()
{
    scnID_ = SCN_TITLE;
    cpy_ = 200.0f;
    SetWindowText("LineBattleoftheShip::ƒ^ƒCƒgƒ‹");

    SetFogColor(255, 255, 50);
    sps_ = { true,true };
}

TitleScene::~TitleScene()
{
}

void TitleScene::Draw(void)
{
   lpobjlMng.DrawNaw();
   lpImglMng.Draw();
}

SCN_ID TitleScene::GetSCNID_(void)
{
    return scnID_;
}
