#include "pch.h"
#include "CStageTwo.h"

#include "CObject.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CCore.h"
#include "CollisionMgr.h"
#include "CSceneMgr.h"
#include "CLineMgr.h"
#include "CInputMgr.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"
#include "CMapEditor.h"
#include "CPotal.h"

CStageTwo::CStageTwo(wstring _szName)
	: CScene(_szName)
	, m_hSubDC(0)
{
}

CStageTwo::~CStageTwo()
{
}

void CStageTwo::Enter()
{
	size_t i = CSceneMgr::GetInstance()->GetCurIndex();
	//오브젝트 삽입
	AddObject(new CPlayer(100.f, 500.f, 32.f), OBJ_TYPE::PLAYER);

	MapSize mapSize = CMapEditor::GetInst()->GetMapSize(MAP::STAGE_2);
	AddObject(new CPotal
	(mapSize.m_iWidth - (float)CPotal::POTAL_WIDTH * 1.5f //포탈 위치 X
		, mapSize.m_iHeight - (float)CPotal::POTAL_HEIGHT - 70.f//포탈 위치 Y
		, 0.f), OBJ_TYPE::POTAL);  // 포탈 크기와 오브젝트 타입(렌더링순서 관련)
}

void CStageTwo::Exit()
{
	ClearObject();
}

void CStageTwo::Update(float _fDeltaTime)
{
	/* Update */
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end();)
		{
			(*iter)->Update(_fDeltaTime);

			if ((*iter)->IsDisable())
			{
				delete (*iter);
				iter = m_arrObject[i].erase(iter);
				continue;
			}
			else
			{
				++iter;
			}
		}
	}
	/* LateUpdate */
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->LateUpdate(_fDeltaTime);
		}
	}
}

void CStageTwo::Render(HDC _hdc)
{
	SetBkMode(_hdc, TRANSPARENT);

	mapRender(_hdc);
	objectRedner(_hdc);

	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}

void CStageTwo::mapRender(HDC _hdc)
{
	size_t curMap = CSceneMgr::GetInstance()->GetCurIndex();

	wstring mapName = CMapEditor::GetInst()->GetMapName((MAP)curMap);
	m_hSubDC = CBitmapMgr::GetInstance()->FindBmp(mapName.c_str());
	MapSize mapSize = CMapEditor::GetInst()->GetMapSize((MAP)curMap);

	BitBlt(_hdc
		, (int)CScrollMgr::GetInst()->GetScrollX()
		, (int)CScrollMgr::GetInst()->GetScrollY(),
		(int)mapSize.m_iWidth,
		(int)mapSize.m_iHeight,
		m_hSubDC, 0, 0, SRCCOPY);
}

void CStageTwo::objectRedner(HDC _hdc)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
}
