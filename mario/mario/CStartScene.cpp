#include "pch.h"
#include "CStartScene.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CBitmapMgr.h"
#include "CCore.h"

CStartScene::CStartScene(wstring _szName)
	: CScene(_szName)
	, m_hSubDC(0)
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Enter()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Logo.bmp", L"Logo");
}

void CStartScene::Exit()
{
	ClearObject();
}

void CStartScene::Update(float _fDeltaTime)
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

void CStartScene::Render(HDC _hdc)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}

	m_hSubDC = CBitmapMgr::GetInstance()->FindBmp(L"Logo");
	BitBlt(_hdc, 0, 0, WIDTH, HEIGHT, m_hSubDC, 0, 0, SRCCOPY);
	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}
