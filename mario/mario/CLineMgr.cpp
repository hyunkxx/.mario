#include "pch.h"
#include "CLineMgr.h"

#include "CCore.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CLine.h"
#include "CInputMgr.h"

CLineMgr* CLineMgr::pInstance;

CLineMgr::CLineMgr()
	: m_ptLeft(0.f,0.f)
	, m_ptRight(0.f, 0.f)
	, m_bReady(false)
{
}

CLineMgr::~CLineMgr()
{
}

void CLineMgr::SetBeginPoint()
{
	size_t index = CSceneMgr::GetInstance()->GetCurIndex();
	if (m_vecLines[index].size() == 0)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &mousePos);
		m_ptLeft.fX = (float)mousePos.x;
		m_ptLeft.fY = (float)mousePos.y;
	}
	else
	{
		m_ptLeft.fX = m_ptRight.fX;
		m_ptLeft.fY = m_ptRight.fY;
	}
}

void CLineMgr::SetEndPoint()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &mousePos);
	m_ptRight.fX = (float)mousePos.x;
	m_ptRight.fY = (float)mousePos.y;
	m_bReady = true;
}

void CLineMgr::CreateLine()
{
	size_t index = CSceneMgr::GetInstance()->GetCurIndex();

	if (CInputMgr::GetInstance()->GetKey(VK_LBUTTON, KEY_STATE::DOWN))
		SetBeginPoint();

	if (CInputMgr::GetInstance()->GetKey(VK_LBUTTON, KEY_STATE::DOWN))
	{
		SetEndPoint();

		if (m_bReady)
		{
			m_vecLines[index].push_back(new CLine(m_ptLeft, m_ptRight));
			m_bReady = false;
		}
	}
}

void CLineMgr::PushObjectList()
{
	//함수가 호출된 스테이지의 라인을 씬매니저 오브젝트로 푸쉬함
	size_t index = CSceneMgr::GetInstance()->GetCurIndex();

	for (auto iter = m_vecLines[(UINT)index].begin(); iter != m_vecLines[(UINT)index].end(); ++iter)
	{
		CSceneMgr::GetInstance()->GetCurScene()->AddObject(*iter, OBJ_TYPE::TERRAIN);
	}
}
