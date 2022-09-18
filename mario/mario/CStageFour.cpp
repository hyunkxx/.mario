#include "pch.h"
#include "CStageFour.h"

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

#include "CBossMonster.h"

CStageFour::CStageFour(wstring _szName)
	: CScene(_szName)
	, m_hSubDC(0)
{
}

CStageFour::~CStageFour()
{
}

void CStageFour::Enter()
{
	size_t i = CSceneMgr::GetInstance()->GetCurIndex();

	size_t curMap   = CSceneMgr::GetInstance()->GetCurIndex();
	MapSize mapSize = CMapEditor::GetInst()->GetMapSize((MAP)curMap);

	//시작화면 위치
	CScrollMgr::GetInst()->SetScrollX(0);
	CScrollMgr::GetInst()->SetScrollY(0);

	// 보스 몬스터 생성
	CBossMonster* BossMonster = new CBossMonster();
	BossMonster->SetTarget(m_arrObject[(UINT)OBJ_TYPE::PLAYER].front());
	AddObject(BossMonster, OBJ_TYPE::ENUMY);

	//오브젝트 삽입
	AddObject(new CPlayer(100.f, 800.f , 30.f), OBJ_TYPE::PLAYER);
}

void CStageFour::Exit()
{
	ClearObject();
}

void CStageFour::Update(float _fDeltaTime)
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

	//라인충돌
	/*list<CObject*> playerList = *(CSceneMgr::GetInstance()->GetCurScene()->GetObjectList(OBJ_TYPE::PLAYER));
	CCollisionMgr::CollisionLine(playerList, *(CLineMgr::GetInstance()->GetLines(SCENE_STATE::STAGE_1)));*/
}

void CStageFour::Render(HDC _hdc)
{
	SetBkMode(_hdc, TRANSPARENT);

	mapRender(_hdc);
	objectRedner(_hdc);

	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}

void CStageFour::mapRender(HDC _hdc)
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

void CStageFour::objectRedner(HDC _hdc)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
}
