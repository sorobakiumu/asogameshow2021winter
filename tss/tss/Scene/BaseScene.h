#pragma once
#include<memory>

enum SCN_ID
{
	SCN_BASE,
	SCN_TITLE,
	SCN_GAME,
	SCN_MAX,
};

class BaseScene;
using UNBS = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	BaseScene();
	virtual UNBS Update(UNBS own) = 0;	//シーンを、更新する。
	virtual ~BaseScene(); 
	virtual void Draw(void) = 0;
	virtual SCN_ID GetSCNID_(void);
protected:
	SCN_ID scnID_;
};
