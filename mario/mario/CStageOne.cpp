#include "pch.h"
#include "CStageOne.h"

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

CStageOne::CStageOne(wstring _szName)
	: CScene(_szName)
	, m_hSubDC(0)
{
}

CStageOne::~CStageOne()
{
}

void CStageOne::Enter()
{
	size_t i = CSceneMgr::GetInstance()->GetCurIndex();

	AddObject(new CPlayer(100.f, 500.f, 30.f), OBJ_TYPE::PLAYER);
}

void CStageOne::Exit()
{
	ClearObject();
}

void CStageOne::Update(float _fDeltaTime)
{
	//CMapEditor::GetInst()->Update();

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


	list<CObject*> playerList = *(CSceneMgr::GetInstance()->GetCurScene()->GetObjectList(OBJ_TYPE::PLAYER));
	CCollisionMgr::CollisionLine(playerList, *(CLineMgr::GetInstance()->GetLines(SCENE_STATE::STAGE_1)));
}

void CStageOne::Render(HDC _hdc)
{	
	SetBkMode(_hdc, TRANSPARENT);
	
	//CMapEditor::GetInst()->Render(_hdc);

	const MapSize* const mapSize = CMapEditor::GetInst()->GetMapSize();

	m_hSubDC = CBitmapMgr::GetInstance()->FindBmp(L"main1");

	BitBlt(_hdc
		,(int)CScrollMgr::GetInst()->GetScrollX()
		,(int)CScrollMgr::GetInst()->GetScrollY(),
		mapSize[1].m_iWidth,
		mapSize[1].m_iHeight,
		m_hSubDC, 0, 0, SRCCOPY);

	//m_hSubDC = CBitmapMgr::GetInstance()->FindBmp(L"main1");
	//m_hSubDC = CMapEditor::GetInst()->GetMap(MAP::MAIN);
	//BitBlt(_hdc, 0,0, 1920, 681, m_hSubDC, 0, 0, SRCCOPY);

	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}

	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}
