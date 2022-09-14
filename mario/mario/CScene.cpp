#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CSceneMgr.h"

size_t CScene::nPlayerCount;

CScene::CScene(wstring _szName)
	: m_szName(_szName)
{
}

CScene::~CScene()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end();++iter)
		{
			delete (*iter);
			iter = m_arrObject[i].erase(iter);
		}
	}
}


void CScene::AddObject(CObject* _pObj, OBJ_TYPE _eType)
{
	if (_eType == OBJ_TYPE::PLAYER)
		nPlayerCount++;

	m_arrObject[(UINT)_eType].emplace_back(_pObj);
}

list<CObject*>* CScene::GetObjectList(OBJ_TYPE _eType)
{
	return &m_arrObject[(UINT)_eType];
}

void CScene::Exit()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		////플레이어랑 터레인은 삭제안함
		if (i == (UINT)OBJ_TYPE::PLAYER)
			continue;
		if (i == (UINT)OBJ_TYPE::TERRAIN)
			continue;

		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end();)
		{
			(*iter)->Release();

			delete (*iter);
			iter = m_arrObject[i].erase(iter);
		}
	}
}