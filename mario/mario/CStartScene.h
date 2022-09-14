#pragma once

#include "CScene.h"

//==========================================================================//
//            CStartScene Ŭ����   ���� ���� ����� ó�����۵Ǵ� �޴� ��		//
//==========================================================================//
// CScene�� ��� :: CStageOne > CStageTwo > CStageThree > CStageFour Ŭ����  //
//                           �� 4���� ��������                               //
//                       �������� PrevScene() ȣ��						  	//
//                       �������� NextScene() ȣ��						  	//
//  ���� ���ӳ����� ������ ���� �޼��� NextScene()�� ȣ���ϴ� ������ �� �̵�	  	//
//==========================================================================//
//              CEndStage Ŭ���� : �������������� Ŭ����� �Ѿ�� ������      //  
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

