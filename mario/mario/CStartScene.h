#pragma once

#include "CScene.h"

//==========================================================================//
//            CStartScene 클래스   게임 최초 실행시 처음시작되는 메뉴 씬		//
//==========================================================================//
// CScene을 상속 :: CStageOne > CStageTwo > CStageThree > CStageFour 클래스  //
//                           총 4개의 스테이지                               //
//                       이전씬은 PrevScene() 호출						  	//
//                       다음씬은 NextScene() 호출						  	//
//  각자 게임내에서 일정한 조건 달성시 NextScene()을 호출하는 식으로 씬 이동	  	//
//==========================================================================//
//              CEndStage 클래스 : 마지막스테이지 클리어시 넘어가는 엔딩씬      //  
//==========================================================================//

class CStartScene : public CScene
{
public:
	explicit CStartScene(wstring _szName);
	virtual ~CStartScene();
	CStartScene(const CStartScene& rhs) = delete;
	CStartScene(CStartScene&& rhs) = delete;
	CStartScene& operator=(const CStartScene& rhs) = delete;
public:
	void Enter() override;
	void Update(float _fDeltaTime) override;
	void Render(HDC _hDC) override;
private:
};

