#include "pch.h"
#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CStartScene.h"

#include "CStageOne.h"
#include "CStageTwo.h"
#include "CStageThree.h"
#include "CStageFour.h"

#include "CStageEdit.h"
#include "CScrollMgr.h"


CSceneMgr* CSceneMgr::pInstance;

CSceneMgr::CSceneMgr()
	: m_nCurIndex(0)
{
	//스테이지 생성
	m_arrScene[(UINT)SCENE_STATE::STAGE_START] = new CStartScene(L"Start Scene");
	m_arrScene[(UINT)SCENE_STATE::STAGE_1]     = new CStageOne(L"Stage 1");
	m_arrScene[(UINT)SCENE_STATE::STAGE_2]     = new CStageTwo(L"Stage 2");
	m_arrScene[(UINT)SCENE_STATE::STAGE_3]     = new CStageThree(L"Stage 3");
	m_arrScene[(UINT)SCENE_STATE::STAGE_4]     = new CStageFour(L"Stage 4");
	m_arrScene[(UINT)SCENE_STATE::STAGE_END]   = new CStageOne(L"End Stage");
	m_arrScene[(UINT)SCENE_STATE::STAGE_EDIT]  = new CStageEdit(L"Edit Stage");

	//기본 씬은 스타트 씬
	m_pCurScene = m_arrScene[(UINT)SCENE_STATE::STAGE_START];
}
CSceneMgr::~CSceneMgr()
{
	for (auto& stage : m_arrScene)
		delete stage;
}

void CSceneMgr::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void CSceneMgr::PrevScene()
{
	if (m_nCurIndex > 0)
		m_nCurIndex--;

	m_pCurScene->Exit();
	CScrollMgr::GetInst()->Reset();
	m_pCurScene = m_arrScene[m_nCurIndex];
	m_pCurScene->Enter();
}

void CSceneMgr::NextScene()
{
	if (m_nCurIndex < (UINT)SCENE_STATE::STAGE_COUNT - 1)
		m_nCurIndex++;
	
	m_pCurScene->Exit();
	CScrollMgr::GetInst()->Reset();
	m_pCurScene = m_arrScene[m_nCurIndex];
	m_pCurScene->Enter();
	m_bNext = false;
}