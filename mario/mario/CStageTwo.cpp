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


#include "CMonsterDog.h"


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

<<<<<<< Updated upstream
	//����ȭ�� ��ġ
	CScrollMgr::GetInst()->SetScrollX(900);
	CScrollMgr::GetInst()->SetScrollY(0);
	//������Ʈ ����
	AddObject(new CPlayer(100.f, 100.f, 30.f), OBJ_TYPE::PLAYER);
=======
	MapSize mapSize = CMapEditor::GetInst()->GetMapSize(MAP::STAGE_2);
	
	int scX = CScrollMgr::GetInst()->GetScrollX();
	int scY = CScrollMgr::GetInst()->GetScrollY();

	AddObject(new CMonsterDog({ 300.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 440.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 770.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 980.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 990.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 1080.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);
	AddObject(new CMonsterDog({ 1200.f + scX, 470.f, 211.f  + scY, 143.f }), OBJ_TYPE::ENUMY);

	AddObject(new CPotal
	(mapSize.m_iWidth - (float)CPotal::POTAL_WIDTH * 1.5f //��Ż ��ġ X
		, mapSize.m_iHeight - (float)CPotal::POTAL_HEIGHT - 70.f//��Ż ��ġ Y
		, 0.f), OBJ_TYPE::POTAL);  // ��Ż ũ��� ������Ʈ Ÿ��(���������� ����)
>>>>>>> Stashed changes
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

	//�����浹
	/*list<CObject*> playerList = *(CSceneMgr::GetInstance()->GetCurScene()->GetObjectList(OBJ_TYPE::PLAYER));
	CCollisionMgr::CollisionLine(playerList, *(CLineMgr::GetInstance()->GetLines(SCENE_STATE::STAGE_1)));*/
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
