#include "pch.h"
#include "CStartScene.h"

#include "CSceneMgr.h"
#include "CLineMgr.h"
#include "CObject.h"

CStartScene::CStartScene(wstring _szName)
	: CScene(_szName)
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Enter()
{
	CLineMgr::GetInstance()->CreateLine();
	CLineMgr::GetInstance()->PushObjectList();

	//해당씬에 들어갈 오브젝트들 AddObject
	AddObject(new CObject(500.f, 500.f, 30.f),OBJ_TYPE::ENEMY);
}

void CStartScene::Update(float _fDeltaTime)
{
	CLineMgr::GetInstance()->CreateLine();
	CLineMgr::GetInstance()->PushObjectList();
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

void CStartScene::Render(HDC _hdc)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}
