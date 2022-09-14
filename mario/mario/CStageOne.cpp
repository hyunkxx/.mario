#include "pch.h"
#include "CStageOne.h"

#include "CObject.h"
#include "CScene.h"

CStageOne::CStageOne(wstring _szName)
	: CScene(_szName)
{
}

CStageOne::~CStageOne()
{
}

void CStageOne::Enter()
{
	//�ش���� �� ������Ʈ�� AddObject

	//�÷��̾ ������������ ����� > ������ ���̵��� �÷��̾� �����͸�
	// ����Ʈ���� ������ �����ʰ� �ٸ� ���� ���������� ����.
	if(nPlayerCount < 1)
		AddObject(new CObject(400.f, 400.f, 30.f), OBJ_TYPE::PLAYER);

	AddObject(new CObject(100.f, 100.f, 20.f), OBJ_TYPE::ENEMY);
	AddObject(new CObject(200.f, 200.f, 20.f), OBJ_TYPE::ENEMY);
	AddObject(new CObject(200.f, 300.f, 20.f), OBJ_TYPE::ENEMY);
	AddObject(new CObject(200.f, 400.f, 20.f), OBJ_TYPE::ENEMY);
}

void CStageOne::Update(float _fDeltaTime)
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

void CStageOne::Render(HDC _hdc)
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
